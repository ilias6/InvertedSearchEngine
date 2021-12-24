#include <pthread.h>
#include "queue.hpp" 


enum SchedulerErrorCode{S_SUCCESS, S_FAIL};

class Scheduler {
    private:
        Queue<Job *> q;
        int numOfThreads;
        Queue<pthread_t *> threadPool;
    public:
        Scheduler(int);
        ~Scheduler();
        SchedulerErrorCode addJob(Job *);
};
