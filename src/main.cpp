#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"


using namespace std;

int main(int argc, char * argv[]) {
    List<int> myList = List<int>();

	Word w1 = Word("0123456789000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000122222222222222223333333333333333sdkjfsbhdjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss332872899hfndfjdsfbskdjfbdfksbhdfkshbdfkshdbfskhdbflsdfbskdhfdskbhfkjsdbhfkbhds000");
	Word w2 = Word("12345678901111111111111111111111111111111122222222222222222222222222222222222222223333333333333333333333333333333333333333333333333333333333333333333333333skjdfsjfbdfsgdkhfbskdfjshbdkfjsdhbfgdskfjshgdkfgsbdkfsgbfjsdfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff3");

	for (int i = 0;	i < 1000; ++i)
		w1.editDist(w2);

//	cout << w1.hammingDist(w2) << endl;

    return 0;

}
