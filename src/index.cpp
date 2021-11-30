#include <iostream>
#include <cstdlib>

#include "../include/index.hpp"
#include "../include/core.hpp"

using namespace std;


Index::Index(MatchType tp){
    this->type=tp;
    if (this->type == MT_EXACT_MATCH) {
        this->numOfTrees=0;
        this->tree=NULL;
        this->hTable=new HashTable();
        return;
    }
    if(this->type==MT_EDIT_DIST){
        this->numOfTrees=1;
        this->tree=new BKTree*;
        this->tree[0]=new  BKTree(&Word::editDist);
    }else{
        this->numOfTrees=MAX_WORD_LENGTH-MIN_WORD_LENGTH;//one tree for each length (hammingDist)
        tree=new BKTree*[this->numOfTrees];

        for(int i=0;i<this->numOfTrees;i++)
            tree[i]=new BKTree(&Word::hammingDist);
    }
    // also make hashtable for searching if something exists as is in index
    this->hTable=new HashTable();
    return ;
}

// insert takes argument null terminated array
//of Entry * (its the query converted in entries *)
IndexErrorCode Index::insert(Entry ** arr){
    //first check if Entry exists in hashTable as is
    for(int i=0;arr[i]!=NULL;i++){
        Entry * e=hTable->getEntry(arr[i]->getWord());
        IndexErrorCode i_err;
        HashTableErrorCode h_err;
        if(e==NULL){
            h_err=hTable->insert(e);
            if(h_err==H_T_FAIL)
                return I_FAIL;
            i_err=this->insert(e);
            if(i_err==I_FAIL)
                return I_FAIL;
        }
    }
}

IndexErrorCode Index::insert(Entry *e){
    switch(this->type){
        case MT_EXACT_MATCH://already inserted from caller
            break;
        case MT_EDIT_DIST:
            if (this->tree[0]->insert(e) == BK_FAIL)
                return I_FAIL;
            break;
        case MT_HAMMING_DIST:
            int idx=e->getWord().getLen()-MIN_WORD_LENGTH;
            if (this->tree[idx]->insert(e) == BK_FAIL)
                return I_FAIL;
            break;
    }
    return I_SUCCESS;
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
    if (w == NULL || w->getLen() == 0)
        return results;

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
        if(idx>=this->numOfTrees)
            return results;
        List<Entry *> res = this->tree[idx]->search(w, n);
        results.append(&res);
    }
    return results;
}
