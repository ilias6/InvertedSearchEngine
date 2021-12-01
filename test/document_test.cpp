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

        }

        virtual void TearDown() {
		/*
            for(int i=0;i<size;i++)
                delete doc_arr[i];
            delete[] doc_arr;
	    */
        }
};

TEST_F(DocumentTest,ConstructorTest){
    this->size=3;//3 docs
    const char * arr[]={"2 6243 http dbpedia resource list people from minnesota http"};
}
