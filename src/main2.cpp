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
using namespace std;

int main(int argc, char * argv[]) {

    PRINT_CORE_SETTINGS();
    List<Entry> myList = List<Entry>();
    HashTable t(3, djb2);
    BKTree tree;
    for (int i = 0; i < 1000; i++) {
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
	    tree.insert(&ePtr->getWord());
	}
	else {
	    cout << "WHATTT??\n";
	}
    }
    cout << "END OF LOOP\n";

    myList.print();
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
    myList.print();
    Document doc1(0,"input/doc1");
    doc1.print();
    Query q1(0,"input/doc1");
    /*
    BKTree tree;
    Word w("hell");
    tree.insert(&w);
    Word w2("help");
    tree.insert(&w2);
    Word w3("fall");
    tree.insert(&w3);
    Word w4("fell");
    tree.insert(&w4);
    Word w5("felt");
    tree.insert(&w5);
    Word w6("small");
    tree.insert(&w6);
    Word w7("melt");
    tree.insert(&w7);

    */
    tree.print();

    return 0;

}
