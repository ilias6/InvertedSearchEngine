#ifndef __ENTRY_HPP__
#define __ENTRY_HPP__

#include <iostream>
#include "./word.hpp"
#include "./list.hpp"
using namespace std;

class Entry {
    private:
	Word word;
	List<int> payload;
    public:
	List<int> & getPayload();
	void addToPayload(int);
	Word &getWord();
	Entry(const char *, int);
	Entry(Word &, int);
	Entry(Entry &);
	~Entry();
	friend ostream & operator<<(ostream &, const Entry &);
	bool operator==(Entry &);
};

#endif
