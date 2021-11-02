#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../include/utils.hpp"


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

Query ** makeQueries(const char ** paths, int pathsNum) {
    Query ** qs = new Query*[pathsNum];
    for (int i = 0; i < pathsNum; ++i)
	qs[i] = new Query(i, paths[i]);

    return qs;
}

void destroyQueries(Query ** qs, int qNum) {
    for (int i = 0; i < qNum; ++i)
	delete qs[i];
    delete[] qs;
}

EntryList * makeEntryList(Query ** qs, int qNum) {
    time_t cur;
    cur = time(NULL);
    cout << "###########################\nBuilding entry list in: ";
    EntryList * eList = new EntryList();
    for (int i = 0; i < qNum; ++i)
	eList->insert(*qs[i]); 
    float elapsed = time(NULL) - cur;
    elapsed /= 60;
    cout << elapsed << " minutes\n###########################\n";
    return eList;
}

Index * makeIndex(MatchType type, EntryList * eList) {
    time_t cur;
    cur = time(NULL);
    cout << "---------------------------\nBuilding index in: ";
    Index * index = new Index(*eList, type); 
    float elapsed = time(NULL) - cur;
    elapsed /= 60;
    cout << elapsed << " minutes\n---------------------------\n";
    return index;
}

void search(Index * index, Word * word, int threshold) {
    List<Entry *> res = index->search(word, threshold);
    int len = res.getLen();
    for (int i = 0; i < len; ++i) {
	if (i > 0 && !(i % 10))
	    cout << endl;
	cout << res.getItem(i)->getWord().getStr();
	if (i < len-1)
	    cout << ", ";
    }
    cout << endl;
}

void multipleSearch(Index * index, Word ** words, int wordsNum, int threshold) {

    for (int i = 0; i < wordsNum; ++i) {
	time_t cur;
	cur = time(NULL);
	cout << "***************************\nSearching for : " << words[i]->getStr() << endl << "Results:\n";
	search(index, words[i], threshold);
	float elapsed = time(NULL) - cur;
	elapsed /= 60;
	cout << "In :" << elapsed << " minutes\n***************************\n";
    }

}

char * genRandStr(const int len) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    char * str = new char[len+1];

    for (int i = 0; i < len; ++i) 
        str[i] = alpha[rand() % (sizeof(alpha) - 1)];
    str[len] = '\0';

    return str;
}
