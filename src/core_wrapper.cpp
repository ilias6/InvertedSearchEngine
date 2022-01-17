#include <cstdlib>
#include <iostream>
#include "../include/core_wrapper.hpp"
#include "../include/utils.hpp"

#include <unistd.h>

#define APPROXIMATE_Q_NUM 10000

CoreWrapper::CoreWrapper() {
    this->scheduler = new Scheduler(16);

    this->entryList = new EntryList(findNextPrime(APPROXIMATE_Q_NUM));

    this->indeces = new Index**[3];
    this->indeces[0] = new Index*;

    for(int i=1;i<3;i++)
        this->indeces[i] = new Index*[MAX_DISTANCE+1];
    this->indeces[0][0]=new Index(MT_EXACT_MATCH,findNextPrime(APPROXIMATE_Q_NUM/2));
    for(int i=0;i<MAX_DISTANCE+1;i++){
        this->indeces[1][i]=new Index(MT_HAMMING_DIST,findNextPrime(APPROXIMATE_Q_NUM/64));
        this->indeces[2][i]=new Index(MT_EDIT_DIST,findNextPrime(APPROXIMATE_Q_NUM/64));
    }

    this->queries = new Vector<Query *>();
    this->docs = new Queue<Document *>();
    this->results = new Queue<Result *>();
    //this->exactEntries=NULL;
}

CoreWrapperErrorCode CoreWrapper::deactivateQuery(QueryID id) {
    Query * qPtr = biSearchQuery(this->queries, id);
    if (qPtr != NULL){
        // this->scheduler->waitPendingMatchesFinish();
        // qPtr->deactivate();
        Args * args = new DeactivateArgs(qPtr);
        Job * job = new Job(DEACTIVATE, args);
        if (this->scheduler->addJob(job) != S_SUCCESS) {
            cerr << "addJob fail [Deactivate]\n";
            return C_W_FAIL;
        }
        return C_W_SUCCESS;
    }
    return C_W_FAIL;
}

CoreWrapperErrorCode CoreWrapper::addQuery(QueryID id, const char * str, MatchType type, unsigned int dist){
    this->scheduler->waitPendingMatchesFinish();
    Query * q = new Query(id,str,type,dist);
    this->queries->insertSorted(q, q->getId());
    // insert to entry list
    Args * args = new InsertArgs(q);
    Job *j=new Job(INSERT, args);
    if (this->scheduler->addJob(j) != S_SUCCESS)
        return C_W_FAIL;
    return C_W_SUCCESS;
}

Document * CoreWrapper::pullDocument(){
    try{
        Document * d = this->docs->pop();
        return d;
    }catch(invalid_argument& ia){
        return NULL;
    }
}

CoreWrapperErrorCode CoreWrapper::matchDocument(Document * doc){
    this->scheduler->waitPendingInsertionsFinish();
    Args * args = new SearchArgs(doc);
    Job *j=new Job(SEARCH, args);

    if (this->scheduler->addJob(j) != S_SUCCESS)
        return C_W_FAIL;
    return C_W_SUCCESS;
}

void CoreWrapper::searchWordExact(Document * doc,Result *res,int thread_index){
    Args * args = new SearchMethodArgs(res, doc, 0, 0, thread_index);
    Job * job = new Job(SEARCH_METHOD, args);
    if (this->scheduler->addJob(job) != S_SUCCESS) {
        cerr << "addJob fail searchWordInIndeces\n";
        return;
    }
}

void CoreWrapper::searchWordEdit(Document * doc,Result *res,int thread_index){
    // int range = MAX_DISTANCE;
    // for(int j=0;j<= range;j++){
        // Args * args = new SearchMethodArgs(res, doc, 2, j, thread_index);
        // Job * job = new Job(SEARCH_METHOD, args);
        // if (this->scheduler->addJob(job) != S_SUCCESS) {
            // cerr << "addJob fail searchWordInIndeces\n";
            // return;
        // }
    // }

    Args * args = new SearchMethodArgs(res, doc, 2, 0, thread_index);
    Job * job = new Job(SEARCH_METHOD, args);
    if (this->scheduler->addJob(job) != S_SUCCESS) {
        cerr << "addJob fail searchWordInIndeces\n";
        return;
    }
}

