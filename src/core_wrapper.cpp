#include <cstdlib>
#include <iostream>
#include "../include/core_wrapper.hpp"
#include "../include/utils.hpp"


CoreWrapper::CoreWrapper(unsigned int Q) {
    this->Q = Q;
    this->queryCounter = 0;

    this->entryLists = new EntryList**[3];
    this->entryLists[0] = new EntryList*;
    this->entryLists[0][0] = new EntryList(Q/3);
    this->entryLists[1] = new EntryList*[MAX_DISTANCES];
    this->entryLists[2] = new EntryList*[MAX_DISTANCES];
    for (int i = 0; i < MAX_DISTANCES; ++i)
	for (int j = 1; j < 3; ++j)
	    this->entryLists[j][i] = new EntryList(findNextPrime((Q/3)/MAX_DISTANCES));

    this->indeces = new Index**[3];
    this->indeces[0] = new Index*;
    this->indeces[1] = new Index*[MAX_DISTANCES];
    this->indeces[2] = new Index*[MAX_DISTANCES];

    this->queries = new Query*[Q];
    for (int i = 0; i < Q; ++i)
	this->queries[i] = NULL;
}

void CoreWrapper::addToEntryList(MatchType type, unsigned int dist) {
    if (type == MT_EXACT_MATCH) {
	this->entryLists[0][0]->insert(*this->queries[this->queryCounter]);
    }
    else if (type == MT_HAMMING_DIST) {
	this->entryLists[1][dist]->insert(*this->queries[this->queryCounter]);
    }
    else {
	this->entryLists[2][dist]->insert(*this->queries[this->queryCounter]);
    }
}

void CoreWrapper::addQuery(QueryID id, const char * str, MatchType type, unsigned int dist) {
    this->queries[this->queryCounter] = new Query(id, str, type, dist);
    this->addToEntryList(type, dist);
    this->queryCounter++;
}

void CoreWrapper::makeIndeces() {
    this->indeces[0][0] = new Index(*this->entryLists[0][0], MT_EXACT_MATCH);

    for (int i = 0; i < MAX_DISTANCES; ++i) {
	this->indeces[1][i] = new Index(*this->entryLists[1][i], MT_HAMMING_DIST);
	this->indeces[2][i] = new Index(*this->entryLists[2][i], MT_EDIT_DIST);
    }
}

CoreWrapper::~CoreWrapper() {
    for (int i = 0; i < Q; ++i)
	delete this->queries[i];
    delete[] this->queries;

    delete this->indeces[0][0];
    delete this->indeces[0];
    for (int i = 1; i < 3; ++i) {
	for (int j = 0; j < MAX_DISTANCES; ++j)
	    delete this->indeces[i][j];
	delete[] this->indeces[i];
    }
    delete[] this->indeces;

    delete *this->entryLists[0];
    delete this->entryLists[0];
    for (int i = 1; i < 3; ++i) {
	for (int j = 0; j < MAX_DISTANCES; ++j)
	    delete this->entryLists[i][j];
	delete[] this->entryLists[i];
    }
    delete[] this->entryLists;
}
