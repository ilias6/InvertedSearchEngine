#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "index.hpp"
#include "word.hpp"
#include "entry.hpp"
#include "entry_list.hpp"
#include "core.hpp"
#include "query.hpp"
#include "vector.hpp"
#include <fstream>
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

#endif
