#include <gtest/gtest.h>
#include "../include/entry_list.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryListTest: public ::testing::Test {
    protected:
	EntryList * eList;
	Query ** qs;
    int numOfQueries;
        virtual void SetUp() {
    	    eList = new EntryList(7);
            numOfQueries=4;
    	    qs = new Query*[numOfQueries];
    	    for (int i = 0; i < numOfQueries; ++i) {
    		char path[64];
    		sprintf(path, "../input/test_queries/query_%d", i);
    		qs[i] = new Query(i,path);
    		eList->insert(*qs[i]);
	    }
	}

        virtual void TearDown() {
	    for (int i = 0; i < numOfQueries; ++i)
		delete qs[i];
	    delete[] qs;
	    delete eList;
        }
};

//TEST_F(EntryListTest, )
