#include <iostream>
#include "../include/entry_list.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
using namespace std;

EntryList::EntryList():hashtable(10003, djb2), list(){

}

EntryList::~EntryList(){

}

int EntryList::insert(Query &q){
    int len=q.getWordsInQuery();
    int id=q.getId();

    for(int i=0;i<len;i++)
        this->insert(q.getWord(i),id);
    return 0;
}

int EntryList::remove(Query &q){
return 0;
}
HashTable & EntryList::getHashTable(){
    return hashtable;
}


Entry * EntryList::getItemPtr(int i) {
    return this->list.getItemPtr(i);
}

int EntryList::insert(Word *w,int id){
    Entry *e;
    e=hashtable.getEntry(w);
    //if word does not exist
    if(e==NULL){
        // add it to list and then to hashtable
        Entry tmp(*w,id);
        list.insert(tmp,&e);
        hashtable.insert(e);
        return 0;
    }
    // else update payload
    hashtable.updateEntryPayload(w,id);
    return 0;
}
int EntryList::remove(Word *,int){
    return 0;
}
int EntryList::getLen(){
    return list.getLen();
}
void EntryList::print(){
    list.print();
}
