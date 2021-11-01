#include <iostream>
#include <cstdlib>

#include "../include/index.hpp"
#include "../include/core.hpp"

using namespace std;

void Index::insertFromList(EntryList &entryList) {
    if (this->type == MT_EXACT_MATCH) {
    	   hTable=new HashTable(entryList.getHashTable());
	       return;
    }
    int len=entryList.getLen();
    if(this->type==MT_EDIT_DIST){
        this->numOfTrees=1;
        tree=new BKTree*;
        tree[0]=new  BKTree(&Word::editDist);
        for (int i = 0; i < len; ++i) {
            Entry * e = entryList.getItemPtr(i);
            this->tree[0]->insert(e);
            // cout << i << endl;
        }
    }else{
        this->numOfTrees=MAX_WORD_LENGTH-MIN_WORD_LENGTH;//one tree for each length (hammingDist)
        tree=new BKTree*[this->numOfTrees];
        for(int i=0;i<this->numOfTrees;i++){
            tree[i]=new BKTree(&Word::hammingDist);
        }
        for (int i = 0; i < len; ++i) {
            Entry * e = entryList.getItemPtr(i);
            int idx=e->getWord().getLen()-MIN_WORD_LENGTH;
            this->tree[idx]->insert(e);
            // cout << i << endl;
        }
    }
}

Index::Index(EntryList & entryList,MatchType type){
    this->type = type;
    this->tree=NULL;
    this->hTable=NULL;
    this->insertFromList(entryList);
}



Index::~Index() {
    if(this->type==MT_EXACT_MATCH){
        delete hTable;
    }else{
        for(int i=0;i<this->numOfTrees;i++)
            delete tree[i];
        delete[] tree;
    }
}


List<Entry *> Index::search(Word * w, int n) {
    List<Entry *> results;
    if (this->type == MT_EXACT_MATCH) {
	       Entry * ePtr = this->hTable->getEntry(w);
	       if (ePtr != NULL)
	          results.insert(ePtr);
	       return results;
    }

    if(this->type== MT_EDIT_DIST){
        List<Entry *> res = this->tree[0]->search(w, n);
        results.append(&res);
    }else{
        // haming dist
        int idx=w->getLen()-MIN_WORD_LENGTH;
        List<Entry *> res = this->tree[idx]->search(w, n);
        results.append(&res);
    }
    return results;
}
