#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "../include/utils.hpp"
#include "../include/entry_list.hpp"

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

Vector<char> * countQueries(ifstream & inFile, int * counter) {
    cout << "Counting queries...\n";
    Vector<char> * vec = new Vector<char>();
    *counter = 0;
    char c;
    while (!inFile.eof()) {
    	inFile.get(c);
	if (c == '\n') {
            vec->insert(c);
    	    inFile.get(c);
	    if (c == 's')
	        (*counter)++;
	}
        vec->insert(c);
    }
    cout << "Done---->Total queries: " << *counter << "\n";
    return vec;
}


	/*
Query ** makeQueries(Vector<char> & vec, int numOfQueries) {
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^\nReading queries..." << endl;

    Query ** qs = new Query*[numOfQueries];
    int i = 0;

    int start = 0;
    int end = 0;
    while (i < numOfQueries) {
	if (vec.getItem(end) == '\n' && ((vec.getItem(end+1) == 'e')
				          || (vec.getItem(end+1) == 'r'))
					  || (vec.getItem(end+1) == 'm')) {

	    cout << "Not a query skipped\n";
	    while (vec.getItem(end) != '\n' && vec.getItem(end+1) != 's')
		end++;
	    start = end++ +2;
	    continue;
	}
	while (vec.getItem(end) != '\n' || vec.getItem(end+1) != 's')
	    end++;
	cout << "start: " <<  start << " end: " << end << endl;
	qs[i] = new Query(i, vec, start);
	qs[i]->print();
	++i;
	start = end++ +2;
    }

    cout << "Done!\n^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    return qs;
}
	*/

Query ** makeQueries(char ** paths, int pathsNum) {
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^\nReading queries..." << endl;
    Query ** qs = new Query*[pathsNum];
    for (int i = 0; i < pathsNum; ++i)
	qs[i] = new Query(i, paths[i]);
    cout << "Done!\n^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

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
    // This is the correct one
    EntryList * eList = new EntryList(qNum*MAX_QUERY_WORDS);
    // EntryList * eList = new EntryList(10000);
    for (int i = 0; i < qNum; ++i)
	eList->insert(*qs[i]);
    float elapsed = time(NULL) - cur;
    elapsed /= 60;
    cout << elapsed << " minutes\n###########################\n\n";
    return eList;
}

Index * makeIndex(MatchType type, EntryList * eList) {
    time_t cur;
    cur = time(NULL);
    if (type == MT_HAMMING_DIST)
    	cout << "---------------------------\nBuilding hamming-distance index in: ";
    else if (type == MT_EDIT_DIST)
    	cout << "---------------------------\nBuilding edit-distance index in: ";
    else
    	cout << "---------------------------\nBuilding exact-match index in: ";
    Index * index = new Index(*eList, type);
    float elapsed = time(NULL) - cur;
    elapsed /= 60;
    cout << elapsed << " minutes\n---------------------------\n\n";
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

    if (index->getType() == MT_HAMMING_DIST)
    	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nSearching in hamming-distance index:\n";
    else if (index->getType() == MT_EDIT_DIST)
    	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nSearching in edit-distance index:\n";
    else
    	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nSearching in exact-match index:\n";
    for (int i = 0; i < wordsNum; ++i) {
	time_t cur;
	cur = time(NULL);
	cout << "***************************\nSearching for : " << words[i]->getStr() << endl << "Results:\n";
	search(index, words[i], threshold);
	float elapsed = time(NULL) - cur;
	elapsed /= 60;
	cout << "In :" << elapsed << " minutes\n***************************\n";
    }
    cout << endl;
}

char * genRandStr(const int len) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    char * str = new char[len+1];

    /* this one is because the query files for input have words staring with a mostly */
    /* without it search will give empty results */
    str[0] = 'a';
    for (int i = 1; i < len; ++i)
        str[i] = alpha[rand() % (sizeof(alpha) - 1)];
    str[len] = '\0';

    return str;
}
