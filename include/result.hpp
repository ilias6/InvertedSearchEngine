#ifndef __RESULT_HPP__
#define __RESULT_HPP__
#include "query.hpp"
#include "vector.hpp"
#include "document.hpp"
#include "hash_table.hpp"

enum ResultErrorCode {R_SUCCESS,R_FAIL};
class Result{
    private:
        DocID docId;
        Vector<Query *> queries;//
        bool ** wordFlags;
        HashTable ** wordIndices;
        int getIdx(int, Word *);
    public:
        Result(DocID,Vector<Query *> &);
        ~Result();
        ResultErrorCode increaseCounter(QueryID, Word * w);
        ResultErrorCode fetch(DocID *,unsigned int *,QueryID **);
        DocID getId();
        void print();
};


#endif
