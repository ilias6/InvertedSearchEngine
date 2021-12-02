#include "../include/utils.hpp"
#include "../include/gtest.h"


TEST(isPrimeTest, NotPrime) {
    int nums[] = {0, -2, 10, -80, 54280};
    for (int i = 0; i < 5; ++i)
	ASSERT_TRUE(false == isPrime(nums[i]));
}

TEST(isPrimeTest, Prime) {
    int nums[] = {3, 7, 83, 7919};
    for (int i = 0; i < 4; ++i)
	ASSERT_TRUE(true == isPrime(nums[i]));
}

TEST(findNextPrimeTest, Simple) {
    int n = 54280;
    int p = findNextPrime(n);
    for (int i = n; i < p; ++i)
	ASSERT_TRUE(false == isPrime(i));
}

TEST(findNextPrimeTest, SameNum) {
    int n = 7919;
    int p = findNextPrime(n);
    ASSERT_TRUE(n == p);
}

TEST(UtilsScanTest,ScanTest) {
    ;
}
