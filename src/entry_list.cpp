#include <iostream>
#include "../include/entry_list.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
using namespace std;

EntryList::EntryList():hashtable(10003, djb2), list(){

}

EntryList::~EntryList(){

}

entryListErrorCode EntryList::insert(Query &q){
    int len=q.getWordsInQuery();
    int id=q.getId();

    for(int i=0;i<len;i++)
        if (this->insert(q.getWord(i),id) == E_L_FAIL)
	    return E_L_FAIL;
    return E_L_SUCCESS;
}

entryListErrorCode EntryList::remove(Query &q){
    return E_L_SUCCESS;
}

HashTable & EntryList::getHashTable(){
    return hashtable;
}


Entry * EntryList::getItemPtr(int i) {
    return this->list.getItemPtr(i);
}

entryListErrorCode EntryList::insert(Word *w,int id){
    Entry *e;
    e=hashtable.getEntry(w);
    //if word does not exist
    if(e==NULL){
        // add it to list and then to hashtable
        Entry tmp(*w,id);
        if (list.insert(tmp,&e) == L_FAIL)
	    return E_L_FAIL;
        if (hashtable.insert(e) == H_T_FAIL)
	    return E_L_FAIL;
        return E_L_SUCCESS;
    }
    // else update payload
    hashtable.updateEntryPayload(w,id);
    return E_L_SUCCESS;
}
entryListErrorCode EntryList::remove(Word *,int){
    return E_L_SUCCESS;
}
int EntryList::getLen(){
    return list.getLen();
}
void EntryList::print(){
    list.print();
}
