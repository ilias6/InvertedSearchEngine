#include <iostream>
#include "hash_table.hpp"

/* BUCKETS START*/
Bucket::Bucket():list(){

}

int Bucket::bucketSize(){
    return this->list.len();
}


int Bucket::insert(Entry * e){
    list.insert(e);
    return SUCCESS;
}

bool existsInBucket(Entry * e2){
    Entry * e1;
    int exists=false;
    for(int i=0;i<list.getLen();i++){
        e1=list.getItem(i);
        if((e1->getWord()).exactMatch(e1->getWord())){
            exists=true;
            break;
        }
    }
    return exists;
}

void Bucket::print(void){
    list.print();
}
/* BUCKETS END*/
/* HashTable START*/
HashTable::HashTable(int sz,long long (*h_f)(Word & w)){
    this->size=sz;
    hash_func=h_f;
    this->array=new Bucket(sz);
}
HashTable::HashTable(){
    this->size=0;
    this->array=NULL;
    this->hash_func=NULL;
}
HashTable::~HashTable(){
    this->size=0;
    delete this->array;
    this->array=NULL;
    this->hash_func=NULL;
}

int HashTable::getSize(void){
    return this->size;
}
void HashTable::setSize(int s){
    this->size=s;
}
void setHashFunc(long long (*h_f)(Word &)){
    this->hash_func=h_f;
}

enum htable_retval HashTable::insert(Word &w){
    // Entry e();
}

/* HashTable END*/
