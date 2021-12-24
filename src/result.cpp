#include <iostream>
#include "../include/result.hpp"
#include "../include/utils.hpp"

using namespace std;


Result::Result(DocID id,Vector<Query *> & cur_queries):queries(cur_queries){
    this->docId=id;

    int len=cur_queries.getLen();

    //this->wordIndices = new HashTable*[len];

    this->wordFlags=new bool*[len];

    for(int i=0;i<len;i++) {
        //this->wordIndices[i] = new HashTable(MAX_QUERY_WORDS, djb2);
        Query * q = cur_queries.getItem(i);
        int queryLen = q->getWordsInQuery();
        wordFlags[i]=new bool[queryLen];
        for (int j = 0; j < queryLen; ++j) {
            wordFlags[i][j] = false;
            //PayloadEntry pE(j, 0, MT_EXACT_MATCH, 0, NULL);
            //Entry * ePtr = new Entry(*q->getWord(j), pE);
            //this->wordIndices[i]->insert(ePtr);
        }
    }
}

Result::~Result(){
    int len=this->queries.getLen();
    for (int i = 0; i < len; ++ i) {
        //this->wordIndices[i]->deleteData();
        //delete this->wordIndices[i];
        delete[] this->wordFlags[i];
    }
    delete[] this->wordFlags;
    //delete[] this->wordIndices;
}

DocID Result::getId(){
    return this->docId;
}

// For the hash table implementation but probably it does not worth
/*
int Result::getIdx(int hashIdx, Word * w) {
    Entry * ePtr = this->wordIndices[hashIdx]->getEntry(w);
    if (ePtr == NULL) {
        cerr << "Result: hash table correpted!\n";
        exit(1);
    }
    return ePtr->getPayload().getItem(0).getId();
}
*/

ResultErrorCode Result::increaseCounter(QueryID query_id, Word * w){
    int query_index;
    query_index=biSearchQueryIndex(&this->queries,query_id);
    if(query_index==-1)//query with this id not found
        return R_FAIL;
    Query * query = this->queries.getItem(query_index);
    int qLen = query->getWordsInQuery();
    //int wordIndex = this->getIdx(query_index, w);
    int wordIndex = -1;

    for (int i = 0; i < qLen; ++i)
        if (query->getWord(i)->exactMatch(*w)) {
            wordIndex = i;
            break;
        }
    wordFlags[query_index][wordIndex] = true;
    return R_SUCCESS;
}

ResultErrorCode Result::fetch(DocID * d_id,unsigned int * size_ptr,QueryID ** q_id){
    int size=0;
    *d_id=this->docId;
    int vec_len=queries.getLen();
    *q_id=(QueryID *)malloc(sizeof(QueryID)*vec_len);
    for(int i=0;i<vec_len;i++){
        Query *q=queries.getItem(i);
        if (satisfy(this->wordFlags[i], q->getWordsInQuery()))
            (*q_id)[size++]=q->getId();;
    }
    if(size==0){
        free(*q_id);
        *size_ptr=0;
        *q_id=NULL;
        return R_SUCCESS;

    }
    *size_ptr=size;
    //resize array to actual size
    if(size!=vec_len){
        QueryID * tmp=*q_id;
        *q_id=(QueryID *)malloc(sizeof(QueryID)*size);
        for(int i=0;i<size;i++)
            (*q_id)[i]=tmp[i];
        free(tmp);
    }
    return R_SUCCESS;
}

void Result::print(){
    cout<<"------------DOC: "<<this->docId<<"-------------"<<endl;
}
