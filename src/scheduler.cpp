#include "../include/scheduler.hpp"
#include "../include/core_wrapper.hpp"
#include "../include/document.hpp"
#include <iostream>
#include <errno.h>
#include <cstdlib>
#include <pthread.h>

#include <unistd.h>

extern CoreWrapper * CW;

void Scheduler::waitPendingMatchesFinish(void){
    pthread_mutex_lock(&this->pending_match_mutex);

    while(pending_match_jobs)
        pthread_cond_wait(&this->pending_match_cv,&this->pending_match_mutex);

    pthread_mutex_unlock(&this->pending_match_mutex);
    return ;
}

bool checkCondition(pthread_mutex_t * stdout_mutex,pthread_mutex_t * mutex, bool * condition) {
    bool cond = false;
    // pthread_mutex_lock(stdout_mutex);
    // cout<<"check"<<endl;
    // pthread_mutex_unlock(stdout_mutex);
    if(pthread_mutex_lock(mutex)){
        perror("mutex lock (checkCondition)");
        pthread_exit(NULL);
    }
    if (*condition)
        cond = true;
    if(pthread_mutex_unlock(mutex)){
        perror("mutex unlock (checkCondition)");
        pthread_exit(NULL);
    }
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
        if(pthread_mutex_lock(&sched->job_mutex[t_indx])){
            cerr<<"ID "<<t_id<<endl;
            perror("job_mutex lock");
            pthread_exit(NULL);
        }
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
                if(pthread_mutex_unlock(&sched->job_mutex[t_indx])){
                    cerr<<"ID "<<t_id<<endl;
                    perror("job_mutex unlock");
                    pthread_exit(NULL);
                }
                delete args;
                return NULL;
            }
            pthread_cond_wait(&sched->job_cv[t_indx],&sched->job_mutex[t_indx]);
            // if all jobs are done
            if (checkCondition(&sched->stdout_mutex,&sched->work_condition_mutex, &sched->work_done)){ 
                // pthread_mutex_lock(&sched->stdout_mutex);
                // cout<<"I'm "<<t_id<<" and going to exit 2:"<<endl;
                // pthread_mutex_unlock(&sched->stdout_mutex);
                if(pthread_mutex_unlock(&sched->job_mutex[t_indx])){
                    cerr<<"ID "<<t_id<<endl;
                    perror("job_mutex unlock");
                    pthread_exit(NULL);
                }
                delete args;
                return NULL;
            }
        }
        //if there are jobs for thread do stuff
        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"going to take job"<<endl;
        // pthread_mutex_unlock(&sched->stdout_mutex);
        Job * myJob=sched->thread_jobs[t_indx];
        if(pthread_mutex_unlock(&sched->job_mutex[t_indx])){
            cerr<<"ID "<<t_id<<endl;
            perror("job_mutex lock");
            pthread_exit(NULL);
        }
        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"took job"<<endl;
        // pthread_mutex_unlock(&sched->stdout_mutex);

        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"I'm "<<t_id<<" and got a job:\n\n";
        // pthread_mutex_unlock(&sched->stdout_mutex);

        if (sched->doJob(myJob) != S_SUCCESS){
            return new SchedulerErrorCode(S_FAIL);
        }
        // pthread_mutex_lock(&sched->stdout_mutex);
        // cout<<"I'm "<<t_id<<" and done:\n\n";
        // pthread_mutex_unlock(&sched->stdout_mutex);
        delete myJob;

        if(pthread_mutex_lock(&sched->job_mutex[t_indx])){
            cerr<<"ID "<<t_id<<endl;
            perror("job_mutex lock");
            pthread_exit(NULL);
        }
        sched->thread_jobs[t_indx]=NULL;
        if(pthread_mutex_unlock(&sched->job_mutex[t_indx])){
            cerr<<"ID "<<t_id<<endl;
            perror("job_mutex lock");
            pthread_exit(NULL);
        }
        /* signal master that i am available
        */
        pthread_cond_signal(&sched->avail_worker_cv);
    }
}

