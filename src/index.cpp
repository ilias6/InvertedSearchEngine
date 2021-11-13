#include <iostream>
#include <cstdlib>

#include "../include/index.hpp"
#include "../include/core.hpp"

using namespace std;

IndexErrorCode Index::insertFromList(EntryList &entryList) {
    if (this->type == MT_EXACT_MATCH) {
	try {
	    hTable=new HashTable(entryList.getHashTable());
	}
	catch (bad_alloc & exc) {
	    return I_FAIL;
	}
	return I_SUCCESS;
    }
    int len=entryList.getLen();
    if(this->type==MT_EDIT_DIST){
        this->numOfTrees=1;
        try {
	    tree=new BKTree*;
	    tree[0]=new  BKTree(&Word::editDist);
	}
    	catch (bad_alloc & exc) {
    	    return I_FAIL;
    	}
            for (int i = 0; i < len; ++i) {
                Entry * e = entryList.getItemPtr(i);
                if (this->tree[0]->insert(e) == BK_FAIL)
    		return I_FAIL;
                // cout << i << endl;
            }
    }else{
        this->numOfTrees=MAX_WORD_LENGTH-MIN_WORD_LENGTH;//one tree for each length (hammingDist)
        try {
	    tree=new BKTree*[this->numOfTrees];
	}
	catch (bad_alloc & exc) {
	    return I_FAIL;
	}
        for(int i=0;i<this->numOfTrees;i++){
            try {
		tree[i]=new BKTree(&Word::hammingDist);
	    }
	    catch (bad_alloc & exc) {
	    	return I_FAIL;
	    }
        }
        for (int i = 0; i < len; ++i) {
            Entry * e = entryList.getItemPtr(i);
            int idx=e->getWord().getLen()-MIN_WORD_LENGTH;
            if (this->tree[idx]->insert(e) == BK_FAIL)
		return I_FAIL;
            // cout << i << endl;
        }
    }
    return I_SUCCESS;
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
    }else if (this->type==MT_HAMMING_DIST){
        for(int i=0;i<this->numOfTrees;i++)
            delete tree[i];
        delete[] tree;
    }else{
        delete tree[0];
        delete tree;
    }
}

MatchType Index::getType() {
    return this->type;
}

List<Entry *> Index::search(Word * w, int n) {
    List<Entry *> results;
    if (this->type == MT_EXACT_MATCH) {
	       Entry * ePtr = this->hTable->getEntry(w);
	       if (ePtr != NULL)
	          results.insert(ePtr);
	       return results;
    }

    if(this->type == MT_EDIT_DIST) {
        List<Entry *> res = this->tree[0]->search(w, n);
        results.append(&res);
    }
    else {
        // haming dist
        int idx=w->getLen()-MIN_WORD_LENGTH;
        List<Entry *> res = this->tree[idx]->search(w, n);
        results.append(&res);
    }
    return results;
}
