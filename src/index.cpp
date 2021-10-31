#include <iostream>
#include <cstdlib>

#include "../include/index.hpp"

using namespace std;

void Index::insertFromList(List<Entry> * entryList) {
    if (this->type == HT) {
	for (int i = 0; i < entryList->getLen(); ++i) {
	    Entry * e = entryList->getItemPtr(i);
	    this->hTable.insert(e);
	}
	return;
    }

    for (int i = 0; i < entryList->getLen(); ++i) {
	Entry * e = entryList->getItemPtr(i);
	this->tree.insert(e);
    }
}

Index::Index(List<Entry> * entryList, int (Word::*distFunc)(Word &)):
	    tree(distFunc), hTable() {
    this->type = BKT;
    this->insertFromList(entryList);
}

Index::Index(List<Entry> * entryList, int tableSize, unsigned long (*h_f)(const char *)):
	    tree(), hTable() {
    type = HT;
    hTable.setHashFunc(h_f);
    hTable.setSizeAndAlloc(tableSize);
    this->insertFromList(entryList);
}

Index::~Index() {}


List<Entry *> Index::search(Word * w, int n) { 
    List<Entry *> results;
    if (this->type == HT) {
	Entry * ePtr = this->hTable.getEntry(w);
	if (ePtr != NULL)
	    results.insert(ePtr);
	return results;
    }
    
    List<Entry *> res = this->tree.search(w, n);
    results.append(&res);
    return results;
}
