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
        pthread_t * thread_id;
        Job ** thread_jobs;//thread_jobs[i] for i'th thread (if null thread sleeps)

        int pending_match_jobs;
        pthread_mutex_t pending_match_mutex;
        pthread_cond_t pending_match_cv;

        pthread_mutex_t* job_mutex;// for job array
        pthread_cond_t* job_cv;

        pthread_mutex_t queue_mutex;
        pthread_cond_t queue_cv;

        pthread_mutex_t avail_worker_mutex;
        pthread_cond_t avail_worker_cv;

        pthread_mutex_t results_mutex;

        pthread_mutex_t work_condition_mutex;
        bool work_done;

        // for debugging purposes (stdout)
        pthread_mutex_t stdout_mutex;

        int assignJob();
    public:
        Scheduler(int);
        ~Scheduler();
        void waitPendingMatchesFinish();
        SchedulerErrorCode addJob(Job *);
        SchedulerErrorCode waitAllTasksFinish();
        SchedulerErrorCode doJob(Job *);
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
