#include "../include/queue.hpp"
#include "../include/gtest.h"

TEST(QueueTest, Push) {
    Queue<int> q;
    for (int i = 0; i < 12; ++i){
	q.push(i);
	ASSERT_TRUE(q.getVector().getLen()==i+1);
	ASSERT_TRUE(q.getVector().getItem(i)==i);	
	ASSERT_TRUE(q.getVector().getItem(0)==0);	
    }
    for (int i = 0; i < 12; ++i) {
	int n = q.pop();
	cout << n << " " << i << endl;
	EXPECT_TRUE(n == i);
    }

}
