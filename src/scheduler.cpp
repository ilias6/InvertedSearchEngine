#include "../include/scheduler.hpp"
#include "../include/core_wrapper.hpp"
#include "../include/document.hpp"
#include "../include/entry.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <errno.h>
#include <cstdlib>
#include <pthread.h>

#include <unistd.h>

extern CoreWrapper * CW;


void Scheduler::waitPendingMatchesFinish(void){
    mutexDown(&this->pending_match_mutex);
    while(pending_match_jobs)
        pthread_cond_wait(&this->pending_match_cv,&this->pending_match_mutex);
    // all pending matches finished-> do all pending deactivates
    for(int i=0;i<pending_deactivate_counter;i++)
        pending_deactivate_queries->getItem(i)->deactivate();
    if(pending_deactivate_counter>0){
        delete pending_deactivate_queries;
        pending_deactivate_queries=NULL;
        pending_deactivate_queries=new Vector<Query*>(20);
        this->pending_deactivate_counter=0;
    }
    mutexUp(&this->pending_match_mutex);

    return ;
}

void Scheduler::waitPendingInsertionsFinish(void){
    mutexDown(&this->pending_insert_mutex);
    while(pending_insert_jobs)
        pthread_cond_wait(&this->pending_insert_cv,&this->pending_insert_mutex);
    // all pending matches finished-> do all pending deactivates
    mutexUp(&this->pending_insert_mutex);
    return ;
}

void Scheduler::waitForAvailRes(void){
    mutexDown(&this->results_mutex);
    while(!CW->results->getList().getLen())
        pthread_cond_wait(&this->avail_res_cv,&this->results_mutex);

    for(int i=0;i<pending_deactivate_counter;i++)
        pending_deactivate_queries->getItem(i)->deactivate();
    if(pending_deactivate_counter>0){
        delete pending_deactivate_queries;
        pending_deactivate_queries=NULL;
        pending_deactivate_queries=new Vector<Query*>(20);
        this->pending_deactivate_counter=0;
    }
    mutexUp(&this->results_mutex);
    return ;
}

void Scheduler::resMutexDown(void) {
    mutexDown(&this->results_mutex);
}

void Scheduler::resMutexUp(void) {
    mutexUp(&this->results_mutex);
}

inline bool checkCondition(pthread_mutex_t * stdout_mutex,pthread_mutex_t * mutex, bool * condition) {
    bool cond = false;
    // pthread_mutex_lock(stdout_mutex);
    // cout<<"check"<<endl;
    // pthread_mutex_unlock(stdout_mutex);
    mutexDown(mutex);
    if (*condition)
        cond = true;
    mutexUp(mutex);
    // pthread_mutex_lock(stdout_mutex);
    // cout<<"check done"<<endl;
    // pthread_mutex_unlock(stdout_mutex);
    return cond;
}

