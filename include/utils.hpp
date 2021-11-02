#ifndef __UTILS_HPP__
#define __UTILS_HPP__
bool isPrime(int);
int findNextPrime(int);
bool charInWhitespace(char c);
Query ** makeQuerries(const char **);
Index * makeIndex(MatchType, EntryList *);
void multipleSearch(Word **);
void search(Word *);
EntryList * makeEntryList(Query **);
#endif
