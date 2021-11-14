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

	void checkConstructor() {
	    Word * w = new Word("aa");
	    /* Edit check */
	    List<Entry *> lst = editIndex->search(w, 1);
	    int len = lst.genLen();
	    ASSERT_EQ(len == 5);
	    Entry * e = new Entry(w, 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;
	    e = new Entry("aaa", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;
	    e = new Entry("aba", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;
	    e = new Entry("baa", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;
	    e = new Entry("aab", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;

	    delete w;

	    /* Hamming check */
	    w = new Word("aj");
	    lst = hammingIndex->search(w, 1);
	    int len = lst.genLen();
	    ASSERT_EQ(len == 2);
	    e = new Entry("aa", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;
	    e = new Entry("dj", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;

	    delete w;

	    /* Exact check */
	    w = new Word("aaa");
	    lst = exactIndex->search(w);
	    int len = lst.genLen();
	    ASSERT_EQ(len == 1);
	    e = new Entry("aaa", 0);
	    ASSERT_EQ(true == lst.exists(e))
	    delete e;

	    delete w;
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
    Index hammingIndex(eList, MT_HAMMING_DIST);
    Index exactIndex(eList, MT_EXACT_DIST);
    
    Word * w = new Word("abcd");
    List<Entry *> lst = editIndex.search(w);
    int len = lst.getLen();
    ASSERT_EQ(len == 0);
    lst = hammingIndex.search(w);
    len = lst.getLen();
    ASSERT_EQ(len == 0);
    lst = exactIndex.search(w);
    len = lst.getLen();
    ASSERT_EQ(len == 0);

    delete w;
    w = new Word("");
    lst = editIndex.search(w);
    len = lst.getLen();
    ASSERT_EQ(len == 0);
    lst = hammingIndex.search(w);
    len = lst.getLen();
    ASSERT_EQ(len == 0);
    lst = exactIndex.search(w);
    len = lst.getLen();
    ASSERT_EQ(len == 0);
}
