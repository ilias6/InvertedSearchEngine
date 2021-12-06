#ifndef __RESULT_HPP__
#define __RESULT_HPP__
#include "query.hpp"
#include "vector.hpp"
#include "document.hpp"
enum ResultErrorCode {R_SUCCESS,R_EMPTY,R_FAIL};
class Result{
    private:
        DocID docId;
        Vector<Query *> queries;//
        int * counters;//               1-1 match
	bool ** wordFlags;
    public:
        Result(DocID,Vector<Query *> &);
        ~Result();
        ResultErrorCode increaseCounter(QueryID, Word * w);
        ResultErrorCode fetch(DocID *,unsigned int *,QueryID **);
	DocID getId();
        void print();
};


#endif
