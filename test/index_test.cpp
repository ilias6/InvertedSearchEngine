#include "../include/gtest.h"
#include "../include/index.hpp"
#include "../include/core.hpp"
#include "../include/utils.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class IndexTest: public ::testing::Test {
    protected:
        Index * editIndex = NULL;
        Index * hammingIndex = NULL;
        Index * exactIndex = NULL;

        virtual void SetUp() {
            this->editIndex = new Index(MT_EDIT_DIST, 5);
            this->hammingIndex = new Index(MT_HAMMING_DIST, 5);
            this->exactIndex = new Index(MT_EXACT_MATCH, 5);
        }

        virtual void TearDown() {
            delete this->editIndex;
            delete this->hammingIndex;
            delete this->exactIndex;
        }
};

TEST_F(IndexTest, SimpleIndexTest) {
	Entry ** entryPtrs = new Entry*[6];
	PayloadEntry pL(0, NULL);
	for (int i = 0; i < 5; ++i) {
		char * str = genRandStr(16);
		entryPtrs[i] = new Entry(str, pL, MT_EXACT_MATCH, 0);
		delete[] str;
	}
	entryPtrs[5] = NULL;

	this->editIndex->insert(entryPtrs);

	// IndexErrorCode err;
	for (int i = 0; i < 5; ++i) {
		List<Entry *> res = this->editIndex->search(&entryPtrs[i]->getWord(), 0);
		ASSERT_TRUE(res.getLen() == 1);
		ASSERT_TRUE(res.getItem(0) == entryPtrs[i]);
	}
	this->hammingIndex->insert(entryPtrs);
	for (int i = 0; i < 5; ++i) {
		List<Entry *> res = this->hammingIndex->search(&entryPtrs[i]->getWord(), 0);
		ASSERT_TRUE(res.getLen() == 1);
		ASSERT_TRUE(res.getItem(0) == entryPtrs[i]);
	}
	this->exactIndex->insert(entryPtrs);
	for (int i = 0; i < 5; ++i) {
		List<Entry *> res = this->exactIndex->search(&entryPtrs[i]->getWord(), 0);
		ASSERT_TRUE(res.getLen() == 1);
		ASSERT_TRUE(res.getItem(0) == entryPtrs[i]);
	}
	for (int i = 0; i < 5; ++i) {
		delete entryPtrs[i];
	}
	delete[] entryPtrs;

}

TEST_F(IndexTest, EmptyIndexTest) {
     Index editIndex(MT_EDIT_DIST, 3);
     Index hammingIndex(MT_HAMMING_DIST, 3);
     Index exactIndex(MT_EXACT_MATCH, 3);

     Word * w = new Word("abcd");
     List<Entry *> lst = editIndex.search(w);
     int len = lst.getLen();
     ASSERT_TRUE(len == 0);
     lst = hammingIndex.search(w);
     len = lst.getLen();
     ASSERT_TRUE(len == 0);
     lst = exactIndex.search(w);
     len = lst.getLen();
     ASSERT_TRUE(len == 0);

     delete w;

     w = new Word("");
     lst = editIndex.search(w);
      len = lst.getLen();
     ASSERT_TRUE(len == 0);
     lst = hammingIndex.search(w);
     len = lst.getLen();
     ASSERT_TRUE(len == 0);
     lst = exactIndex.search(w);
     len = lst.getLen();
     ASSERT_TRUE(len == 0);

     delete w;
 }
