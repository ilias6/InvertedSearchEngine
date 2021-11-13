#include <gtest/gtest.h>
#include "../include/entry.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class EntryTest: public ::testing::Test {
    protected:
	Entry * e;
	int * payload; 	
        virtual void SetUp() {
	    Word w("abcd");
	    e = new Entry(w, 0);
	    ASSERT_TRUE(1 == e->getPayload().getLen());
	    ASSERT_TRUE(0 == e->getPayload().getItem(0));
	    payload = new int[4];
	    for (int i = 0; i < 4; ++i) {
		payload[i] = i+10;
		e->addToPayload(payload[i]);
	    }
        }

        virtual void TearDown() {
	    delete e;
	    delete[] payload;
        }
};

