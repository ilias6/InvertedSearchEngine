#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
using namespace std;

int main(int argc, char * argv[]) {
    List<Word> myList = List<Word>();

	Word w1("skata1");
	Word w2("skata2");
    // HashTable t(2,djb2);
    myList.insert(w1);
    myList.print();
	// cout << w1.editDist(w2) << endl;
	// cout << w1.hammingDist(w2) << endl;
    // Entry * e=new Entry(w1,0);
    // // t.insert(e);
    // t.print();
    return 0;

}
