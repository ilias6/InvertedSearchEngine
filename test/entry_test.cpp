#include <gtest/gtest.h>
#include "../include/entry.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryTest: public ::testing::Test {
    protected:
	Entry * e;
    int size;
	int * payload;
        virtual void SetUp() {
    	    Word w("abcd");
    	    e = new Entry(w, 0);
    	    ASSERT_TRUE(1 == e->getPayload().getLen());
    	    ASSERT_TRUE(0 == e->getPayload().getItem(0));
            size=1000;
    	    payload = new int[size];
    	    for (int i = 0; i < size; ++i) {
                payload[i] = i+10;
                e->addToPayload(payload[i]);
    	    }
        }

        virtual void TearDown() {
            delete e;
            delete[] payload;
        }
};

TEST_F(EntryTest,addToPayload){
    Entry e("test",0);
    ListErrorCode val;
    val=e.addToPayload(1);
    ASSERT_TRUE(L_SUCCESS==val);
    // if addToPayload adds to list
    //then list is checked!!
    List<int> & lst=e.getPayload();
    int n=1;
    ASSERT_TRUE(lst.exists(n));
    e.addToPayload(2);
    n=2;
    ASSERT_TRUE(lst.exists(n));
    int not_exists=999;
    ASSERT_FALSE(lst.exists(not_exists));
    for(int i=0;i<size;i++){
        val=e.addToPayload(payload[i]);
        ASSERT_TRUE(L_SUCCESS==val);
        ASSERT_TRUE(lst.exists(payload[i]));
    }
}

TEST_F(EntryTest,removeFromPayload){
    // if removeFromPayload removes from list
    //then list is checked!!
    ListErrorCode val;
    List<int> & lst=e->getPayload();
    for(int i=0;i<size;i++){
        val=e->removeFromPayload(payload[i]);
        ASSERT_TRUE(L_SUCCESS==val);
        val=e->removeFromPayload(payload[i]);
        ASSERT_TRUE(L_NOT_EXISTS==val);
        ASSERT_FALSE(lst.exists(payload[i]));
    }
    val=e->removeFromPayload(0);
    ASSERT_TRUE(L_SUCCESS==val);
    val=e->removeFromPayload(payload[0]);
    ASSERT_TRUE(L_EMPTY==val);
}

TEST_F(EntryTest,EntryCharPtrConstructor){
    //if word is constructed from char * then word is checked
    Entry entry("test",0);
    Word & w1=entry.getWord();
    Word w2("test");
    ASSERT_TRUE(w1.exactMatch(w2));
}

TEST_F(EntryTest,EntryWordConstructor){
// if word is constructed from other word then word is checked
Word w2("test");
Entry entry(w2,0);
Word & w1=entry.getWord();
ASSERT_TRUE(w1.exactMatch(w2));
}

TEST_F(EntryTest,CopyConstructor){
    Entry e1("test_entry",999);
    for(int i=0;i<988;i++)
        e1.addToPayload(i);
    Entry e2(e1);
    Word &w1=e1.getWord();
    Word &w2=e2.getWord();
    ASSERT_TRUE(w1.exactMatch(w2));
    List<int> &lst1=e1.getPayload();
    List<int> &lst2=e2.getPayload();
    ASSERT_TRUE(lst1.getLen()==lst2.getLen());
    int len=lst1.getLen();
    for(int i=0;i<len;i++)
        ASSERT_TRUE(lst1.getItem(i)==lst2.getItem(i));
}

TEST_F(EntryTest,EqualOperatorOverload){
    //equal operator just check exactMatch of words
    Entry e1("test",0);
    Entry e2("test",1);
    ASSERT_TRUE(e1==e2);
    Entry e3("test",0);
    Entry e4("testtttt",0);
    ASSERT_FALSE(e3==e4);
}