void * doJobFunction(void *void_argc){
    ArgClass * args = (ArgClass *)void_argc;
    int t_id=args->getId();
    int t_indx=t_id-1;
    //t_id is used as index in thread_jobs array
    //if thread_jobs[i]==NULL
    //then thread sleeps until a job is assigned to it
    Scheduler * sched = args->getSched();

    // cout<<"Hello i'm : "<<t_id<<endl;
    // acquire lock mutex
    while(1){
        mutexDown(&sched->job_mutex[t_indx]);
        while(sched->thread_jobs[t_indx]==NULL){
            //wait on condition variable if thread has no job
            // pthread_mutex_lock(&sched->stdout_mutex);
            // cout<<"I'm "<<t_id<<" and waiting until i get a job:"<<endl;
            // pthread_mutex_unlock(&sched->stdout_mutex);
            // sleep(2);

            if (checkCondition(&sched->stdout_mutex,&sched->work_condition_mutex, &sched->work_done)){

                // pthread_mutex_lock(&sched->stdout_mutex);
                // cout<<"I'm "<<t_id<<" and going to exit 1:"<<endl;
                // pthread_mutex_unlock(&sched->stdout_mutex);
                mutexUp(&sched->job_mutex[t_indx]);
                delete args;
                return NULL;
            }
            pthread_cond_wait(&sched->job_cv[t_indx],&sched->job_mutex[t_indx]);
            // if all jobs are done
            if (checkCondition(&sched->stdout_mutex,&sched->work_condition_mutex, &sched->work_done)){
                // pthread_mutex_lock(&sched->stdout_mutex);
                // cout<<"I'm "<<t_id<<" and going to exit 2:"<<endl;
                // pthread_mutex_unlock(&sched->stdout_mutex);
                mutexUp(&sched->job_mutex[t_indx]);
                delete args;
                return NULL;
            }
        }
        //if there are jobs for thread do stuff
        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"going to take job"<<endl;
        // pthread_mutex_unlock(&sched->stdout_mutex);
        Job * myJob=sched->thread_jobs[t_indx];
        mutexUp(&sched->job_mutex[t_indx]);
        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"took job"<<endl;
        // pthread_mutex_unlock(&sched->stdout_mutex);

        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"I'm "<<t_id<<" and got a job:\n\n";
        // pthread_mutex_unlock(&sched->stdout_mutex);

        if (sched->doJob(myJob, t_indx) != S_SUCCESS){
            return new SchedulerErrorCode(S_FAIL);
        }

        mutexDown(&sched->job_mutex[t_indx]);
        sched->thread_jobs[t_indx]=NULL;
        mutexUp(&sched->job_mutex[t_indx]);

        if (myJob->getId() == SEARCH) {
            mutexDown(&sched->threads_in_search_mutex);
            sched->threads_in_search--;
            mutexUp(&sched->threads_in_search_mutex);
        }
        delete myJob;

        /* signal master that i am available
        */

        pthread_cond_signal(&sched->avail_worker_cv);
    }
}

