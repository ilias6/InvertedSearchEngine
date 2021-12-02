#include <cstdlib>
#include <iostream>
#include "../include/core_wrapper.hpp"
#include "../include/utils.hpp"

#define APPROXIMATE_Q_NUM 1000 

CoreWrapper::CoreWrapper() {
    this->entryList = new EntryList(findNextPrime(APPROXIMATE_Q_NUM));

    this->indeces = new Index**[3];
    this->indeces[0] = new Index*;

    for(int i=1;i<3;i++)
        this->indeces[i] = new Index*[MAX_DISTANCES+1];
    this->indeces[0][0]=new Index(MT_EXACT_MATCH,findNextPrime(APPROXIMATE_Q_NUM/2));
    for(int i=0;i<MAX_DISTANCES;i++){
        this->indeces[1][i]=new Index(MT_EDIT_DIST,findNextPrime(APPROXIMATE_Q_NUM/64));
        this->indeces[2][i]=new Index(MT_HAMMING_DIST,findNextPrime(APPROXIMATE_Q_NUM/64));
    }

    this->queries = new Vector<Query *>();
    this->docs = new Vector<Document *>();
}

void CoreWrapper::deactivateQuery(QueryID id) {
    Query * qPtr = biSearchQuery(this->queries, id);
    if (qPtr != NULL)
	qPtr->deactivate();
}

IndexErrorCode CoreWrapper::addQuery(QueryID id, const char * str, MatchType type, unsigned int dist){
    Query * q = new Query(id,str,type,dist);
    this->queries->insert(q);

    // insert to entry list
    Entry ** e_arr=NULL;
    EntryListErrorCode list_error_code;
    list_error_code=entryList->insert(*q, &e_arr);
    if(list_error_code==E_L_FAIL)
        return I_FAIL;
    IndexErrorCode error_code;
    switch(type){
        case MT_EXACT_MATCH:
            error_code=indeces[0][0]->insert(e_arr);
            break;
        case MT_EDIT_DIST:
            error_code=indeces[1][dist]->insert(e_arr);
            break;
        case MT_HAMMING_DIST:
            error_code=indeces[2][dist]->insert(e_arr);
            break;
    }
    // delete entry arr
    for(int i=0;e_arr[i]!=NULL;i++)
        delete e_arr[i];
    delete[] e_arr;
    return error_code;
}


CoreWrapper::~CoreWrapper() {
    delete this->entryList;
    delete this->queries;
    delete this->docs;

    delete this->indeces[0][0];
    delete this->indeces[0];

    for(int i=1;i<3;i++) {
	for(int i=0;i<MAX_DISTANCES;i++){
	    delete this->indeces[1][i];
	    delete this->indeces[2][i];
	}
        delete[] this->indeces[i];
    }
  
    delete[] this->indeces;
}
