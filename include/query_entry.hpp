#ifndef __QUERY_ENTRY_HPP__
#define __QUERY_ENTRY_HPP__

#include <iostream>
#include "./core.h"
#include "./query.hpp"
using namespace std;

class QueryEntry {
    private:
        int index;
        Query * queryPtr;
    public:
        QueryEntry(int, Query *);
        ~QueryEntry();
        int getIndex();
        Query * getQuery();
};

#endif
