#include "../include/gtest.h"
#include "../include/index.hpp"
#include "../include/core.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class IndexTest: public ::testing::Test {
    protected:
        Index * editIndex = NULL;
        Index * hammingIndex = NULL;
        Index * exactIndex = NULL;
    int numOfQueries;
    int numOfEntries;
        EntryList * eList;
    Query ** qs;

        virtual void SetUp() {
            this->numOfEntries = 16;
            numOfQueries=4;
            eList = new EntryList(7);
            qs = new Query*[numOfQueries];
            for (int i = 0; i < numOfQueries; ++i) {
                        char path[64];
                        sprintf(path, "input/test_queries/query_%d", i);
                        qs[i] = new Query(i,path);
                eList->insert(*qs[i]);
            }
            this->editIndex = new Index(*eList, MT_EDIT_DIST);
            this->hammingIndex = new Index(*eList, MT_HAMMING_DIST);
            this->exactIndex = new Index(*eList, MT_EXACT_MATCH);
            IndexErrorCode errorVal;
        }

        void checkConstructor() {
            ASSERT_TRUE(editIndex->getType()==MT_EDIT_DIST);
            ASSERT_TRUE(hammingIndex->getType()==MT_HAMMING_DIST);
            ASSERT_TRUE(exactIndex->getType()==MT_EXACT_MATCH);
            char test_words[][16]={
                "a","word","is","here","hel","hll","ello","oop","trooper","shit","mastodon","helps","a","wolves"
            };
            //call eddit search with threshold 0 just to check that insert was done
            //BK_tree search  is already tested

                /* Edit check */
            for(int i=0;i<14;i++){
                Word * w = new Word(test_words[i]);
                Entry * e=new Entry(*w,0);
                List<Entry *> lst = editIndex->search(w, 0);
                    int len = lst.getLen();
                    ASSERT_TRUE(len == 1);
                ASSERT_TRUE(*e == *lst.getItem(0));
                delete e;
                delete w;
            }


                /* Hamming check */
            for(int i=0;i<14;i++){
                Word * w = new Word(test_words[i]);
                Entry * e=new Entry(*w,0);
                List<Entry *> lst = hammingIndex->search(w, 0);
                int len = lst.getLen();
                ASSERT_TRUE(len == 1);
                ASSERT_TRUE(*e == *lst.getItem(0));

                delete e;
                delete w;
            }
            {
                //search a word with bigger len than the biggest word
                //->must return empty list
                Word * w = new Word("aaaaaaaaaaaaaaaaaaaaaaa");
                Entry * e=new Entry(*w,0);
                List<Entry *> lst = hammingIndex->search(w, 0);
                int len = lst.getLen();
                ASSERT_TRUE(len == 0);
                delete e;
                delete w;
            }
            // exact search
            for(int i=0;i<14;i++){
                Word * w = new Word(test_words[i]);
                Entry * e=new Entry(*w,0);
                List<Entry *> lst = exactIndex->search(w, 0);
                    int len = lst.getLen();
                    ASSERT_TRUE(len == 1);
                ASSERT_TRUE(*e == *lst.getItem(0));
                delete e;
                delete w;
            }

        }

        virtual void TearDown() {
            delete this->editIndex;
            delete this->hammingIndex;
            delete this->exactIndex;
            for(int i=0;i<numOfQueries;i++)
                delete qs[i];
            delete[] qs;
            delete eList;
        }
};


TEST_F(IndexTest, ConstructorTest) {
    checkConstructor();
}

TEST_F(IndexTest, EmptyIndexTest) {
     EntryList eList(17);
     Index editIndex(eList, MT_EDIT_DIST);
     Index hammingIndex(eList, MT_HAMMING_DIST);
     Index exactIndex(eList, MT_EXACT_MATCH);

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
