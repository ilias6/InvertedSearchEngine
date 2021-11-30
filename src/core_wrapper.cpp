#include <cstdlib>
#include <iostream>
#include "../include/core_wrapper.hpp"
#include "../include/utils.hpp"


CoreWrapper::CoreWrapper(unsigned int Q) {
    this->Q = Q;
    this->queryCounter = 0;

    this->entryList = new EntryList(Q);

    this->indeces = new Index**[3];
    this->indeces[0] = new Index*;
    this->indeces[1] = new Index*[MAX_DISTANCES];
    this->indeces[2] = new Index*[MAX_DISTANCES];

    this->queries = new Query*[Q];
    for (int i = 0; i < Q; ++i)
	this->queries[i] = NULL;
}

void CoreWrapper::addToEntryList(MatchType type, unsigned int dist) {
}

void CoreWrapper::addQuery(QueryID id, const char * str, MatchType type, unsigned int dist) {
}


CoreWrapper::~CoreWrapper() {
    for (int i = 0; i < Q; ++i)
	delete this->queries[i];
    delete[] this->queries;
}
