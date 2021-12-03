#include <iostream>
#include "../include/result.hpp"
#include "../include/utils.hpp"

using namespace std;



Result::Result(DocID id,Vector<Query *> & cur_queries):queries(cur_queries){
    this->docId=id;
    int len=cur_queries.getLen();
    this->counters=new int[len];
    for(int i=0;i<len;i++)
        counters[i]=0;
}

Result::~Result(){
    delete[] this->counters;
}


ResultErrorCode Result::increaseCounter(QueryID query_id){
    int query_index;
    query_index=biSearchQueryIndex(&this->queries,query_id);
    if(query_index==-1)//query with this id not found
        return R_FAIL;
    this->counters[query_index]++;
    return R_SUCCESS;
}

ResultErrorCode Result::fetch(DocID * d_id,unsigned int * size_ptr,QueryID ** q_id){
    int size=0;
    *d_id=this->docId;
    int vec_len=queries.getLen();
    *q_id=new QueryID[vec_len];
    for(int i=0;i<vec_len;i++){
        Query *q=queries.getItem(i);
        if(counters[i]>=q->getWordsInQuery())
            (*q_id)[size++]=q->getId();;
    }
    if(size==0){
        delete[] *q_id;
        *size_ptr=0;
        *q_id=NULL;
        return R_EMPTY;

    }
    *size_ptr=size;
    //resize array to actual size
        if(size!=vec_len){
            QueryID * tmp=*q_id;
            *q_id=new QueryID[size];
            for(int i=0;i<size;i++)
                (*q_id)[i]=tmp[i];
            delete[] tmp;
        }
    return R_SUCCESS;
}

void Result::print(){
    cout<<"------------DOC: "<<this->docId<<"-------------"<<endl;
    int vec_len=this->queries.getLen();
    for(int i=0;i<vec_len;i++)
        cout<<"QueryID "<<queries.getItem(i)->getId()<<": "<<counters[i]<<" matches"<<endl;

}