SchedulerErrorCode Scheduler::doJob(Job * job, int thread_index){
    JobId id = job->getId();
    switch(id){
        case SEARCH:
            {
                Args * searchArgs = job->getArgs();
                Document * doc = searchArgs->getDocument();
                Vector<Query *> * deactivated_vec=job->getDeactivated();
                Result * res=new Result(doc->getId(),*CW->queries);

                this->searches_in_progress[thread_index] = 1;

                // CW->searchWordExact(doc,res,thread_index);
                // CW->searchWordHamm(doc,res,thread_index);
                // CW->searchWordHammAndExact(doc,res,thread_index);
                CW->searchWordEdit(doc,res,thread_index);

                int words_in_doc=doc->getWordsInDoc();
                for(int i=0;i<words_in_doc;i++){
                    Word *w=doc->getWord(i);

                    List<Entry *> entry_res=CW->indeces[0][0]->search(w);
                    CW->increaseCounter(entry_res, res, MT_EXACT_MATCH, 0);

                    int len = w->getLen();
                    int range = 3;
                    if (len < range)
                        range = len;
                    for (int j = 0; j <= range; ++j) {
                        List<Entry *> entry_res=CW->indeces[1][j]->search(w, j);
                        CW->increaseCounter(entry_res, res, MT_HAMMING_DIST, j);
                    }
                }


                mutexDown(&this->searches_mutex[thread_index]);

                while (this->searches_in_progress[thread_index] > 0)
                    pthread_cond_wait(&this->searches_cv[thread_index], &this->searches_mutex[thread_index]);

                // cout << thread_index+1 << " Wake up now" << endl;
                mutexUp(&this->searches_mutex[thread_index]);

                mutexDown(&this->results_mutex);

        // for deactivate: remove queries that shouldn't be in result (deactivated queries)
                if(deactivated_vec!=NULL){
                    int vlen=deactivated_vec->getLen();
                    for(int i=0;i<vlen;i++)
                        res->resetCounters(deactivated_vec->getItem(i)->getId());
                }


                if(CW->addResult(res)==C_W_FAIL){
                    delete res;
                    delete doc;
                    cerr<<"Failed adding result to result_pool ! [DocID "<<doc->getId()<<"] "<<endl;
                    exit(1);
                }
                delete doc;
                if (CW->results->getList().getLen() == 1)
                    pthread_cond_signal(&this->avail_res_cv);

                mutexUp(&this->results_mutex);

                // decrease pending_match_jobs
                mutexDown(&this->pending_match_mutex);
                this->pending_match_jobs--;
                // cout << "Done: " << doc->getId() << endl;
                   // cout<<"pending"<<this->pending_match_jobs<<endl;
                if(this->pending_match_jobs==0){
                    pthread_cond_signal(&this->pending_match_cv);
                }
                mutexUp(&this->pending_match_mutex);
            }
            break;

        case SEARCH_METHOD:
            {
            Args * searchMethodArgs = job->getArgs();
            Result * res = searchMethodArgs->getRes();
            Document * doc = searchMethodArgs->getDocument();
            // int type = searchMethodArgs->getType();
            // int dist = searchMethodArgs->getDist();
            int thread_index = searchMethodArgs->getParentIndex();

            int words_in_doc=doc->getWordsInDoc();
            for(int i=0;i<words_in_doc;i++){
                Word *w=doc->getWord(i);
                for (int j = 0; j <= 3; ++j) {
                    List<Entry *> entry_res=CW->indeces[2][j]->search(w, j);
                    CW->increaseCounter(entry_res, res, MT_EDIT_DIST, j);
                }
            }

            mutexDown(&this->searches_mutex[thread_index]);
            this->searches_in_progress[thread_index]--;
            if(this->searches_in_progress[thread_index]==0) {
                // pthread_mutex_lock(&this->stdout_mutex);
                // cout << "Signaled :" << thread_index << endl;
                // pthread_mutex_unlock(&this->stdout_mutex);
                pthread_cond_signal(&searches_cv[thread_index]);
            }
            mutexUp(&this->searches_mutex[thread_index]);
            }
            break;
        case INSERT:
            {
            Args * insertArgs = job->getArgs();
            Query * q = insertArgs->getQuery();
            int type = q->getType();
            int dist = q->getMatchDist();

            Entry ** e_arr=NULL;
            mutexDown(&this->entryList_mutex);
            CW->entryList->insert(*q, &e_arr);
            mutexUp(&this->entryList_mutex);

            switch(type){
                case MT_EXACT_MATCH:
                    mutexDown(&this->hash_mutex);
                    CW->indeces[0][0]->insert(e_arr);
                    mutexUp(&this->hash_mutex);
                    break;
                case MT_HAMMING_DIST:
                    CW->indeces[1][dist]->insert(e_arr);
                    break;
                case MT_EDIT_DIST:
                    CW->indeces[2][dist]->insert(e_arr);
                    break;
            }
            delete[] e_arr;
            // decrease pending_insert_jobs
            mutexDown(&this->pending_insert_mutex);
            this->pending_insert_jobs--;
            // cout << "Done: " << doc->getId() << endl;
               // cout<<"pending"<<this->pending_match_jobs<<endl;
            if(this->pending_insert_jobs==0){
                pthread_cond_signal(&this->pending_insert_cv);
            }
            mutexUp(&this->pending_insert_mutex);
            }
            break;
        default:
            break;
    }
    return S_SUCCESS;
}

