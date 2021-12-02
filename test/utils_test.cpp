#include "../include/utils.hpp"
#include "../include/gtest.h"


TEST(UtilsisPrimeTest, NotPrime) {
    int nums[] = {0, -2, 10, -80, 54280};
    for (int i = 0; i < 5; ++i)
	ASSERT_TRUE(false == isPrime(nums[i]));
}

TEST(UtilsisPrimeTest, Prime) {
    int nums[] = {3, 7, 83, 7919};
    for (int i = 0; i < 4; ++i)
	ASSERT_TRUE(true == isPrime(nums[i]));
}

TEST(UtilsfindNextPrimeTest, Simple) {
    int n = 54280;
    int p = findNextPrime(n);
    for (int i = n; i < p; ++i)
	ASSERT_TRUE(false == isPrime(i));
}

TEST(UtilsfindNextPrimeTest, SameNum) {
    int n = 7919;
    int p = findNextPrime(n);
    ASSERT_TRUE(n == p);
}

TEST(UtilsBiSearchQuery, FoundSimple) {
    Vector<Query *> queries;
    Query ** qs = new Query*[27];
    for (int i = 0; i < 27; ++i) {
	qs[i] = new Query(i, "1 word", MT_EXACT_MATCH, 0);
	queries.insert(qs[i]);
    }

    Query * qPtr = biSearchQuery(&queries, 5);
    ASSERT_TRUE(qPtr->getId() == 5);
    qPtr = biSearchQuery(&queries, 15);
    ASSERT_TRUE(qPtr->getId() == 15);
    qPtr = biSearchQuery(&queries, 20);
    ASSERT_TRUE(qPtr->getId() == 20);
    qPtr = biSearchQuery(&queries, 16);
    ASSERT_TRUE(qPtr->getId() == 16);
    qPtr = biSearchQuery(&queries, 24);
    ASSERT_TRUE(qPtr->getId() == 24);
    qPtr = biSearchQuery(&queries, 26);
    ASSERT_TRUE(qPtr->getId() == 26);
    qPtr = biSearchQuery(&queries, 0);
    ASSERT_TRUE(qPtr->getId() == 0);

    for (int i = 0; i < 27; ++i)
	delete qs[i];
    delete[] qs;
}

TEST(UtilsBiSearchQuery, FoundComplex) {
    Vector<Query *> queries;
    Query ** qs = new Query*[256];
    for (int i = 0; i < 256; ++i) {
	qs[i] = new Query(i*2, "1 word", MT_EXACT_MATCH, 0);
	queries.insert(qs[i]);
    }
    
    for (int i = 0; i < 128; ++i) {
	int n = (rand() % 256)*2;
	Query * qPtr = biSearchQuery(&queries, n);
	ASSERT_TRUE(qPtr->getId() == n);
    }

    for (int i = 0; i < 256; ++i)
	delete qs[i];
    delete[] qs;
}

TEST(UtilsBiSearchQuery, NotFoundSimple) {
    Vector<Query *> queries;
    Query ** qs = new Query*[27];
    for (int i = 0; i < 27; ++i) {
	qs[i] = new Query(i, "1 word", MT_EXACT_MATCH, 0);
	queries.insert(qs[i]);
    }

    Query * qPtr = biSearchQuery(&queries, -1);
    ASSERT_TRUE(qPtr == NULL);
    qPtr = biSearchQuery(&queries, 28);
    ASSERT_TRUE(qPtr == NULL);

    for (int i = 0; i < 27; ++i)
	delete qs[i];
    delete[] qs;
}

TEST(UtilsBiSearchQuery, NotFoundComplex) {
    Vector<Query *> queries;
    Query ** qs = new Query*[256];
    for (int i = 0; i < 256; ++i) {
	qs[i] = new Query(i*2, "1 word", MT_EXACT_MATCH, 0);
	queries.insert(qs[i]);
    }
    
    for (int i = 0; i < 128; ++i) {
	int n = (rand() % 256)*2 +1;
	Query * qPtr = biSearchQuery(&queries, n);
	ASSERT_TRUE(qPtr == NULL);
    }

    for (int i = 0; i < 256; ++i)
	delete qs[i];
    delete[] qs;
}

TEST(UtilsScanTest,ScanTest) {
    const char * arr[5]={"10 20 30","prwth deuterh trith tetarth","not not notnot notnot",
"MORETHANMAXWOR","a"};
    int max_word_length=10;
    int min_word_length=2;

    Word ** word_arr;
    int unique_words;
    ASSERT_TRUE(0==scan(3,arr[0],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==3);
    Word *w=new Word("10");
    ASSERT_TRUE(word_arr[0]->exactMatch(*w));
    w->set("20");
    ASSERT_TRUE(word_arr[1]->exactMatch(*w));
    w->set("30");
    ASSERT_TRUE(word_arr[2]->exactMatch(*w));

    for(int i=0;i<unique_words;i++)
        delete word_arr[i];
    delete[] word_arr;

// -2 means corrupted;
    ASSERT_TRUE(-2==scan(4,arr[0],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==0);
    ASSERT_TRUE(word_arr==NULL);


    ASSERT_TRUE(0==scan(4,arr[1],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==4);
    w->set("prwth");
    ASSERT_TRUE(word_arr[0]->exactMatch(*w));
    w->set("deuterh");
    ASSERT_TRUE(word_arr[1]->exactMatch(*w));
    w->set("trith");
    ASSERT_TRUE(word_arr[2]->exactMatch(*w));
    w->set("tetarth");
    ASSERT_TRUE(word_arr[3]->exactMatch(*w));
    for(int i=0;i<unique_words;i++)
        delete word_arr[i];
    delete[] word_arr;

    ASSERT_TRUE(-2==scan(5,arr[1],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==0);
    ASSERT_TRUE(word_arr==NULL);

    ASSERT_TRUE(0==scan(4,arr[2],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==2);
    w->set("not");
    ASSERT_TRUE(word_arr[0]->exactMatch(*w));
    w->set("notnot");
    ASSERT_TRUE(word_arr[1]->exactMatch(*w));


    for(int i=0;i<unique_words;i++)
        delete word_arr[i];
    delete[] word_arr;

    ASSERT_TRUE(-2==scan(10,arr[2],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==0);
    ASSERT_TRUE(word_arr==NULL);

// -1 indicates tha word is bigger than max words
    ASSERT_TRUE(-1==scan(1,arr[3],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==0);
    ASSERT_TRUE(word_arr==NULL);

    // -1 indicates tha word is smaller than max words
    ASSERT_TRUE(-3==scan(1,arr[4],&word_arr,&unique_words,max_word_length,min_word_length));
    ASSERT_TRUE(unique_words==0);
    ASSERT_TRUE(word_arr==NULL);
    delete w;
}
