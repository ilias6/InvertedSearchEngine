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

    for(int i=1;i<3;i++)
        this->indeces[i] = new Index*[MAX_DISTANCES+1];
    this->indeces[0][0]=new Index(MT_EXACT_MATCH,findNextPrime(Q/2));
    for(int i=0;i<MAX_DISTANCES;i++){
        this->indeces[1][i]=new Index(MT_EDIT_DIST,findNextPrime(Q/64));
        this->indeces[2][i]=new Index(MT_HAMMING_DIST,findNextPrime(Q/64));
    }

    this->queries = new Query*[Q];
    for (int i = 0; i < Q; ++i)
	   this->queries[i] = NULL;
}

IndexErrorCode CoreWrapper::addQuery(QueryID id, const char * str, MatchType type, unsigned int dist){
    if(this->queryCounter>this->Q){
        cerr<<"More queries than expected!"<<endl;
        exit(1);
    }
    int indx=this->queryCounter++;
    this->queries[indx]=new Query(id,str,type,dist);
    // insert to entry list
    Entry ** e_arr=NULL;
    EntryListErrorCode list_error_code;
    list_error_code=entryList->insert(*this->queries[indx],&e_arr);
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
    for (int i = 0; i < Q; ++i)
	   delete this->queries[i];
    delete[] this->queries;
}
