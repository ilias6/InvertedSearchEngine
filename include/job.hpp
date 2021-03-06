#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <cstdlib>
#include "document.hpp"
#include "entry.hpp"
#include "word.hpp"
#include "result.hpp"

enum JobErrorCode{J_SUCCESS, J_FAIL};
enum JobId{SEARCH,INSERT,DEACTIVATE,SEARCH_METHOD};
enum Status{PENDING,IN_PROGRESS,DONE};

class Args {
    public:
        Args();
        virtual ~Args();
        virtual Document * getDocument();
        virtual void print();
        // virtual QueryID getQueryId();
        virtual Result * getRes();
        virtual int getType();
        virtual int getDist();
        virtual int getParentIndex();
        virtual Query * getQuery();

};

class Job {
    private:
        enum Status status;
        JobId id;
        Args * args;
        Vector<Query *> * deactivated;
    public:
        Job(JobId, Args *);
        void setStatus(enum Status);
        Status getStatus();
        JobId getId();
        Args * getArgs();
        void print();
        void addDeactivated(Vector<Query *> *);
        Vector<Query *> * getDeactivated();
        ~Job();
};


class SearchArgs:public Args {
    private:
        Document * doc;
    public:
        SearchArgs(Document *);
        virtual ~SearchArgs();
        Document * getDocument();
        void print();
};

class SearchMethodArgs:public Args {
    private:
        Result * res;
        Document * doc;
        int typeIndex;
        int distIndex;
        int threadIndex;
    public:
        SearchMethodArgs(Result *, Document *, int, int, int);
        ~SearchMethodArgs();
        Result * getRes();
        Document * getDocument();
        int getType();
        int getDist();
        int getParentIndex();
};

class DeactivateArgs:public Args {
    private:
        Query *qPtr;
    public:
        DeactivateArgs(Query *q);
        ~DeactivateArgs();
        Query * getQuery();
};

class InsertArgs:public Args {
    private:
        Query *qPtr;
    public:
        InsertArgs(Query *q);
        ~InsertArgs();
        Query * getQuery();
};
//
// class SearchArgs {
//
// };

#endif
