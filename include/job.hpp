#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <cstdlib>
#include "document.hpp"

enum JobErrorCode{J_SUCCESS, J_FAIL};
enum JobId{SEARCH,INSERT,DEACTIVATE,EXACTSEARCH, EDITSEARCH, HAMMINGSEARCH};
enum Status{PENDING,IN_PROGRESS,DONE};
class Args {
    public:
        Args();
        ~Args();
        Document * getDocument();
        void print();
        QueryID getQueryId();

};

class Job {
    private:
        enum Status status;
        JobId id;
        Args * args;
    public:
        Job(JobId, Args *);
        void setStatus(enum Status);
        JobId getId();
        Args * getArgs();
        void print();
        ~Job();
};


class SearchArgs:public Args {
    private:
        Document * doc;
    public:
        SearchArgs(Document *);
        ~SearchArgs();
        virtual Document * getDocument();
        virtual void print();
};

class DeactivateArgs:public Args {
    private:
        QueryID id;
    public:
        DeactivateArgs();
        ~DeactivateArgs();
        virtual QueryID getQueryId();
};

// class SearchArgs {
//
// };
//
// class SearchArgs {
//
// };

#endif
