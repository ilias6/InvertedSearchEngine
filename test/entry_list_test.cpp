#include "../include/entry_list.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryListTest: public ::testing::Test {
    protected:
	EntryList * eList;
	Query ** qs;
    int numOfQueries;
        virtual void SetUp() {
    	    eList = new EntryList(7);
            numOfQueries=4;
            EntryListErrorCode err_val;
    	    qs = new Query*[numOfQueries];
    	    for (int i = 0; i < numOfQueries; ++i) {
        		char path[64];
        		sprintf(path, "input/test_queries/query_%d", i);
        		qs[i] = new Query(i,path);
        		err_val=eList->insert(*qs[i]);
                ASSERT_TRUE(E_L_SUCCESS==err_val);
            }
	    }


        virtual void TearDown() {
    	    for (int i = 0; i < numOfQueries; ++i)
                delete qs[i];
    	    delete[] qs;
    	    delete eList;
        }

};

TEST_F(EntryListTest,ConstructorTest){
    EntryList el(10000);
    // check if hashtable is constructed
    HashTable &hashtable=el.getHashTable();
    ASSERT_TRUE(hashtable.getSize()==10000);
    // check list size equal 0
    ASSERT_TRUE(el.getLen()==0);
    ASSERT_TRUE(el.getItemPtr(0)==NULL);

}

TEST_F(EntryListTest,InsertTest){
    //ass we see in test words word "a" exists in query 0 and in query 3
    //se when we get Entry-> payload must contain 0 and 3
    char test_words[][16]={
        "a","word","is","here","hel","hll","ello","oop","trooper","shit","mastodon","helps","wolves"
    };
    EntryList *el=new EntryList(11);

    HashTable & ht=el->getHashTable();
    EntryListErrorCode err_val;
    for (int i = 0; i < numOfQueries; ++i) {
        char path[64];
        sprintf(path, "input/test_queries/query_%d", i);
        err_val=el->insert(*qs[i]);
        ASSERT_TRUE(E_L_SUCCESS==err_val);
    }
    //ENTRY LIST MUST HAVE SIZE 13 BECAUSE A EXISTS MORE THA ONE TIMES
    ASSERT_TRUE(el->getLen()==13);
    // get word "a"
    Entry *e=eList->getItemPtr(0);
    // check if Payload contains 0 and 3
    Word * w2=new Word(test_words[0]);
    // check if word is "a"
    ASSERT_TRUE(e->getWord().exactMatch(*w2));

    List<int> list=e->getPayload();
    ASSERT_TRUE(2==list.getLen());
    int v=0;
    ASSERT_TRUE(list.exists(v));
    v=3;
    ASSERT_TRUE(list.exists(v));

    delete w2;
    for(int i=1;i<13;i++){
        Word * w2=new Word(test_words[i]);
        Entry * e=eList->getItemPtr(i);
        ASSERT_TRUE(e->getWord().exactMatch(*w2));
        delete w2;
    }

    delete el;

}
//not implemented
// TEST_F(EntryListTest,RemoveTest){
//
// }

TEST_F(EntryListTest,GetItemPtrTest){
    char test_words[][16]={
        "a","word","is","here","hel","hll","ello","oop","trooper","shit","mastodon","helps","wolves"
    };
    for(int i=0;i<13;i++){
        Word * w2=new Word(test_words[i]);
        Entry * e=eList->getItemPtr(i);
        ASSERT_TRUE(e->getWord().exactMatch(*w2));
        delete w2;
    }
    Entry * e=eList->getItemPtr(14);
    ASSERT_TRUE(e==NULL);
    e=eList->getItemPtr(-1);
   ASSERT_TRUE(e==NULL);
}
