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

        pthread_mutex_t* job_mutex;// for job array
        pthread_cond_t* job_cv;

        pthread_mutex_t queue_mutex;
        pthread_cond_t queue_cv;
        // for debugging purposes (stdout)
        pthread_mutex_t stdout_mutex;
        int assignJob(Job *);
    public:
        Scheduler(int);
        ~Scheduler();
        SchedulerErrorCode addJob(Job *);
        SchedulerErrorCode waitAllTasksFinish();
        int assignJob();
        void * doJobFunction(void *);
        void * giveJobFunction(void *);

};

#endif
