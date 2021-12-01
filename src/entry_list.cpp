#include <iostream>
#include "../include/entry_list.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include "../include/utils.hpp"

using namespace std;

EntryList::EntryList(int n):hashtable(n, djb2), list(){}

EntryList::~EntryList(){

}

EntryListErrorCode EntryList::insert(Query &q, Entry *** qEntryPtrs){
    int len=q.getWordsInQuery();
    PayloadEntry pE(q.getId(),q.getWordsInQuery(),q.getType(),q.getMatchDist(),q.getAdressOfActive());
    *qEntryPtrs = new Entry*[len+1];
 			
    (*qEntryPtrs)[len] = NULL;
    for(int i=0;i<len;i++)
        if (this->insert(q.getWord(i), pE, (*qEntryPtrs)+i) == E_L_FAIL)
	       return E_L_FAIL;
    return E_L_SUCCESS;
}

EntryListErrorCode EntryList::remove(Query &q){
    return E_L_SUCCESS;
}

HashTable & EntryList::getHashTable(){
    return hashtable;
}


Entry * EntryList::getItemPtr(int i) {
    return this->list.getItemPtr(i);
}

EntryListErrorCode EntryList::insert(Word *w, PayloadEntry & pE, Entry ** qEntryPtr){
    Entry *e;
    e=hashtable.getEntry(w);
    //if word does not exist
    if(e==NULL){
       // add it to list and then to hashtable
        Entry tmp(*w,pE);
        if (list.insert(tmp,&e) == L_FAIL)
	       return E_L_FAIL;
        if (hashtable.insert(e) == H_T_FAIL)
	       return E_L_FAIL;
	*qEntryPtr = e;
        return E_L_SUCCESS;
    }
    // else update payload
    hashtable.updateEntryPayload(w, pE, &e);
    *qEntryPtr = e;
    return E_L_SUCCESS;
}
EntryListErrorCode EntryList::remove(Word *,int){
    return E_L_SUCCESS;
}
int EntryList::getLen(){
    return list.getLen();
}
void EntryList::print(){
    list.print();
}
