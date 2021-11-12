#include <gtest/gtest.h>
#include "../include/index.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class IndexTest: public ::testing::Test {
    protected:
	Index * editIndex = NULL;
	Index * hammingIndex = NULL;
	Index * exactIndex = NULL;
        int numOfEntries;
        Entry ** entryPtrs;//data for HashTable insertion

        virtual void SetUp() {
            this->hTable = new HashTable(7, djb2);
            this->entryPtrs = new Entry*[16];
            this->numOfEntries = 16;
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

