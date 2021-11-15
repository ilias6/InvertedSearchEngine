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
            this->hTable = new HashTable(7, djb2);
                ASSERT_TRUE(this->hTable->getSize() == 7);
            this->numOfEntries = 16;
            this->entryPtrs = new Entry*[this->numOfEntries];
            HashTableErrorCode errorVal;
            const char strArr[][5]={"aaa", "aab", "abb", "aba", "baa", "bab",
                "bba", "bbb", "aa", "e", "dj", "test", "ing", "my", "clas", "ses"};
            for(int i = 0; i < numOfEntries; i++) {
                this->entryPtrs[i] = new Entry(strArr[i], i);
                errorVal = this->hTable->insert(entryPtrs[i]);
                ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
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

/* Bucket::getEntry needs to be tested only*/
/*

TEST_F(HashTableTest, GetEntry) {       Bucket getBucketCopy(Word *);
    const char strArr[][5]={"aaa", "aab", "abb", "aba", "baa", "bab",
    "bba", "bbb", "aa", "e", "dj", "test", "ing", "my", "clas", "ses"};

    HashTable hTable(7, djb2);
    List<Entry> entryList;
    for (int i = 0; i < this->numOfEntries; ++i) {
        Entry e(strArr[i], i);
        entryList.insert(e);
        Entry * ePtrOrigin = &entryList.getItem(i);
        HashTableErrorCode errorVal = hTable.insert(ePtrOrigin);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
        Entry * ePtrHTable = hTable.getEntry(&e.getWord());
        ASSERT_TRUE(ePtrHTable == ePtrOrigin);
    }

    const char strArr2[][5]={"aaaa", "ab", "bb", "b", "a", "baba",};
    for (int i = 0; i < 6; ++i) {
        Entry e(strArr2[i], i);
        Entry * ePtrHTable = hTable.getEntry(&e.getWord());
        ASSERT_TRUE(ePtrHTable == NULL);
    }
}

*/

TEST_F(HashTableTest, updateEntryPayload) {
    for (int i = 0; i < this->numOfEntries; ++i) {
        HashTableErrorCode errorVal = this->hTable->updateEntryPayload(&entryPtrs[i]->getWord(), i+1);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful update
        int n1 = 57;
        errorVal = this->hTable->updateEntryPayload(&entryPtrs[i]->getWord(), n1);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful update

        Entry * ePtrHTable = this->hTable->getEntry(&this->entryPtrs[i]->getWord());
        List <int> payload2(ePtrHTable->getPayload());

        List <int> payload1;
        payload1.insert(i);
        int n2 = i+1;
        payload1.insert(n2);
        payload1.insert(n1);
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
        Entry e(strArr[i], i);
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
        Entry e(strArr[i], i);
        Entry * ePtrOrigin = NULL;
        entryList.insert(e, &ePtrOrigin);
        HashTableErrorCode errorVal = b.insert(ePtrOrigin);
        ASSERT_TRUE(errorVal == H_T_SUCCESS);//succesful insert
        List <Entry *> lst = b.getListCopy();
        ASSERT_TRUE(i+1 == lst.getLen());
        Entry * ePtrBucket = lst.getItem(i);
        ASSERT_TRUE(ePtrBucket == ePtrOrigin);
    }
}
//in other words bucket is just a list....
