#include "../include/scheduler.hpp"
#include <iostream>
#include <errno.h>
#include <cstdlib>
#include <pthread.h>

void * Scheduler::doJobFunction(void *void_argc){
    int t_id=*(int *)void_argc;
    int t_indx=t_id-1;
    //t_id is used as index in thread_jobs array
    //if thread_jobs[i]==NULL
    //then thread sleeps until a job is assigned to it

    // cout<<"Hello i'm : "<<t_id<<endl;
    // acquire lock mutex
    while(1){
        if(pthread_mutex_lock(&this->job_mutex[t_indx])){
            cerr<<"ID "<<t_id<<endl;
            perror("job_mutex lock");
            pthread_exit(NULL);
        }
        while(this->thread_jobs[t_id]==NULL){
            //wait on condition variable if thread has no job
            pthread_cond_wait(&this->job_cv[t_indx],&this->job_mutex[t_indx]);
        }
        //if there is jobs for thread do stuff
        Job * myJob=this->thread_jobs[t_indx];
        pthread_mutex_lock(&this->stdout_mutex);
        cout<<"I'm "<<t_id<<" and got a job:"<<endl;
        // myJob->print();
        pthread_mutex_unlock(&this->stdout_mutex);


        this->thread_jobs[t_id]=NULL;
        /* signal master that i am available
        pthread_cond_signal(&this->queue_cv);
        */
        if(pthread_mutex_unlock(&this->job_mutex[t_indx])){
            cerr<<"ID "<<t_id<<endl;
            perror("job_mutex unlock");
            pthread_exit(NULL);
        }
    }
    free((int *)void_argc);
    return NULL;
}

int Scheduler::assignJob() {
    for (int i = 0; i < this->numOfThreads-1; ++i) {
        if (this->thread_jobs[i] != NULL) {
            if(pthread_mutex_lock(&this->job_mutex[i])){
                perror("job_mutex lock (assign)");
                pthread_exit(NULL);
            }
            Job * job = this->q.pop();
            this->thread_jobs[i] = job;
            if(pthread_mutex_unlock(&this->job_mutex[i])){
                perror("job_mutex unlock (assign)");
                pthread_exit(NULL);
            return i;
            }
        }
    }
    return -1;
}

void * Scheduler::giveJobFunction(void *void_argc){
    while(1) {
        if(pthread_mutex_lock(&this->queue_mutex)){
            perror("queue_mutex lock");
            pthread_exit(NULL);
        }

        while(this->q.getList().getLen() == 0)
            pthread_cond_wait(&this->queue_cv, &this->queue_mutex);
        int t_id = assignJob();
        if (t_id != -1) {
            if (pthread_cond_signal(&this->job_cv[t_id])) {
                perror("cond_signal failed (giveJobFunction)");
                pthread_exit(NULL);
            }
        }
        if(pthread_mutex_unlock(&this->queue_mutex)) {
            perror("queue_mutex unlock");
            pthread_exit(NULL);
        }
    }
}

Scheduler::Scheduler(int threads_num){
    //threads_num workers + 1 the master thread
    this->job_mutex=(pthread_mutex_t *)malloc((threads_num)*sizeof(pthread_mutex_t));
    this->stdout_mutex=PTHREAD_MUTEX_INITIALIZER;
    this->queue_mutex=PTHREAD_MUTEX_INITIALIZER;

    if(this->job_mutex==NULL){
        perror("Malloc job mutex arr failed");
        exit(1);
    }
    this->job_cv=(pthread_cond_t *)malloc((threads_num)*sizeof(pthread_cond_t));
    if(this->job_cv==NULL){
        perror("Malloc condition var arr failed");
        exit(1);
    }
    int ret_v = pthread_cond_init(&this->queue_cv, NULL);
    if(ret_v){
        perror("Error initializing job condition variable");
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
    this->thread_jobs=(Job **)malloc(threads_num*sizeof(Job *));

    if(thread_jobs==NULL){
        cerr<<"Malloc fail!"<<endl;
        exit(1);
    }

    //thread with id 0 is resonsble for giving jobs
    int *id=(int *)malloc(sizeof(int));
    *id=0;
    int ret_val=pthread_create(&thread_id[0],NULL,this->giveJobFunction,(void *)id);
    if(ret_val){
        perror("Error creating thread 0 (MASTER_THREAD)!");
        exit(1);
    }
    // other threads are workers
    for(int i=0;i<threads_num;i++){
        thread_jobs[i]=NULL;
        id=(int *)malloc(sizeof(int));
        *id=i+1;
    //create i thread
        int ret_val=pthread_create(&thread_id[i],NULL,this->doJobFunction,(void *)id);
        if(ret_val){
            perror("Error creating thread!");
            exit(1);
        }
    }


}
Scheduler::~Scheduler(){
;
}
SchedulerErrorCode Scheduler::addJob(Job * j){
    if(pthread_mutex_lock(&this->queue_mutex)){
        perror("Error acquiring lock to push job to Queue (MAIN_THREAD)!");
        return S_FAIL;
    }
    // acquired lock -> time to push job to queue
    // may check error
    q.push(j);
    if(pthread_mutex_unlock(&this->queue_mutex)){
        perror("Error unlocking job mutex (MAIN_THREAD)!");
        return S_FAIL;
    }
    return S_SUCCESS;
}
SchedulerErrorCode Scheduler::waitAllTasksFinish(){

}