int Scheduler::assignJob() {
    while (1) {

        for (int i = 0; i < this->numOfThreads-1; ++i) {

            mutexDown(&this->job_mutex[i]);
            if (this->thread_jobs[i] == NULL) {
                // pthread_mutex_lock(&this->stdout_mutex);
                // cout<<i<<" Before pop: "<<this->q.getList().getLen()<<endl;
                // pthread_mutex_unlock(&this->stdout_mutex);

                Job * job = NULL;
                mutexDown(&this->threads_in_search_mutex);
                if (this->max_docs_in_par <= this->threads_in_search) {
                    while (this->max_docs_in_par <= this->threads_in_search) {
                        mutexUp(&this->threads_in_search_mutex);

                        mutexDown(&this->queue_mutex);
                        job = this->q.pop();
                        mutexUp(&this->queue_mutex);

                        JobId jobId = job->getId();
                        if (jobId == SEARCH) {
                            mutexDown(&this->queue_mutex);
                            this->q.push(job);
                            job = NULL;
                            mutexUp(&this->queue_mutex);
                        }
                        else {
                            mutexDown(&this->threads_in_search_mutex);
                            break;
                        }
                        mutexDown(&this->threads_in_search_mutex);
                    }
                    mutexUp(&this->threads_in_search_mutex);
                }
                else {
                    mutexUp(&this->threads_in_search_mutex);

                    mutexDown(&this->queue_mutex);
                    job = this->q.pop();
                    mutexUp(&this->queue_mutex);
                }
                if (job == NULL) {
                    mutexDown(&this->queue_mutex);
                    job = this->q.pop();
                    mutexUp(&this->queue_mutex);
                }
                if (job->getId() == SEARCH) {
                    mutexDown(&this->threads_in_search_mutex);
                    this->threads_in_search++;
                    mutexUp(&this->threads_in_search_mutex);
                }
                // pthread_mutex_lock(&this->stdout_mutex);
                // cout<<i<<" After pop "<<this->q.getList().getLen()<<endl;
                // pthread_mutex_unlock(&this->stdout_mutex);

                this->thread_jobs[i] = job;
                mutexUp(&this->job_mutex[i]);
                if (pthread_cond_signal(&this->job_cv[i])) {
                    perror("cond_signal failed (giveJobFunction)");
                    pthread_exit(NULL);
                }
                // pthread_mutex_lock(&sched->stdout_mutex);
                // cout<<"signaled : "<<avail_t_id+1<<" to get job"<<endl;
                // pthread_mutex_unlock(&sched->stdout_mutex);
                return 0;
            }
            mutexUp(&this->job_mutex[i]);
        }
        pthread_cond_wait(&this->avail_worker_cv, &this->avail_worker_mutex);

    }

    return -1;
}

void * giveJobFunction(void *void_argc){

    ArgClass * args = (ArgClass *)void_argc;
    // int t_id=args->getId();
    // int t_indx=t_id;//thread 0
    //t_id is used as index in thread_jobs array
    //if thread_jobs[i]==NULL
    //then thread sleeps until a job is assigned to it
    Scheduler * sched = args->getSched();

    while(1) {

        mutexDown(&sched->queue_mutex);
        while(sched->q.getList().getLen() == 0){
            // pthread_mutex_lock(&sched->stdout_mutex);
            // cout<<"\n\tI'M THREAD 0 AND WAIT TO GET A JOB TO ASSIGN"<<endl;
            // pthread_mutex_unlock(&sched->stdout_mutex);

            if (checkCondition(&sched->stdout_mutex,&sched->work_condition_mutex, &sched->work_done)) {
                mutexUp(&sched->queue_mutex);
                delete args;
                return NULL;
            }
           // pthread_mutex_lock(&sched->stdout_mutex);
            // cout<<"\n\tI'M THREAD 0 and fell asleep"<<endl;
           // pthread_mutex_unlock(&sched->stdout_mutex);
            pthread_cond_wait(&sched->queue_cv, &sched->queue_mutex);
          // pthread_mutex_lock(&sched->stdout_mutex);
           // cout<<"\n\tI'M THREAD 0 and woke up"<<endl;
          // pthread_mutex_unlock(&sched->stdout_mutex);
            if (checkCondition(&sched->stdout_mutex,&sched->work_condition_mutex, &sched->work_done)) {
                mutexUp(&sched->queue_mutex);
                delete args;
                return NULL;
            }
        }
        mutexUp(&sched->queue_mutex);
        int avail_t_id = sched->assignJob();
        if (avail_t_id != -1) {

        }
        else {
            cout<<"\n\tFUCK"<<endl;;
            // sleep(1);
        }
    }

}