SchedulerErrorCode Scheduler::doJob(Job * job){
    JobId id = job->getId();
    switch(id){
        case SEARCH:
            {
                Args * searchArgs = job->getArgs();
                Document * doc = searchArgs->getDocument();

        pthread_mutex_lock(&this->stdout_mutex);
        cout<<" Job "<<doc->getId()<<endl;
        pthread_mutex_unlock(&this->stdout_mutex);
                int words_in_doc=doc->getWordsInDoc();
                Result * res=new Result(doc->getId(),*CW->queries);

                for(int i=0;i<words_in_doc;i++){
                    Word *w=doc->getWord(i);
                    CW->searchWordInIndeces(w,res);
                }


                if(pthread_mutex_lock(&this->results_mutex)){
                    perror("results_mutex lock (doJob)");
                    pthread_exit(NULL);
                }
                if(CW->addResult(res)==C_W_FAIL){
                    delete res;
                    delete doc;
                    cerr<<"Failed adding result to result_pool ! [DocID "<<doc->getId()<<"] "<<endl;
                    exit(1);
                }
                if(pthread_mutex_unlock(&this->results_mutex)){
                    perror("results_mutex unlock (doJob)");
                    pthread_exit(NULL);
                }
                // decrease pending_match_jobs
                pthread_mutex_lock(&this->pending_match_mutex);
                this->pending_match_jobs--;
                if(this->pending_match_jobs==0)
                    pthread_cond_signal(&pending_match_cv);
                pthread_mutex_unlock(&this->pending_match_mutex);
        pthread_mutex_lock(&this->stdout_mutex);
        cout<<"assigned Job "<<doc->getId()<<endl;
        pthread_mutex_unlock(&this->stdout_mutex);
            }
            break;

        case EXACTSEARCH:
            break;
        case EDITSEARCH:
            break;
        case HAMMINGSEARCH:
            break;
        default:
            break;
    }
    return S_SUCCESS;
}

