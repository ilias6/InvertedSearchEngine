#include "../include/document.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class DocumentTest: public ::testing::Test {
    protected:
        Document ** doc_arr;
        int size;
        virtual void SetUp() {
;
        }

        virtual void TearDown() {
		/*
            for(int i=0;i<size;i++)
                delete doc_arr[i];
            delete[] doc_arr;
	    */;
        }
};

TEST_F(DocumentTest,ConstructorTest){
    this->size=3;//3 docs
    this->doc_arr=new Document*[this->size];
    const char * arr[]={"9 6243 http dbpedia resource list people from minnesota http",
    "2 ok ok","10 a b c a b c a b c cc"};
    for(int i=0;i<this->size;i++){
        this->doc_arr[i]=new Document(i,arr[i]);
        ASSERT_TRUE(i==this->doc_arr[i]->getId());
    }
    ASSERT_TRUE(8==this->doc_arr[0]->getWordsInDoc());
    ASSERT_TRUE(1==this->doc_arr[1]->getWordsInDoc());
    ASSERT_TRUE(4==this->doc_arr[2]->getWordsInDoc());
    Word * w2=new Word("6243");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[0]->getWord(0))));
    w2->set("http");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[0]->getWord(1))));
    w2->set("resource");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[0]->getWord(3))));
    w2->set("minnesota");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[0]->getWord(7))));

    w2->set("ok");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[1]->getWord(0))));
    ASSERT_TRUE(this->doc_arr[1]->getWord(1)==NULL);
    ASSERT_TRUE(this->doc_arr[1]->getWord(2)==NULL);
    w2->set("a");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[2]->getWord(0))));
    w2->set("b");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[2]->getWord(1))));
    w2->set("c");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[2]->getWord(2))));
    w2->set("cc");
    ASSERT_TRUE(w2->exactMatch(*(this->doc_arr[2]->getWord(3))));



    delete w2;
    for(int i=0;i<this->size;i++)
        delete this->doc_arr[i];
    delete[] this->doc_arr;
}
