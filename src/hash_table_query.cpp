#include <iostream>
#include "../include/hash_table_query.hpp"
#include "../include/utils.hpp"
#include "../include/hash_functions.hpp"

/* BUCKETS START*/
using namespace std;
BucketQuery::BucketQuery():list() {}

int BucketQuery::bucketSize(){
    return this->list.getLen();
}


BucketQuery::BucketQuery(BucketQuery & b) {
    this->list.copyVector(b.list);
}

void BucketQuery::copyBucketQuery(BucketQuery &b2){
    this->list.copyVector(b2.list);
}

enum HashTableQueryErrorCode BucketQuery::insert(QueryEntry * e){
    list.insert(e);
    return H_T_Q_SUCCESS;
}

// used for testing
Vector<QueryEntry *> BucketQuery::getListCopy() {
    return this->list;
}

Vector<QueryEntry *> * BucketQuery::getList() {
    return &this->list;
}

/* flag == true search for id == j 
 * flag == false get jth query of BucketQuery */
QueryEntry * BucketQuery::getQueryEntry(QueryID j, bool flag){
    //returns NULL if doesn't exist
    QueryEntry * q=NULL;
    if (flag) {
        for(int i=0;i<list.getLen();i++){
            q=list.getItem(i);
            if((q->getQuery()->getId()) == j)
                break;
            q = NULL;

        }
    }
    else {
        if(j>=(unsigned int)list.getLen())
            return NULL;
        return list.getItem(j);
    }
    return q;
}

void BucketQuery::print(void){
    list.print();
}

void BucketQuery::printAddr(void){
    //list.printAddr();
    cout << "BucketQuery::printAddr is not implemented\n";
}

/* BUCKETS END*/
/* HashTableQuery START*/
HashTableQuery::HashTableQuery(int sz,unsigned long (*h_f)(const char *)){
    this->size=sz;
    this->current_size=0;
    hash_func=h_f;
    this->array=new BucketQuery[sz];
}

HashTableQuery::HashTableQuery(){
    this->size=0;
    this->current_size=0;
    this->array=NULL;
    this->hash_func=NULL;
}

HashTableQuery::HashTableQuery(HashTableQuery & ht){
    this->size=ht.size;
    this->current_size=ht.current_size;
    this->array=new BucketQuery[size];
    for(int i=0;i<size;i++)
        this->array[i].copyBucketQuery(ht.array[i]);
    this->hash_func=ht.hash_func;
}

BucketQuery * HashTableQuery::getBucket(int i) {
    return &this->array[i];
}

HashTableQuery::~HashTableQuery(){
    this->size=0;
    if(this->array!=NULL)
        delete[] this->array;
    this->array=NULL;
    this->hash_func=NULL;
}

void HashTableQuery::deleteData(){
    for(int i=0;i<this->size;i++){
        Query * e;
        int sz=array[i].bucketSize();
        for(int j=0;j<sz;j++){
            e=array[i].getQueryEntry(j, false)->getQuery();
            delete e;
        }
    }
}

QueryEntry * HashTableQuery::getQueryEntry(QueryID id) {
    string idStr = to_string(id);
    char * str = new char[idStr.length()+1];
    strcpy(str, idStr.c_str());
    unsigned long hash = this->hash_func(str);
    delete[] str;
    int bucket_index = hash%this->size;
    return this->array[bucket_index].getQueryEntry(id, true);
}

int HashTableQuery::getSize(void){
    return this->size;
}

int HashTableQuery::getNumOfQueries(void){
    return this->current_size;
}

enum HashTableQueryErrorCode HashTableQuery::setSizeAndAlloc(int sz){
    if (this->size == 0) {
        this->size=sz;
        this->array=new BucketQuery[sz];
        return H_T_Q_SUCCESS;
    }

    if(this->array!=NULL)
        delete[] this->array;
    else
        cout << "Weird things happened!\n";
    this->size=sz;
    this->array=new BucketQuery[sz];
    return H_T_Q_SUCCESS;
}

enum HashTableQueryErrorCode HashTableQuery::setHashFunc(unsigned long (*h_f)(const char *)){
    this->hash_func=h_f;
    return H_T_Q_SUCCESS;
}

enum HashTableQueryErrorCode HashTableQuery::insert(QueryEntry * q){
    if ((float)this->current_size/this->size >= 1.8)
        this->rehash();

    //insert just inserts entry in hashtable
    string idStr = to_string(q->getQuery()->getId());
    char * str = new char[idStr.length()+1];
    strcpy(str, idStr.c_str());
    unsigned long hash= this->hash_func(str);
    delete[] str;
    int bucket_index=hash%this->size;
    this->current_size++;
    return this->array[bucket_index].insert(q);
}

void HashTableQuery::rehash() {
    int tmpSize = this->size;
    BucketQuery * tmpBucketQueryArr = this->array;

    this->size = findNextPrime(this->size*4);
    this->array = new BucketQuery[this->size];
    for (int i = 0; i < tmpSize; i++) {
        int bSize = tmpBucketQueryArr[i].bucketSize();
        for (int j = 0; j < bSize; ++j)
            this->insert(tmpBucketQueryArr[i].getQueryEntry(j, false));
    }
    delete[] tmpBucketQueryArr;
}

void HashTableQuery::print(void){
    cout<<"::HASHTABLE INFO::"<<endl;
    cout<<"\tSize: "<<this->size<<endl;
    for(int i=0;i<this->size;i++){
        cout<<"-BUCKET "<<i<<" -"<<endl;
        this->array[i].print();
    }

}

void HashTableQuery::printAddr(void){
    cout<<"::HASHTABLE INFO::"<<endl;
    cout<<"\tSize: "<<this->size<<endl;
    for(int i=0;i<this->size;i++){
        cout<<"-BUCKET "<<i<<" -"<<endl;
        this->array[i].printAddr();
    }

}


/* HashTableQuery END*/
