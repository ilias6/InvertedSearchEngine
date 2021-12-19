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
            const char * str[]={"this isis first query","this isis second query","this isis third query","this isis fourth query"};
            MatchType m_t[4]={MT_EXACT_MATCH,MT_EDIT_DIST,MT_HAMMING_DIST,MT_EDIT_DIST};
            unsigned int d[4]={0,1,2,1};
            this->e=new Entry**[numOfQueries];
            for (int i = 0; i < numOfQueries; ++i) {
        		qs[i] = new Query(i,str[i],m_t[i],d[i]);
        		err_val=eList->insert(*qs[i],&e[i]);
                ASSERT_TRUE(E_L_SUCCESS==err_val);
            }
	}


        virtual void TearDown() {
    	    for (int i = 0; i < numOfQueries; ++i){
                delete qs[i];
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


TEST_F(EntryListTest,InsertTest){
    EntryList *el=new EntryList(11);
    EntryListErrorCode err_val;
    // const char * str[]={"this is first query","this is second query","this is third query","this is fourth query"};
    // MatchType m_t[4]={MT_EXACT_MATCH,MT_EDIT_DIST,MT_HAMMING_DIST,MT_EDIT_DIST};
    // unsigned int d[4]={0,1,2,1};
    Entry ***en=new Entry**[numOfQueries];
    for (int i = 0; i < numOfQueries; ++i) {
        err_val=el->insert(*qs[i],&en[i]);
	if (i == 0) {
	    ASSERT_TRUE(strcmp(en[0][0]->getWord().getStr(), "this") == 0);
	    ASSERT_TRUE(strcmp(en[0][1]->getWord().getStr(), "isis") == 0);
	    ASSERT_TRUE(strcmp(en[0][2]->getWord().getStr(), "first") == 0);
	    ASSERT_TRUE(strcmp(en[0][3]->getWord().getStr(), "query") == 0);
	    ASSERT_TRUE(en[0][4] == NULL);
	}
	if (i == 1) {
	    ASSERT_TRUE(strcmp(en[1][0]->getWord().getStr(), "this") == 0);
	    ASSERT_TRUE(strcmp(en[1][1]->getWord().getStr(), "isis") == 0);
	    ASSERT_TRUE(strcmp(en[1][2]->getWord().getStr(), "second") == 0);
	    ASSERT_TRUE(strcmp(en[1][3]->getWord().getStr(), "query") == 0);
	    ASSERT_TRUE(en[1][4] == NULL);
	}
	if (i == 2) {
	    ASSERT_TRUE(strcmp(en[2][0]->getWord().getStr(), "this") == 0);
	    ASSERT_TRUE(strcmp(en[2][1]->getWord().getStr(), "isis") == 0);
	    ASSERT_TRUE(strcmp(en[2][2]->getWord().getStr(), "third") == 0);
	    ASSERT_TRUE(strcmp(en[2][3]->getWord().getStr(), "query") == 0);
	    ASSERT_TRUE(en[2][4] == NULL);
	}
	if (i == 3) {
	    ASSERT_TRUE(strcmp(en[3][0]->getWord().getStr(), "this") == 0);
	    ASSERT_TRUE(strcmp(en[3][1]->getWord().getStr(), "isis") == 0);
	    ASSERT_TRUE(strcmp(en[3][2]->getWord().getStr(), "fourth") == 0);
	    ASSERT_TRUE(strcmp(en[3][3]->getWord().getStr(), "query") == 0);
	    ASSERT_TRUE(en[3][4] == NULL);
	}
        ASSERT_TRUE(E_L_SUCCESS==err_val);
    }
    //ENTRY LIST MUST HAVE SIZE 7
    ASSERT_TRUE(el->getLen()==7);
    // get word "this"
    Entry *e=eList->getItemPtr(0);
    Word * w2=new Word("this");
    // check if word is "this"
    ASSERT_TRUE(e->getWord().exactMatch(*w2));

    delete w2;
    char test_words[][7]={"this","isis","first","query","second","third","fourth"};
    for(int i=0;i<7;i++){
        Word * w2=new Word(test_words[i]);
        Entry * e=eList->getItemPtr(i);
        ASSERT_TRUE(e->getWord().exactMatch(*w2));
        delete w2;
    }

    delete el;
    for (int i = 0; i < numOfQueries; ++i){
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
        "this","isis","first","query","second","third","fourth"
    };
    for(int i=0;i<7;i++){
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
