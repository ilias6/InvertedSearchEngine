#include "../include/entry_list.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryListTest: public ::testing::Test {
    protected:
	EntryList * eList;
	Query ** qs;
    Entry *** e;
    int numOfQueries;
        virtual void SetUp() {
    	    eList = new EntryList(7);
            numOfQueries=4;
            EntryListErrorCode err_val;
    	    qs = new Query*[numOfQueries];
            const char * str[]={"this is first query","this is second query","this is third query","this is fourth query"}
            Matchtype m_t[4]={MT_EXACT_MATCH,MT_EDIT_DIST,MT_HAMMING_DIST,MT_EDIT_DIST};
            unsigned int d[4]={0,1,2,1};
            this->e=new Entry**[numOfQueries];
            for (int i = 0; i < numOfQueries; ++i) {
        		// char path[64];
        		qs[i] = new Query(i,str[i],m_t[i],d[i]);
        		err_val=eList->insert(*qs[i],&e[i]);
                ASSERT_TRUE(E_L_SUCCESS==err_val);
            }
	    }


        virtual void TearDown() {
    	    for (int i = 0; i < numOfQueries; ++i){
                delete qs[i];
                for(int j=0;e[j]!=NULL;j++)
                    delete e[i][j];
                delete[] e[i];
            }
            delete[] e;
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

// NEEEEEEEEEEEEEEEEEED TOOOOOOOO BE CHEEEEEECKED

TEST_F(EntryListTest,InsertTest){
    EntryList *el=new EntryList(11);
    EntryListErrorCode err_val;
    const char * str[]={"this is first query","this is second query","this is third query","this is fourth query"}
    Matchtype m_t[4]={MT_EXACT_MATCH,MT_EDIT_DIST,MT_HAMMING_DIST,MT_EDIT_DIST};
    unsigned int d[4]={0,1,2,1};
    Entry ***en=new Entry**[numOfQueries];
    for (int i = 0; i < numOfQueries; ++i) {
        err_val=eList->insert(*qs[i],&en[i]);
        ASSERT_TRUE(E_L_SUCCESS==err_val);
    }
    //ENTRY LIST MUST HAVE SIZE 7
    ASSERT_TRUE(el->getLen()==7);
    // get word "this"
    Entry *e=eList->getItemPtr(0);
    Word * w2=new Word("this");
    // check if word is "this"
    ASSERT_TRUE(e->getWord().exactMatch(*w2));

    // check if Payload contains 0,1,2,3 ids
    List<PayloadEntry> list=e->getPayload();
    ASSERT_TRUE(4==list.getLen());
    for(int i=0;i<4;i++){
        PayloadEntry p(i,0,m_t[i],d[i],NULL);
        ASSERT_TRUE(list.exists(p));
    }

    delete w2;
    char test_words[][7]={"this","is","first","query","second","third","fourth"};
    for(int i=0;i<7;i++){
        Word * w2=new Word(test_words[i]);
        Entry * e=eList->getItemPtr(i);
        ASSERT_TRUE(e->getWord().exactMatch(*w2));
        delete w2;
    }

    delete el;
    for (int i = 0; i < numOfQueries; ++i){
        for(int j=0;en[j]!=NULL;j++)
            delete en[i][j];
        delete[] en[i];
    }
    delete[] en;

}
//not implemented
// TEST_F(EntryListTest,RemoveTest){
//
// }

TEST_F(EntryListTest,GetItemPtrTest){
    char test_words[][7]={
        "this","is","first","query","second","third","fourth"
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
