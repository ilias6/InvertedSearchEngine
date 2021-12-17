#include "../include/queue.hpp"
#include "../include/gtest.h"

TEST(QueueTest, Push) {
    Queue<int> q;
    for (int i = 0; i < 12; ++i){
        q.push(i);
        ASSERT_TRUE(q.getList().getLen()==i+1);
        ASSERT_TRUE(q.getList().getItem(i)==i);
        ASSERT_TRUE(q.getList().getItem(0)==0);
    }
    for (int i = 0; i < 12; ++i) {
        int n = q.pop();
        EXPECT_TRUE(n == i);
    }

}

TEST(QueueTest, Pop) {
    Queue<int> q;
    for (int i = 0; i < 12; ++i){
        q.push(i);
        ASSERT_TRUE(q.getList().getLen()==i+1);
        ASSERT_TRUE(q.getList().getItem(i)==i);
        ASSERT_TRUE(q.getList().getItem(0)==0);
    }
    for (int i = 0; i < 12; ++i) {
        int n = q.pop();
        EXPECT_TRUE(n == i);
    }
    EXPECT_THROW({
        try{
            q.pop();
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);

}
