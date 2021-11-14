#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include "../include/document.hpp"
#include "../include/core.hpp"
#include "../include/query.hpp"
#include "../include/BK_tree.hpp"
#include "../include/index.hpp"
#include "../include/utils.hpp"
#include "../include/entry_list.hpp"
#include <unistd.h>
#include <cstring>
#include <fstream>

using namespace std;


int main(int argc, char * argv[]) {
    if (argc < 3)
	return -1;

    int numOfQueries = stoi(argv[2]);
    int l = strlen(argv[1]);
    char ** paths = new char*[numOfQueries];
    for (int i = 0; i < numOfQueries; ++i) {
    	paths[i] = new char[32];
	if (argv[1][l-1] == '/')
	    sprintf(paths[i], "%squery_%d", argv[1], i);
	else
	    sprintf(paths[i], "%s/query_%d", argv[1], i);
    }

/*
    char path[] = "./input/small_test.txt";
    ifstream inFile(path);
    if (!inFile.is_open()) {
        cerr << "Failed to open file."<<strerror(errno)<<":" << path << endl;
        return -1;
    }

    Vector<char> * vec = countQueries(inFile, &numOfQueries);
    Query ** qs = makeQueries(*vec, numOfQueries);
    */
    Query ** qs = makeQueries(paths, numOfQueries);
    for(int i=0;i<numOfQueries;i++)
        delete[] paths[i];
    delete[] paths;
    EntryList * eList = makeEntryList(qs, numOfQueries);

    Index * hammingIndex = makeIndex(MT_HAMMING_DIST, eList);
    Index * editIndex = makeIndex(MT_EDIT_DIST, eList);
    Index * hashIndex = makeIndex(MT_EXACT_MATCH, eList);

    int threshold = 2;
    int numOfWords = 5;
    Word ** wordsToSearch = new Word*[numOfWords];
    srand((unsigned)time(NULL) * getpid());
    wordsToSearch[0] = new Word("hel");
    for (int i = 1; i < numOfWords; ++i) {
	       char * str = genRandStr(1+rand()%10);
	       wordsToSearch[i] = new Word(str);
	       delete[] str;
    }

    multipleSearch(hashIndex, wordsToSearch, numOfWords, threshold);
    multipleSearch(editIndex, wordsToSearch, numOfWords, threshold);
    multipleSearch(hammingIndex, wordsToSearch, numOfWords, threshold);

    destroyQueries(qs, numOfQueries);
    delete hammingIndex;
    delete editIndex;
    delete hashIndex;
    for (int i = 0; i < numOfWords; ++i)
	delete wordsToSearch[i];
    delete[] wordsToSearch;
    delete eList;

    return 0;
}
