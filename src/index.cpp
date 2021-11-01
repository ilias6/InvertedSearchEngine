#include <iostream>
#include <cstdlib>

#include "../include/index.hpp"

using namespace std;

void Index::insertFromList(EntryList &entryList) {
    if (this->type == MT_EXACT_MATCH) {
    	   hTable=new HashTable(entryList.getHashTable());
	       return;
    }
    if(this->type==MT_EDIT_DIST)
        tree=new BKTree(&Word::editDist);
    else
        tree=new BKTree(&Word::hammingDist);

    int len=entryList.getLen();
    for (int i = 0; i < len; ++i) {
	       Entry * e = entryList.getItemPtr(i);
	       this->tree->insert(e);
	// cout << i << endl;
    }
}

Index::Index(EntryList & entryList,MatchType type){
    this->type = type;
    this->tree=NULL;
    this->hTable=NULL;
    this->insertFromList(entryList);
}



Index::~Index() {
    if(this->type==MT_EXACT_MATCH)
        delete hTable;
    else
        delete tree;
}


List<Entry *> Index::search(Word * w, int n) {
    List<Entry *> results;
    if (this->type == MT_EXACT_MATCH) {
	       Entry * ePtr = this->hTable->getEntry(w);
	       if (ePtr != NULL)
	          results.insert(ePtr);
	       return results;
    }

    List<Entry *> res = this->tree->search(w, n);
    results.append(&res);
    return results;
}