Scheduler::Scheduler(int threads_num){
    //threads_num workers + 1 the master thread
    this->pending_deactivate_counter=0;
    this->job_mutex=(pthread_mutex_t *)malloc((threads_num)*sizeof(pthread_mutex_t));
    this->searches_mutex=(pthread_mutex_t *)malloc((threads_num)*sizeof(pthread_mutex_t));
    this->search_res_mutex=(pthread_mutex_t *)malloc((threads_num)*sizeof(pthread_mutex_t));
    this->searches_in_progress=(int *)malloc((threads_num)*sizeof(int));
    this->searches_cv=(pthread_cond_t *)malloc((threads_num)*sizeof(pthread_cond_t));
    this->stdout_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->queue_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->avail_worker_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->results_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->pending_match_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->pending_insert_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->work_condition_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->threads_in_search_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->entryList_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->hash_mutex=PTHREAD_MUTEX_INITIALIZER;

    this->max_docs_in_par = threads_num/2;
    this->threads_in_search=0;

    this->pending_match_jobs=0;
    this->pending_insert_jobs=0;
    this->work_done = false;

    this->pending_deactivate_queries=new Vector<Query *>(20);

    if(this->job_mutex==NULL){
        perror("Malloc job mutex arr failed");
        exit(1);
    }
    this->job_cv=(pthread_cond_t *)malloc((threads_num)*sizeof(pthread_cond_t));
    if(this->job_cv==NULL){
        perror("Malloc condition var arr failed");
        exit(1);
    }
    int ret_v = pthread_cond_init(&this->pending_match_cv, NULL);
    if(ret_v){
        perror("Error initializing pending match job condition variable");
        exit(1);
    }
    ret_v = pthread_cond_init(&this->pending_insert_cv, NULL);
    if(ret_v){
        perror("Error initializing pending match job condition variable");
        exit(1);
    }
    ret_v = pthread_cond_init(&this->queue_cv, NULL);
    if(ret_v){
        perror("Error initializing queue condition variable");
        exit(1);
    }
    ret_v = pthread_cond_init(&this->avail_res_cv, NULL);
    if(ret_v){
        perror("Error initializing queue condition variable");
        exit(1);
    }
    ret_v = pthread_cond_init(&this->avail_worker_cv, NULL);
    if(ret_v){
        perror("Error initializing avail_worker condition variable");
        exit(1);
    }
    for(int i=0;i<threads_num;i++){
        ret_v = pthread_cond_init(&this->searches_cv[i], NULL);
        if(ret_v){
            perror("Error initializing queue condition variable");
            exit(1);
        }
        this->job_mutex[i]=PTHREAD_MUTEX_INITIALIZER;
        this->searches_in_progress[i]=0;
        this->searches_mutex[i]=PTHREAD_MUTEX_INITIALIZER;
        this->search_res_mutex[i]=PTHREAD_MUTEX_INITIALIZER;
        ret_v = pthread_cond_init(&this->job_cv[i], NULL);
        if(ret_v){
            perror("Error initializing job condition variable");
            exit(1);
        }
    }
    this->numOfThreads=threads_num+1;
    this->thread_id=(pthread_t *)malloc(this->numOfThreads*sizeof(pthread_t));
    if(thread_id==NULL){
        cerr<<"Malloc fail!"<<endl;
        exit(1);
    }
    this->thread_jobs=(Job **)malloc((threads_num)*sizeof(Job *));

    if(thread_jobs==NULL){
        cerr<<"Malloc fail!"<<endl;
        exit(1);
    }

    //thread with id 0 is resonsble for giving jobs
    int id=0;
    ArgClass * args = new ArgClass(id, this);
    int ret_val=pthread_create(&thread_id[0],NULL,giveJobFunction,(void *)args);
    if(ret_val){
        perror("Error creating thread 0 (MASTER_THREAD)!");
        exit(1);
    }
    // other threads are workers
    for(int i=0;i<threads_num;i++){
        thread_jobs[i]=NULL;
        int id=i+1;
        //create i thread
        ArgClass * args = new ArgClass(id, this);
        int ret_val=pthread_create(&thread_id[i+1],NULL,doJobFunction,(void *)args);
        if(ret_val){
            perror("Error creating thread!");
            exit(1);
        }
    }

}