void CoreWrapper::searchWordHamm(Document * doc,Result *res,int thread_index){
    int range = MAX_DISTANCE;
    for(int j=0;j<=range;j++){
        Args * args = new SearchMethodArgs(res, doc, 1, j, thread_index);
        Job * job=new Job(SEARCH_METHOD, args);
        if (this->scheduler->addJob(job) != S_SUCCESS) {
            cerr << "addJob fail searchWordInIndeces\n";
            return;
        }
    }
}


// void CoreWrapper::searchWordInIndeces(Word *w,Result *res,int thread_index){
    // //first search exact match and increase counters for exact match in res
    // Args * args1 = new SearchMethodArgs(res, w, 0, 0, thread_index);
    // Job *j1=new Job(SEARCH_METHOD, args1);
    // if (this->scheduler->addJob(j1) != S_SUCCESS) {
        // cerr << "addJob fail searchWordInIndeces\n";
        // return;
    // }
//
    // /*
       // int exactEntriesLen = entry_res.getLen();
       // this->exactEntries = new HashTable(findNextPrime(exactEntriesLen), djb2);
       // for (int i = 0; i < exactEntriesLen; ++i)
       // this->exactEntries->insert(entry_res.getItem(i));
       // */
    // // for edit dist
    // int range = MAX_DISTANCE;
    // for(int j=0;j<= range;j++){
        // Args * args2 = new SearchMethodArgs(res, w, 2, j, thread_index);
        // Job *j2=new Job(SEARCH_METHOD, args2);
        // if (this->scheduler->addJob(j2) != S_SUCCESS) {
            // cerr << "addJob fail searchWordInIndeces\n";
            // return;
        // }
    // }
//
    // // for hamming dist
    // for(int j=0;j<=range;j++){
        // Args * args2 = new SearchMethodArgs(res, w, 1, j, thread_index);
        // Job *j2=new Job(SEARCH_METHOD, args2);
        // if (this->scheduler->addJob(j2) != S_SUCCESS) {
            // cerr << "addJob fail searchWordInIndeces\n";
            // return;
        // }
    // }
//
    // //delete this->exactEntries;
// }
/*
   void CoreWrapper::increaseCounter(List<Entry *>& e_list,Result * res){
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
   res->increaseCounter(id, &e->getWord());
   }
   }
   }
   }
   */

void CoreWrapper::increaseCounter(List<Entry *>& e_list,Result * res,MatchType mt,
                                    unsigned int dist){

    int len=e_list.getLen();
    for(int i=0;i<len;i++){
        Entry * e=e_list.getItem(i);
        /*
           if (e == this->exactEntries->getEntry(&e->getWord()))
           continue;
           */
        List<PayloadEntry> &p_list=e->getPayload(mt, dist);
        int plen=p_list.getLen();
        for(int j=0;j<plen;j++){
            PayloadEntry &pE=p_list.getItem(j);
            bool active=pE.getActive();
            if(active){
                QueryID id=pE.getId();
                res->increaseCounter(id, &e->getWord());
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
    this->scheduler->waitForAvailRes();
    this->scheduler->resMutexDown();
    Result * res = this->results->pop();
    this->scheduler->resMutexUp();
    return res;
}

CoreWrapper::~CoreWrapper() {

    this->scheduler->waitPendingMatchesFinish();
    delete this->scheduler;

    delete this->entryList;
    this->results->destroyData();
    delete this->results;

    this->queries->destroyData();
    delete this->queries;

    // this->docs->destroyData();
    delete this->docs;

    delete this->indeces[0][0];
    delete this->indeces[0];

    for(int i=1;i<3;i++) {
        for(int j=0;j<=MAX_DISTANCE;j++)
            delete this->indeces[i][j];
        delete[] this->indeces[i];
    }

    delete[] this->indeces;
}
