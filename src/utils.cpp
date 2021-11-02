#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;


bool isPrime(int n) {
    if (n % 2 == 0)
	return false;

    for (int i = 3; i < n/2; i += 2)
	if (n % i == 0)
	    return false;

    return true;

}

int findNextPrime(int n) {
    int canditatePrime = n;
    while (!isPrime(canditatePrime))
	canditatePrime++;
    return canditatePrime;

}

bool charInWhitespace(char c){
    if(c=='\n'||c=='\t'||c==' '||c=='\f'||c=='\r')
        return true;
    return false;
}

Query ** makeQueries(const char ** paths) {


}

EntryList * makeEntryList(Query ** qs) {


}

Index * makeIndex(MatchType type, EntryList * eList) {
    

}

void search(Index * index, Word * word) {


}

void multipleSearch(Index * index, Word ** words, int wordsNum) {
   for (int i = 0; i < wordsNum; ++i) {
	search(index, words[i]);
    }

}
