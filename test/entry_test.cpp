#include "../include/entry.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryTest: public ::testing::Test {
    protected:
        Entry * e;
        int size;
        PayloadEntry * payload;
        virtual void SetUp() {
            Word w("abcd");
            PayloadEntry p(0, NULL);
            e = new Entry(w, p, MT_EXACT_MATCH, 0);
            ASSERT_TRUE(1 == e->getPayload(MT_EXACT_MATCH, 0).getLen());
            ASSERT_TRUE(p == e->getPayload(MT_EXACT_MATCH, 0).getItem(0));
            size=1000;
            payload = new PayloadEntry[size];
            for (int i = 0; i < size; ++i) {
                payload[i].setPayloadEntry(i+10,NULL);
                e->addToPayload(payload[i], MT_EXACT_MATCH, 0);
            }
        }

        virtual void TearDown() {
            delete e;
            delete[] payload;
        }
};

TEST_F(EntryTest,addToPayload){
    PayloadEntry p0(0,NULL);
    Entry e("test",p0, MT_EXACT_MATCH, 0);
    ListErrorCode val;
    PayloadEntry p1(1,NULL);
    val=e.addToPayload(p1, MT_EXACT_MATCH, 0);
    ASSERT_TRUE(L_SUCCESS==val);
    // if addToPayload adds to list
    //then list is checked!!
    List<PayloadEntry> & lst=e.getPayload(MT_EXACT_MATCH, 0);
    ASSERT_TRUE(lst.exists(p1));
    PayloadEntry p2(2,NULL);
    e.addToPayload(p2, MT_EXACT_MATCH, 0);
    ASSERT_TRUE(lst.exists(p2));

    int not_exists=999;
    PayloadEntry p_not_exists(not_exists,NULL);
    ASSERT_FALSE(lst.exists(p_not_exists));
    for(int i=0;i<size;i++){
        val=e.addToPayload(payload[i], MT_EXACT_MATCH, 0);
        ASSERT_TRUE(L_SUCCESS==val);
        ASSERT_TRUE(lst.exists(payload[i]));
    }
}

/*
TEST_F(EntryTest,removeFromPayload){
    // if removeFromPayload removes from list
    //then list is checked!!
    ListErrorCode val;
    List<PayloadEntry> & lst=e->getPayload();
    for(int i=0;i<size;i++){
        val=e->removeFromPayload(payload[i]);
        ASSERT_TRUE(L_SUCCESS==val);
        val=e->removeFromPayload(payload[i]);
        ASSERT_TRUE(L_NOT_EXISTS==val);
        ASSERT_FALSE(lst.exists(payload[i]));
    }
    PayloadEntry p0(0,0,MT_EXACT_MATCH,2,NULL);
    val=e->removeFromPayload(p0);
    ASSERT_TRUE(L_SUCCESS==val);
    val=e->removeFromPayload(payload[0]);
    ASSERT_TRUE(L_EMPTY==val);
}
*/

TEST_F(EntryTest,EntryCharPtrConstructor){
    //if word is constructed from char * then word is checked
    PayloadEntry p0(0,NULL);
    Entry entry("test",p0, MT_EXACT_MATCH, 0);
    Word & w1=entry.getWord();
    Word w2("test");
    ASSERT_TRUE(w1.exactMatch(w2));
}

TEST_F(EntryTest,EntryWordConstructor){
// if word is constructed from other word then word is checked
PayloadEntry p0(0,NULL);
Word w2("test");
Entry entry(w2,p0, MT_EXACT_MATCH, 0);
Word & w1=entry.getWord();
ASSERT_TRUE(w1.exactMatch(w2));
}

TEST_F(EntryTest,CopyConstructor){
    PayloadEntry p(999,NULL);
    Entry e1("test_entry",p, MT_EXACT_MATCH, 0);
    for(int i=0;i<988;i++){
        p.setPayloadEntry(i,NULL);
        e1.addToPayload(p, MT_EXACT_MATCH, 0);
    }
    Entry e2(e1);
    Word &w1=e1.getWord();
    Word &w2=e2.getWord();
    ASSERT_TRUE(w1.exactMatch(w2));
    List<PayloadEntry> &lst1=e1.getPayload(MT_EXACT_MATCH, 0);
    List<PayloadEntry> &lst2=e2.getPayload(MT_EXACT_MATCH, 0);
    ASSERT_TRUE(lst1.getLen()==lst2.getLen());
    int len=lst1.getLen();
    for(int i=0;i<len;i++)
        ASSERT_TRUE(lst1.getItem(i)==lst2.getItem(i));
}

TEST_F(EntryTest,EqualOperatorOverload){
    //equal operator just check exactMatch of words
    PayloadEntry p0(0,NULL);
    Entry e1("test",p0,MT_EXACT_MATCH, 0);
    PayloadEntry p1(1,NULL);
    Entry e2("test",p1,MT_EXACT_MATCH, 0);
    ASSERT_TRUE(e1==e2);
    Entry e3("test",p0,MT_EXACT_MATCH, 0);
    Entry e4("testtttt",p0,MT_EXACT_MATCH, 0);
    ASSERT_FALSE(e3==e4);
}
