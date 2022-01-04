#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <cstdlib>
#include "document.hpp"

enum JobErrorCode{J_SUCCESS, J_FAIL};
enum JobId{SEARCH, EXACTSEARCH, EDITSEARCH, HAMMINGSEARCH};

class SearchArgs {
    private:
        Document * doc;
    public:
        SearchArgs(Document *);
        ~SearchArgs();
        Document * getDocument();
        void print();
};

class Job {
    private:
        JobId id;
        SearchArgs * searchArgs;
    public:
        Job(JobId, SearchArgs *);
        JobId getId();
        SearchArgs * getSearchArgs();
        void print();
        ~Job();
};


// class SearchArgs {
//
// };
//
// class SearchArgs {
//
// };
//
// class SearchArgs {
//
// };
//
// class SearchArgs {
//
// };

#endif
