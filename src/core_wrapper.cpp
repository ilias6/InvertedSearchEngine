#include <cstdlib>
#include <iostream>
#include "../include/core_wrapper.hpp"
#include "../include/utils.hpp"
#include "../include/result.hpp"

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
    this->docs = new Queue<Document *>();
    this->results = new Queue<Result *>();
}

CoreWrapperErrorCode CoreWrapper::deactivateQuery(QueryID id) {
    Query * qPtr = biSearchQuery(this->queries, id);
    if (qPtr != NULL){
        qPtr->deactivate();
        return C_W_SUCCESS;
    }
    return C_W_FAIL;
}

CoreWrapperErrorCode CoreWrapper::addQuery(QueryID id, const char * str, MatchType type, unsigned int dist){
    Query * q = new Query(id,str,type,dist);
    this->queries->insertSorted(q, q->getId());
    // insert to entry list
    Entry ** e_arr=NULL;
    EntryListErrorCode list_error_code;
    list_error_code=entryList->insert(*q, &e_arr);
    if(list_error_code!=E_L_SUCCESS)
        return C_W_FAIL;
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
    delete[] e_arr;
    if(error_code!=I_SUCCESS)
        return C_W_FAIL;
    return C_W_SUCCESS;
}

CoreWrapperErrorCode CoreWrapper::addDocument(DocID doc_id,const char * str){
    //master thread construct doc and add to pool
    Document * doc=new Document(doc_id,str);
    //push doc to queue (pool) and check if successfull
    if(this->docs->push(doc)!=Q_SUCCESS){
        delete doc;
        return C_W_FAIL;
    }
    return C_W_SUCCESS;
}

Document * CoreWrapper::pullDocument(){
    try{
        return this->docs->pop();
    }catch(invalid_argument& ia){
        return NULL;
    }
}

Result * CoreWrapper::matchDocument(Document * doc){
    int words_in_doc=doc->getWordsInDoc();
    Result * res=new Result(doc->getId(),*this->queries);
    for(int i=0;i<words_in_doc;i++){
        Word *w=doc->getWord(i);
        this->searchWordInIndeces(w,res);
    }
    return res;
}

void CoreWrapper::searchWordInIndeces(Word *w,Result *res){
    //first search exact match and increase counters for exact match in res
    List<Entry *> entry_res=indeces[0][0]->search(w);
    increaseCounter(entry_res,res,MT_EXACT_MATCH);

    // for edit dist
    for(int j=0;j<MAX_DISTANCES;j++){
        List<Entry *> e_res=indeces[1][j]->search(w);
        increaseCounter(entry_res,res,MT_EDIT_DIST,j);
    }

    // for hamming dist
    for(int j=0;j<MAX_DISTANCES;j++){
        List<Entry *> e_res=indeces[2][j]->search(w);
        increaseCounter(entry_res,res,MT_HAMMING_DIST,j);
    }
}

void CoreWrapper::increaseCounter(List<Entry *>& e_list,Result * res,MatchType mt,unsigned int dist){
    int len=e_list.getLen();
    for(int i=0;i<len;i++){
        Entry * e=e_list.getItem(i);
        List<PayloadEntry> &p_list=e->getPayload();
        int plen=p_list.getLen();
        for(int j=0;j<plen;j++){
            PayloadEntry &pE=p_list.getItem(j);
            bool active=pE.getActive();
            if(active){
                QueryID id=pE.getId();
                MatchType tp=pE.getType();
                unsigned int d=pE.getDist();
                if(mt==tp && d==dist)
                    res->increaseCounter(id);
            }
        }
    }
}


CoreWrapperErrorCode CoreWrapper::addResult(Result * res){
    //all threads push results to queue (pool)
    // SEMAPHORES TO BE IMPLMENTED
    if(this->results->push(res)!=Q_SUCCESS){
        delete res;
        return C_W_FAIL;
    }
    return C_W_SUCCESS;

}
Result * CoreWrapper::pullResult(){
    try{
        return this->results->pop();
    }catch(invalid_argument& ia){
        return NULL;
    }
}

CoreWrapper::~CoreWrapper() {
    delete this->entryList;
    this->queries->destroyData();
    delete this->queries;
    this->docs->destroyData();
    delete this->docs;
    this->results->destroyData();
    delete this->results;

    delete this->indeces[0][0];
    delete this->indeces[0];

    for(int i=1;i<3;i++) {
	for(int j=0;j<MAX_DISTANCES;j++)
	    delete this->indeces[i][j];
        delete[] this->indeces[i];
    }

    delete[] this->indeces;
}
