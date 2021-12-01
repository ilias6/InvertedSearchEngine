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


ErrorCode StartQuery(QueryID, const char *, MatchType, unsigned int);

bool isPrime(int);
int findNextPrime(int);
bool charInWhitespace(char c);
//Query ** makeQueries(Vector<char> &, int);
Vector<char> * countQueries(ifstream &, int *);
Query ** makeQueries(char **, int);
void destroyQueries(Query **, int);
int getNumOfQueriesFromFd();
/*
Index * makeIndex(MatchType, EntryList *);
void multipleSearch(Index *, Word **, int, int threshold=0);
void search(Index *, Word *, int threshold=0);
EntryList * makeEntryList(Query **, int);
*/
char * genRandStr(const int);

#endif