int Scheduler::assignJob() {
    while (1) {
        for (int i = 0; i < this->numOfThreads-1; ++i) {
            if(pthread_mutex_lock(&this->job_mutex[i])){
                perror("job_mutex lock (assignJob)");
                pthread_exit(NULL);
            }
            if (this->thread_jobs[i] == NULL) {
                // pthread_mutex_lock(&this->stdout_mutex);
                // cout<<i<<" Before pop: "<<this->q.getList().getLen()<<endl;
                // pthread_mutex_unlock(&this->stdout_mutex);
                if(pthread_mutex_lock(&this->queue_mutex)){
                    perror("queue_mutex lock");
                    pthread_exit(NULL);
                }
                Job * job = this->q.pop();
                if(pthread_mutex_unlock(&this->queue_mutex)){
                    perror("queue_mutex lock");
                    pthread_exit(NULL);
                }
                // pthread_mutex_lock(&this->stdout_mutex);
                // cout<<i<<" After pop "<<this->q.getList().getLen()<<endl;
                // pthread_mutex_unlock(&this->stdout_mutex);

                this->thread_jobs[i] = job;
                if(pthread_mutex_unlock(&this->job_mutex[i])){
                    perror("job_mutex unlock (assign)");
                    pthread_exit(NULL);
                }
                if (pthread_cond_signal(&this->job_cv[i])) {
                    perror("cond_signal failed (giveJobFunction)");
                    pthread_exit(NULL);
                }
                // pthread_mutex_lock(&sched->stdout_mutex);
                // cout<<"signaled : "<<avail_t_id+1<<" to get job"<<endl;
                // pthread_mutex_unlock(&sched->stdout_mutex);
                return 0; 
            }
            if(pthread_mutex_unlock(&this->job_mutex[i])){
                perror("job_mutex unlock (assignJob)");
                pthread_exit(NULL);
            }
        }
        // pthread_mutex_lock(&this->stdout_mutex);
        // cout<<"all unavailable"<<endl;
        // pthread_mutex_unlock(&this->stdout_mutex);
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

        if(pthread_mutex_lock(&sched->queue_mutex)){
            perror("queue_mutex lock");
            pthread_exit(NULL);
        }
        while(sched->q.getList().getLen() == 0){
            // pthread_mutex_lock(&sched->stdout_mutex);
            // cout<<"\n\tI'M THREAD 0 AND WAIT TO GET A JOB TO ASSIGN"<<endl;
            // pthread_mutex_unlock(&sched->stdout_mutex);

            if (checkCondition(&sched->stdout_mutex,&sched->work_condition_mutex, &sched->work_done)) {
                if(pthread_mutex_unlock(&sched->queue_mutex)) {
                    perror("queue_mutex unlock");
                    pthread_exit(NULL);
                }
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
                if(pthread_mutex_unlock(&sched->queue_mutex)) {
                    perror("queue_mutex unlock");
                    pthread_exit(NULL);
                }
                delete args;
                return NULL;
            }
        }
        if(pthread_mutex_unlock(&sched->queue_mutex)) {
            perror("queue_mutex unlock");
            pthread_exit(NULL);
        }
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
    this->job_mutex=(pthread_mutex_t *)malloc((threads_num)*sizeof(pthread_mutex_t));
    this->stdout_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->queue_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->avail_worker_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->results_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->pending_match_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->work_condition_mutex=PTHREAD_MUTEX_INITIALIZER;

    this->pending_match_jobs=0;
    this->work_done = false;

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
    ret_v = pthread_cond_init(&this->queue_cv, NULL);
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
        this->job_mutex[i]=PTHREAD_MUTEX_INITIALIZER;
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
    cout << "TELIWSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\nE\nE\nE\nE\nE\nE\n";
    if(pthread_mutex_lock(&this->work_condition_mutex)){
        perror("work_condition_mutex lock (~)");
    }
    this->work_done = true;
    if(pthread_mutex_unlock(&this->work_condition_mutex)){
        perror("work_condition_mutex lock (~)");
    }

    pthread_cond_signal(&this->queue_cv);
    if (pthread_join(this->thread_id[0], NULL)) {
        perror("pthread join error!");
    }

    // if (pthread_mutex_destroy(&this->queue_mutex)==EBUSY) {
    // perror("mutex destroy (~)");
    // }
    // if (pthread_cond_destroy(&this->queue_cv)==EBUSY) {
    // perror("cond destroy (~)");
    // }

    for (int i = 1; i < this->numOfThreads; ++i) {
        pthread_cond_signal(&this->job_cv[i-1]);
        if (pthread_join(this->thread_id[i], NULL)) {
            perror("pthread join error!");
        }
        // if (pthread_cond_destroy(&this->job_cv[i-1])==EBUSY) {
        // perror("cond destroy (~)");
        // }
        // if (pthread_mutex_destroy(&this->job_mutex[i-1])==EBUSY) {
        // perror("mutex destroy (~)");
        // }
    }

    // if (pthread_mutex_destroy(&this->avail_worker_mutex)==EBUSY) {
    // perror("mutex destroy (~)");
    // }
    // if (pthread_cond_destroy(&this->avail_worker_cv)==EBUSY) {
    // perror("cond destroy (~)");
    // }
    // if (pthread_mutex_destroy(&this->pending_match_mutex)==EBUSY) {
    // perror("mutex destroy (~)");
    // }
    // if (pthread_cond_destroy(&this->pending_match_cv)==EBUSY) {
    // perror("cond destroy (~)");
    // }
    // 
    // if (pthread_mutex_destroy(&this->results_mutex)==EBUSY) {
    // perror("mutex destroy (~)");
    // }

    // free(thread_jobs);
    // free(job_mutex);
    // free(job_cv);
    // free(thread_id);
}

SchedulerErrorCode Scheduler::addJob(Job * j){
    if(j->getId()==SEARCH){
        pthread_mutex_lock(&this->pending_match_mutex);
        this->pending_match_jobs++;
        pthread_mutex_unlock(&this->pending_match_mutex);

    }

    if(pthread_mutex_lock(&this->queue_mutex)){
        perror("Error acquiring lock to push job to Queue (MAIN_THREAD)!");
        return S_FAIL;
    }
    // acquired lock -> time to push job to queue
    // may check error
    // cout<<"ADDED JOB [MAIN_THREAD]"<<endl;
    //if job is of type SEARCH
    //then increase pending match jobs by 1
    q.push(j);
    // let master thread [0] know there is job available
    // cout<<"letting master thread [0] know that there is job for assginment"<<endl;
    if(pthread_mutex_unlock(&this->queue_mutex)){
        perror("Error unlocking job mutex (MAIN_THREAD)!");
        return S_FAIL;
    }

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
