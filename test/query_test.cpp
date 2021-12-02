#include "../include/query.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>

using namespace std;

class QueryTest: public ::testing::Test {
    protected:
        Query * q;
        virtual void SetUp() {
            q = new Query(0, "4 a word is here", MT_EXACT_MATCH, 0);
        }

        virtual void TearDown() {
            delete q;
        }
};

TEST_F(QueryTest, ConstructorTestNormal) {
    ASSERT_TRUE(q->getWordsInQuery() == 4);
    ASSERT_TRUE(q->getId() == 0);
    ASSERT_TRUE(q->getType() == MT_EXACT_MATCH);
    ASSERT_TRUE(q->getActive());
    q->deactivate();
    ASSERT_FALSE(q->getActive());
    q->activate();
    ASSERT_TRUE(q->getActive());
    ASSERT_TRUE(q->getMatchDist() == 0);
    const char strArr[][8] = {"a", "word", "is", "here"};
    for (int i = 0; i < 4; ++i) {
        Word * w = q->getWord(i);
        ASSERT_TRUE(strcmp(w->getStr(), strArr[i]) == 0);
    }

}
