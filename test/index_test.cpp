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
	EntryList * eList;

        virtual void SetUp() {
            this->numOfEntries = 16;
            const char strArr[][5]={"aaa", "aab", "abb", "aba", "baa", "bab",
		"bba", "bbb", "aa", "e", "dj", "test", "ing", "my", "clas", "ses"};
	    this->eList = new EntryList(7);
            for(int i = 0; i < numOfEntries; i++) {
                Entry e(strArr[i], i);
                this->eList->insert(e);
            }
            this->editIndex = new Index(*eList, MT_EDIT_DIST);
            this->hammingIndex = new Index(*eList, MT_HAMMING_DIST);
            this->exactIndex = new Index(*eList, MT_EXACT_MATCH);
            IndexErrorCode errorVal;
        }

        virtual void TearDown() {
            delete this->editIndex;
            delete this->hammingIndex;
            delete this->exactIndex;
            delete eList;
        }
};

TEST(IndexTest, EmptyIndex) {
    EntryList eList(17);
    Index editIndex(eList, MT_EDIT_DIST);

}
