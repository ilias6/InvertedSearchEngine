#include <gtest/gtest.h>
#include "../include/entry_list.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryListTest: public ::testing::Test {
    protected:
	EntryList * eList;
	Query ** qs;
        virtual void SetUp() {
	    eList = new eList(7);	
	    qs = new Query*[4];
	    for (int i = 0; i < 4; ++i) {
		char path[64];
		sprintf(path, "../input/test_queries/query_%d", i);
		qs[i] = new Query(path, i);
		eList->insert(*qs[i]);
	    }
	}

        virtual void TearDown() {
	    for (int i = 0; i < 4; ++i)
		delete qs[i];
	    delete[] qs;
	    delete eList;
        }
};

//TEST_F(EntryListTest, )
