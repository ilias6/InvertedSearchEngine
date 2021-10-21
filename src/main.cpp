#include <iostream>
#include <cstdlib>
#include "../include/list.hpp"
#include "../include/entry.hpp"
#include "../include/word.hpp"


using namespace std;

int main(int argc, char * argv[]) {
    List<int> myList = List<int>();
    myList.insert(1);
    myList.insert(2);
    myList.insert(3);
    myList.insert(99);

    myList.insert(4);
    myList.insert(98);
    myList.insert(5);

    myList.print();
    myList.remove(3);

    myList.print();
    myList.remove(1);

    myList.print();
    myList.remove(5);

    myList.print();
    myList.remove(2);

	cout << "------" <<endl;
    myList.print();
    myList.remove(4);

    myList.print();
    myList.remove(99);

    myList.print();
    myList.insert(2);
    myList.insert(3);
    myList.insert(99);

    cout << myList.exists(55555);
    cout << myList.exists(5);
    cout << myList.exists(1);
    cout << myList.exists(2);
    cout << myList.exists(99) << endl;


    return 0;

}