Scheduler::~Scheduler(){
    mutexDown(&this->work_condition_mutex);
    this->work_done = true;
    mutexUp(&this->work_condition_mutex);

    pthread_cond_signal(&this->queue_cv);
    if (pthread_join(this->thread_id[0], NULL)) {
        perror("pthread join error!");
    }

    if (pthread_mutex_destroy(&this->queue_mutex)) {
    perror("mutex destroy (~)");
    }
    if (pthread_cond_destroy(&this->queue_cv)) {
    perror("cond destroy (~)");
    }

    if (pthread_mutex_destroy(&this->threads_in_search_mutex)) {
    perror("mutex destroy (~)");
    }

    for (int i = 1; i < this->numOfThreads; ++i) {
        pthread_cond_signal(&this->job_cv[i-1]);
        if (pthread_join(this->thread_id[i], NULL)) {
            perror("pthread join error!");
        }
        if (pthread_cond_destroy(&this->job_cv[i-1])) {
        perror("cond destroy (~)");
        }
        if (pthread_mutex_destroy(&this->job_mutex[i-1])) {
        perror("mutex destroy (~)");
        }
        if (pthread_cond_destroy(&this->searches_cv[i-1])) {
        perror("cond destroy (~)");
        }
        if (pthread_mutex_destroy(&this->searches_mutex[i-1])) {
        perror("mutex destroy (~)");
        }
        if (pthread_mutex_destroy(&this->search_res_mutex[i-1])) {
        perror("mutex destroy (~)");
        }
    }

    if (pthread_mutex_destroy(&this->avail_worker_mutex)) {
    perror("mutex destroy (~)");
    }
    if (pthread_cond_destroy(&this->avail_worker_cv)) {
    perror("cond destroy (~)");
    }
    if (pthread_mutex_destroy(&this->pending_match_mutex)) {
    perror("mutex destroy (~)");
    }
    if (pthread_cond_destroy(&this->pending_match_cv)) {
    perror("cond destroy (~)");
    }

    if (pthread_mutex_destroy(&this->results_mutex)) {
    perror("mutex destroy (~)");
    }

    free(thread_jobs);
    free(searches_in_progress);
    free(searches_cv);
    free(searches_mutex);
    free(search_res_mutex);
    free(job_mutex);
    free(job_cv);
    free(thread_id);
    this->q.destroyData();
    delete pending_deactivate_queries;
}

SchedulerErrorCode Scheduler::addJob(Job * j){
    // check if no pending matches
    //aand if so deactivate all queries now that you can
                //TO DO
    //

    if(j->getId()==SEARCH){
        mutexDown(&this->pending_match_mutex);
        this->pending_match_jobs++;
        mutexUp(&this->pending_match_mutex);
        // TO DO : ADD TO JOB THE CURRENT STATE OF pending_deactivate_queries
        //SO THAT WHEN COMPUTING RESULT-> THE DEACTIVATED QUERIES SHHOULD BE REMOVED
        if(this->pending_deactivate_counter>0)
            j->addDeactivated(this->pending_deactivate_queries);
    }else if(j->getId()==DEACTIVATE){
        // increase pending deactivaates
        //and add query to be deactivated to Vector

        Query * q=j->getArgs()->getQuery();
        delete j;
        if(this->pending_match_jobs==0){
            q->deactivate();
            return S_SUCCESS;
        }
        this->pending_deactivate_counter++;
        pending_deactivate_queries->insert(q);
        return S_SUCCESS;
    }
    else if(j->getId()==INSERT){
        mutexDown(&this->pending_insert_mutex);
        this->pending_insert_jobs++;
        mutexUp(&this->pending_insert_mutex);
    }

    // acquired lock -> time to push job to queue
    // may check error
    // cout<<"ADDED JOB [MAIN_THREAD]"<<endl;
    //if job is of type SEARCH
    //then increase pending match jobs by 1
    mutexDown(&this->queue_mutex);
    q.push(j);
    mutexUp(&this->queue_mutex);
    // let master thread [0] know there is job available
    // cout<<"letting master thread [0] know that there is job for assginment"<<endl;

    pthread_cond_signal(&this->queue_cv);

    return S_SUCCESS;
}

// SchedulerErrorCode Scheduler::waitAllTasksFinish(){
//
// }


ArgClass::ArgClass(int id, Scheduler * sch) {
    this->id = id;
    this->sched = sch;
}

ArgClass::~ArgClass() {}

int ArgClass::getId() {
    return this->id;
}

Scheduler * ArgClass::getSched() {
    return this->sched;
}
