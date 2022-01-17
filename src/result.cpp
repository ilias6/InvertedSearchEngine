#include <iostream>
#include "../include/result.hpp"
#include "../include/utils.hpp"

using namespace std;

Result::Result(DocID id,Vector<Query *> & cur_queries):queries(){
    this->docId=id;
    this->queries.setHashFunc(djb2);

    int len=cur_queries.getLen();
    this->queries.setSizeAndAlloc(findNextPrime(int((len+1)/2)));

    this->wordFlags=new bool*[len];
    this->mutexes=new pthread_mutex_t*[len];

    for(int i=0;i<len;i++) {
        Query * q = cur_queries.getItem(i);
        if (!q->getActive())
            continue;

        QueryEntry * qEntry = new QueryEntry(i, q);
        this->queries.insert(qEntry);

        int queryLen = q->getWordsInQuery();
        wordFlags[i]=new bool[queryLen];
        mutexes[i]=new pthread_mutex_t[queryLen];
        for (int j = 0; j < queryLen; ++j) {
            wordFlags[i][j] = false;
            mutexes[i][j]=PTHREAD_MUTEX_INITIALIZER;
        }
    }
}

Result::~Result(){
    int bucketsNum = this->queries.getSize();
    for (int i = 0; i < bucketsNum; ++i) {
        Vector<QueryEntry *> * qEntries = this->queries.getBucket(i)->getList();
        int len = qEntries->getLen();
        for (int k = 0; k < len; ++k) {
            QueryEntry * qEntry = qEntries->getItem(k);
            Query * q = qEntry->getQuery();
            int index = qEntry->getIndex();
            int queryLen = q->getWordsInQuery();
            for (int j = 0; j < queryLen; ++j)
                if (pthread_mutex_destroy(&this->mutexes[index][j])) {
                    perror("mutex destroy (~)");
                }
            delete qEntry;
            delete[] this->wordFlags[index];
            delete[] this->mutexes[index];
        }
    }
    delete[] this->wordFlags;
    delete[] this->mutexes;
    //this->queries.deleteData();
}

DocID Result::getId(){
    return this->docId;
}

ResultErrorCode Result::increaseCounter(QueryID query_id, Word * w){
    QueryEntry * qEntry = this->queries.getQueryEntry(query_id);
    if (qEntry == NULL)
        return R_FAIL;

    int query_index = qEntry->getIndex();
    if(query_index==-1)//query with this id not found
        return R_FAIL;

    Query * query = qEntry->getQuery();
    int qLen = query->getWordsInQuery();
    //int wordIndex = this->getIdx(query_index, w);
    int wordIndex = -1;

    for (int i = 0; i < qLen; ++i)
        if (query->getWord(i)->exactMatch(*w)) {
            wordIndex = i;
            break;
        }
    if (pthread_mutex_lock(&this->mutexes[query_index][wordIndex])) {
        perror("mutex lock increaseCounter");
    }
    wordFlags[query_index][wordIndex] = true;
    if (pthread_mutex_unlock(&this->mutexes[query_index][wordIndex])) {
        perror("mutex lock increaseCounter");
    }
    return R_SUCCESS;
}

ResultErrorCode Result::fetch(DocID * d_id,unsigned int * size_ptr,QueryID ** q_id){
    int size=0;
    *d_id=this->docId;
    int bucketsNum=this->queries.getSize();
    int numOfQueries=this->queries.getNumOfQueries();
    *q_id=(QueryID *)malloc(sizeof(QueryID)*numOfQueries);

    for(int i=0; i<bucketsNum; i++) {
        Vector<QueryEntry *> * qEntries = this->queries.getBucket(i)->getList();
        int len = qEntries->getLen();
        for (int j = 0; j < len; ++j) {
            QueryEntry *qEntry=qEntries->getItem(j);
            Query * q = qEntry->getQuery();
            if (satisfy(this->wordFlags[qEntry->getIndex()], q->getWordsInQuery()))
                // (*q_id)[size++]=q->getId();
                insertSorted(q_id, size++, q->getId());
        }
    }

    if(size==0){
        free(*q_id);
        *size_ptr=0;
        *q_id=NULL;
        return R_SUCCESS;

    }
    *size_ptr=size;
    //resize array to actual size
    if(size!=numOfQueries){
        QueryID * tmp=*q_id;
        *q_id=(QueryID *)malloc(sizeof(QueryID)*size);
        for(int i=0;i<size;i++)
            (*q_id)[i]=tmp[i];
        free(tmp);
    }
    return R_SUCCESS;
}

ResultErrorCode Result::resetCounters(QueryID query_id){
    QueryEntry * qEntry=this->queries.getQueryEntry(query_id);

    int query_index = qEntry->getIndex();
    if(query_index==-1)//query with this id not found
        return R_FAIL;
    // Query * query = this->queries.getItem(query_index);
    // int qLen = query->getWordsInQuery();
    //int wordIndex = this->getIdx(query_index, w);
    if (pthread_mutex_lock(&this->mutexes[query_index][0])) {
        perror("mutex lock increaseCounter");
    }
    wordFlags[query_index][0] = false;

    if (pthread_mutex_unlock(&this->mutexes[query_index][0])) {
        perror("mutex lock increaseCounter");
    }
    return R_SUCCESS;
}

void Result::print(){
    cout<<"------------DOC: "<<this->docId<<"-------------"<<endl;
}
