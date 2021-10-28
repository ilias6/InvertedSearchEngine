#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
using namespace std;

int main(int argc, char * argv[]) {
    //List<Word> myList = List<Word>();
    List<Entry> myList = List<Entry>();
    HashTable t(3, djb2);
    for (int i = 0; i < 10000; i++) {	
	char str[256] = {0};
	sprintf(str, "%d", i);
	Word w(str);
	for (int j = 0; j < 100; ++j) {
		char str2[256] = {0};
		sprintf(str2, "%d", (i+1)%(j+1));
		Word w2(str2);
		Entry e2(w2, j+100); 
		myList.remove(e2);
	}
	Entry e(w, i+100); 
	for (int j = 0; j < 1000; j++) {
		e.addToPayload(j*i+2*(j+1));
	}
	Entry * ePtr = NULL; 
	myList.insert(e, &ePtr);
//	cout << "Next" << endl;
    }
    cout << "END OF LOOP\n";
    //myList.print();
    return 0;

}
