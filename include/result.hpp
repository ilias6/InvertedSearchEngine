#ifndef __RESULT_HPP__
#define __RESULT_HPP__
#include "query.hpp"
#include "vector.hpp"
#include "document.hpp"
#include "hash_table.hpp"
#include <pthread.h>

enum ResultErrorCode {R_SUCCESS,R_FAIL};
class Result{
    private:
        DocID docId;
        Vector<Query *> queries;
        pthread_mutex_t ** mutexes;
        bool ** wordFlags;
    public:
        Result(DocID,Vector<Query *> &);
        ~Result();
        ResultErrorCode increaseCounter(QueryID, Word * w);
        ResultErrorCode fetch(DocID *,unsigned int *,QueryID **);
        ResultErrorCode resetCounters(QueryID);
        DocID getId();
        void print();
};


#endif
