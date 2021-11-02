#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "index.hpp"
#include "word.hpp"
#include "entry.hpp"
#include "entry_list.hpp"
#include "core.hpp"
#include "query.hpp"


bool isPrime(int);
int findNextPrime(int);
bool charInWhitespace(char c);
Query ** makeQueries(const char **, int);
void destroyQueries(Query **, int);
Index * makeIndex(MatchType, EntryList *);
void multipleSearch(Index *, Word **, int, int);
void search(Index *, Word *, int);
EntryList * makeEntryList(Query **, int);
char * genRandStr(const int);
#endif
