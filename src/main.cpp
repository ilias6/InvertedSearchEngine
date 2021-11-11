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

using namespace std;

#define QUERY_FILES_NUM 10000

int main(int argc, char * argv[]) {

    char ** paths = new char*[QUERY_FILES_NUM];
    for (int i = 0; i < QUERY_FILES_NUM; ++i) {
	paths[i] = new char[32];
	sprintf(paths[i], "./input/queries/query_%d\0", i);
    }
     
    Query ** qs = makeQueries(paths, QUERY_FILES_NUM);

    for (int i = 0; i < QUERY_FILES_NUM; ++i)
	delete[] paths[i];
    delete[] paths;

    EntryList * eList = makeEntryList(qs, QUERY_FILES_NUM);

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
    
    destroyQueries(qs, QUERY_FILES_NUM);
    delete hammingIndex;
    delete editIndex;
    delete hashIndex;
    for (int i = 0; i < numOfWords; ++i)
	delete wordsToSearch[i];
    delete[] wordsToSearch;
    delete eList;

    return 0;
}
