#include <iostream>
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include "../include/entry.hpp"


/* BUCKETS START*/
using namespace std;
Bucket::Bucket():list() {}

int Bucket::bucketSize(){
    return this->list.getLen();
}


enum htable_retval Bucket::insert(Entry * e){
    list.insert(e);
    return SUCCESS;
}

Entry * Bucket::getEntry(int indx){
    if(indx>=list.getLen())
        return NULL;
    return list.getItem(indx);
}

Entry * Bucket::getEntry(Word * w){
    //returns NULL if doesn't exist
    Entry * e1=NULL;
    for(int i=0;i<list.getLen();i++){
        e1=list.getItem(i);
        if((e1->getWord()).exactMatch(*w))
            break;
	e1 = NULL;

    }
    return e1;
}

void Bucket::print(void){
    list.print();
}

void Bucket::printAddr(void){
    list.printAddr();
}

/* BUCKETS END*/
/* HashTable START*/
HashTable::HashTable(int sz,unsigned long (*h_f)(const char *)){
    this->size=sz;
    hash_func=h_f;
    this->array=new Bucket[sz];
}
HashTable::HashTable(){
    this->size=0;
    this->array=NULL;
    this->hash_func=NULL;
}
HashTable::~HashTable(){
    this->size=0;
    if(this->array!=NULL)
        delete[] this->array;
    this->array=NULL;
    this->hash_func=NULL;
}

void HashTable::deleteData(){
    for(int i=0;i<this->size;i++){
        Entry * e;
        int sz=array[i].bucketSize();
        for(int j=0;j<sz;j++){
            e=array[i].getEntry(j);
            delete e;
        }
    }
}


// ultra fail function
Entry * HashTable::getEntry(Word * w) {
    unsigned long hash = this->hash_func(w->getStr());
    int bucket_index = hash%this->size;
    return this->array[bucket_index].getEntry(w);
}

int HashTable::getSize(void){
    return this->size;
}
void HashTable::setSize(int s){
    this->size=s;
}
void HashTable::setHashFunc(unsigned long (*h_f)(const char *)){
    this->hash_func=h_f;
}

enum htable_retval HashTable::insert(Entry * e){
    //insert just inserts entry in hashtable
    unsigned long hash= this->hash_func((e->getWord()).getStr());
    int bucket_index=hash%this->size;
    return this->array[bucket_index].insert(e);
}

enum htable_retval HashTable::updateEntryPayload(Word *w,int payload){
    unsigned long hash= this->hash_func(w->getStr());
    int bucket_index=hash%this->size;
    Entry *to_be_updated=this->array[bucket_index].getEntry(w);
    if(to_be_updated==NULL)
        return FAILURE;

    to_be_updated->addToPayload(payload);
    return SUCCESS;
}

void HashTable::print(void){
    cout<<"::HASHTABLE INFO::"<<endl;
    cout<<"\tSize: "<<this->size<<endl;
    for(int i=0;i<this->size;i++){
        cout<<"-BUCKET "<<i<<" -"<<endl;
        this->array[i].print();
    }

}

void HashTable::printAddr(void){
    cout<<"::HASHTABLE INFO::"<<endl;
    cout<<"\tSize: "<<this->size<<endl;
    for(int i=0;i<this->size;i++){
        cout<<"-BUCKET "<<i<<" -"<<endl;
        this->array[i].printAddr();
    }

}


/* HashTable END*/
