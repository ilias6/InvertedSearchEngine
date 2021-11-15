#include "../include/query.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>

using namespace std;

class QueryTest: public ::testing::Test {
    protected:
        Query * q;
        virtual void SetUp() {
            q = new Query(0, "./input/test_queries/query_0");
        }

        virtual void TearDown() {
            delete q;
        }
};

TEST_F(QueryTest, ConstructorTest) {
    ASSERT_TRUE(q->getWordsInQuery() == 4);
    ASSERT_TRUE(q->getId() == 0);
    const char strArr[][8] = {"a", "word", "is", "here"};
    for (int i = 0; i < 4; ++i) {
        Word * w = q->getWord(i);
        ASSERT_TRUE(strcmp(w->getStr(), strArr[i]) == 0);
    }

}
