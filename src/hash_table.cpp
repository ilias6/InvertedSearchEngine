#include <iostream>
#include "hash_table.hpp"

/* DATA IN BUCKETS START*/

Data::Data(Word &w,int indx){
    word=w;
    entry_indx=indx;
}

Word & Data::getWord(){
    return this->word;
}

void Data::setWord(Word &w){
    this->word=w;
    return;
}

void Data::setEntryIndex(int indx){
    this->entry_indx=indx;
    return ;
}
void Data::getEntryIndex(int indx){
    return entry_indx;
}

void Data::print(void){
    cout<<'\t'<<this->word<<" "<<this->entry_indx<<endl;
    return ;
}
bool Data::operator==(const Data & d2){
    return this->word==d2.word;
}
/* DATA IN BUCKETS END*/
/* BUCKETS START*/
Bucket::Bucket():list(){

}

int Bucket::bucketSize(){
    return this->list.len();
}

int  Bucket::getEntryIndex(Word & w){//if ret val is -1 -> word doesn't exist
    // get Data from list and return indx
}

int Bucket::insert(Word &w,int entry_indx){

    // neeeds to be checked !!!!!!!!!!!!!!!!!!
    Data d(w,entry_indx);
    if(!list->exists(d)){
        list.insert(d)
        return SUCCESS;
    }
    return FAILURE;
}
void Bucket::print(void){
    cout<<"-------------------"<<list<<endl;
}
/* BUCKETS END*/
/* HashTable START*/

/* HashTable END*/
