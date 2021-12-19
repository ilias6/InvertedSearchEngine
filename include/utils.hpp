#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <fstream>

#include "query.hpp"
#include "vector.hpp"
#include "hash_table.hpp"


bool isPrime(int);
int findNextPrime(int);
bool charInWhitespace(char c);
int countSpaces(const char *);
int getNumOfQueriesFromFd();//haha NO
int scan(int,const char*,Word ***,int *,int,int);
Query * biSearchQuery(Vector<Query *> *, QueryID);//returns query pointer
int biSearchQueryIndex(Vector<Query *> *, QueryID);//returns index
char * genRandStr(const int);
bool satisfy(bool *, int);

#endif
