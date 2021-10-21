#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"


using namespace std;

int main(int argc, char * argv[]) {
    List<int> myList = List<int>();

	Word w1 = Word("0123456789");
	Word w2 = Word("1234567890");

	cout << w1.editDist(w2) << endl;
	cout << w1.hammingDist(w2) << endl;

    return 0;

}
