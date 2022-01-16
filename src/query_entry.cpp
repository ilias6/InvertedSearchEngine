#include <iostream>
#include <cstring>
#include "../include/query_entry.hpp"

using namespace std;

QueryEntry::QueryEntry(int id, Query *q){
    this->index=id;
    this->queryPtr=q;
}

QueryEntry::~QueryEntry() {}

int QueryEntry::getIndex() {
    return this->index;
}

Query * QueryEntry::getQuery() {
    return this->queryPtr;
}
