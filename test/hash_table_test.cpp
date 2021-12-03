#include "../include/hash_table.hpp"
#include "../include/gtest.h"
#include "../include/hash_functions.hpp"
#include "../include/entry.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class HashTableTest: public ::testing::Test {
    protected:
        HashTable * hTable = NULL;
        int numOfEntries;
        Entry ** entryPtrs;//data for HashTable insertion

        virtual void SetUp() {
            this->hTable = new HashTable(1, djb2);
                ASSERT_TRUE(this->hTable->getSize() == 1);
            this->numOfEntries = 16;
            this->entryPtrs = new Entry*[this->numOfEntries];
            HashTableErrorCode errorVal;
            const char strArr[][5]={"aaa", "aab", "abb", "aba", "baa", "bab",
                "bba", "bbb", "aa", "e", "dj", "test", "ing", "my", "clas", "ses"};
            for(int i = 0; i < numOfEntries; i++) {
                PayloadEntry p(i,0,MT_EXACT_MATCH,2,NULL);
                this->entryPtrs[i] = new Entry(strArr[i], p);
                errorVal = this->hTable->insert(entryPtrs[i]);
                ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
		if (i == 2)
		    ASSERT_TRUE(5 == this->hTable->getSize());//succesful insert
		if (i == 8)
		    ASSERT_TRUE(23 == this->hTable->getSize());//succesful insert
            }
        }

        void checkInsert(HashTable * hTable, int indx, Entry ** entryPtrs, HashTableErrorCode errorVal) {
            ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
                Entry * res = this->hTable->getEntry(&entryPtrs[indx]->getWord());
            ASSERT_TRUE(entryPtrs[indx] == res);
        }

        virtual void TearDown() {
            delete this->hTable;
            for(int i = 0; i < numOfEntries; i++)
                delete entryPtrs[i];
            delete[] entryPtrs;
        }
};

TEST_F(HashTableTest, CopyConstructorTest) {
    HashTable t(*this->hTable);

    for(int i = 0; i < numOfEntries; i++) {
        Entry * res1 = this->hTable->getEntry(&entryPtrs[i]->getWord());
        Entry * res2 = t.getEntry(&entryPtrs[i]->getWord());
        ASSERT_TRUE(res1 == res2);
    }
}

TEST_F(HashTableTest, InsertTest) {
    for(int i = 0; i < numOfEntries; i++)
        checkInsert(this->hTable, i, entryPtrs, H_T_SUCCESS);
}

TEST_F(HashTableTest, updateEntryPayload) {
    for (int i = 0; i < this->numOfEntries; ++i) {
        Entry * e;
        PayloadEntry p(i+1,0,MT_EXACT_MATCH,2,NULL);
        HashTableErrorCode errorVal = this->hTable->updateEntryPayload(&entryPtrs[i]->getWord(), p);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful update
        int n1 = 57;
        p.setPayloadEntry(n1,0,MT_EXACT_MATCH,2,NULL);

        errorVal = this->hTable->updateEntryPayload(&entryPtrs[i]->getWord(), p);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful update

        Entry * ePtrHTable = this->hTable->getEntry(&this->entryPtrs[i]->getWord());
        List <PayloadEntry> payload2(ePtrHTable->getPayload());

        List <PayloadEntry> payload1;
        p.setPayloadEntry(i,0,MT_EXACT_MATCH,2,NULL);
        payload1.insert(p);
        int n2 = i+1;
        p.setPayloadEntry(n2,0,MT_EXACT_MATCH,2,NULL);
        payload1.insert(p);
        p.setPayloadEntry(n1,0,MT_EXACT_MATCH,2,NULL);
        payload1.insert(p);
        int len = payload1.getLen();

        ASSERT_TRUE(len == payload2.getLen());
        for (int j = 0; j < len; ++j)
            ASSERT_TRUE(payload1.getItem(j) == payload2.getItem(j));
    }
}

TEST(BucketTest, getEntry) {
    Bucket b;
    List<Entry> entryList;

    Word w("test");
    Entry * ePtrBucket = b.getEntry(&w);
    ASSERT_TRUE(ePtrBucket == NULL);

    const char strArr[][5]={"aaa", "aab", "abb", "aba", "baa", "bab",
    "bba", "bbb", "aa", "e", "dj", "test", "ing", "my", "clas", "ses"};

    for (int i = 0; i < 16; ++i) {
        PayloadEntry p(i,0,MT_EXACT_MATCH,2,NULL);
        Entry e(strArr[i], p);
        Entry * ePtrOrigin = NULL;
        entryList.insert(e, &ePtrOrigin);
        HashTableErrorCode errorVal = b.insert(ePtrOrigin);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
        ASSERT_TRUE(i+1 == b.bucketSize());
        Entry * ePtrBucket = b.getEntry(&e.getWord());
        ASSERT_TRUE(ePtrBucket == ePtrOrigin);
    }

    ePtrBucket = b.getEntry(&w);
    Entry * ePtrOrigin = entryList.getItemPtr(11);
    ASSERT_TRUE(ePtrBucket == ePtrOrigin);

    Word w2("testing");
    ePtrBucket = b.getEntry(&w2);
    ASSERT_TRUE(ePtrBucket == NULL);
}

TEST(BucketTest, Insert) {
    Bucket b;
    List<Entry> entryList;

    const char strArr[][5]={"aaa", "aab", "abb", "aba", "baa", "bab",
    "bba", "bbb", "aa", "e", "dj", "test", "ing", "my", "clas", "ses"};

    for (int i = 0; i < 16; ++i) {
        PayloadEntry p(i,0,MT_EXACT_MATCH,2,NULL);
        Entry e(strArr[i], p);
        Entry * ePtrOrigin = NULL;
        entryList.insert(e, &ePtrOrigin);
        HashTableErrorCode errorVal = b.insert(ePtrOrigin);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
        Vector<Entry *> lst = b.getListCopy();
        ASSERT_TRUE(i+1 == lst.getLen());
        Entry * ePtrBucket = lst.getItem(i);
        ASSERT_TRUE(ePtrBucket == ePtrOrigin);
    }
}
//in other words bucket is just a list....
