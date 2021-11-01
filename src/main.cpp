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

using namespace std;

int main(int argc, char * argv[]) {

    PRINT_CORE_SETTINGS();
    List<Entry> myList = List<Entry>();
    int n = 100000;
    cout << findNextPrime(n/4) << endl;
    HashTable t(findNextPrime(n/4), djb2);
    for (int i = 0; i < n; i++) {
	char str[256] = {0};
	sprintf(str, "%d", i);
	Word w(str);
	Entry e(w, -1000);
	for (int j = 0; j < 10; j++) {
	    e.addToPayload(j*2);
	}

	if (!t.getEntry(&e.getWord())) {
	    Entry * ePtr = &e;
	    myList.insert(e, &ePtr);
	    t.insert(ePtr);
	}
	else {
	    cout << "WHATTT??\n";
	}
    }
    cout << "END OF LOOP\n";

    for (int i = 0; i < 10; i++) {
	char str[256] = {0};
	sprintf(str, "%d", i);
	Word w(str);
	Entry e(w, i+100);
	if (!t.getEntry(&e.getWord())) {
	    cout << "WAHT\n";
	    Entry * ePtr = NULL;
	    myList.insert(e, &ePtr);
	    t.insert(ePtr);
	}
	else {
	    t.updateEntryPayload(&e.getWord(), -10*i);
	}


    }
    Document doc1(0,"input/doc1");
    doc1.print();
    Query q1(0,"input/doc1");
    cout << "Index building..\n";
    Index index(&myList, &Word::editDist);
    cout << "Index built\n";
    Word w("4265");
    cout << "Searching for 1 distance from 4265:\n";
    List<Entry *> res = index.search(&w, 1);

    for (int i = 0; i < res.getLen(); ++i)
	cout << res.getItem(i)->getWord() << endl;
    return 0;

}
