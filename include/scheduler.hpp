#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__
#include <pthread.h>
#include "queue.hpp"
#include "job.hpp"




enum SchedulerErrorCode{S_SUCCESS, S_FAIL};

class Scheduler {
    private:
        Queue<Job *> q;
        int numOfThreads;
        int max_docs_in_par;
        pthread_t * thread_id;
        Job ** thread_jobs;//thread_jobs[i] for i'th thread (if null thread sleeps)

        int pending_match_jobs;
        pthread_mutex_t pending_match_mutex;
        pthread_cond_t pending_match_cv;

        int pending_insert_jobs;
        pthread_mutex_t pending_insert_mutex;
        pthread_cond_t pending_insert_cv;

        int pending_deactivate_counter;
        Vector<Query *> *pending_deactivate_queries;

        pthread_mutex_t* job_mutex;// for job array
        pthread_cond_t* job_cv;

        pthread_mutex_t queue_mutex;
        pthread_cond_t queue_cv;

        int avail_workers_num;
        pthread_mutex_t avail_worker_mutex;
        pthread_cond_t avail_worker_cv;

        pthread_mutex_t results_mutex;

        pthread_mutex_t work_condition_mutex;
        bool work_done;

        pthread_cond_t avail_res_cv;

        int threads_in_search;
        pthread_mutex_t threads_in_search_mutex;

        int * searches_in_progress;
        pthread_cond_t * searches_cv;
        pthread_mutex_t * searches_mutex;
        pthread_mutex_t * search_res_mutex;

        pthread_mutex_t  entryList_mutex;
        pthread_mutex_t  hash_mutex;

        // for debugging purposes (stdout)
        pthread_mutex_t stdout_mutex;

        int assignJob();
    public:
        Scheduler(int);
        ~Scheduler();
        void waitPendingMatchesFinish();
        void waitPendingInsertionsFinish();
        void waitForAvailRes();
        void resMutexUp();
        void resMutexDown();
        SchedulerErrorCode addJob(Job *);
        SchedulerErrorCode waitAllTasksFinish();
        SchedulerErrorCode doJob(Job *, int);
        friend void * doJobFunction(void *);
        friend void * giveJobFunction(void *);
        friend void * waitForJob(void *);

};

class ArgClass {
    private:
        int id;
        Scheduler * sched;
    public:
       ArgClass(int, Scheduler *);
       ~ArgClass();
       int getId();
       Scheduler * getSched();
};

#endif
