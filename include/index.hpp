#ifndef __INDEX_HPP__
#define __INDEX_HPP__

#include "BK_tree.hpp"
#include "entry.hpp"
#include "hash_table.hpp"

using namespace std;

enum indexType{BKT, HT};

class Index {
    private:
	indexType type;	
	BKTree tree;
	HashTable hTable;
    public:
	Index(List<Entry> *, int (Word::*distFunc)(Word &));
	Index(List<Entry> *, int tableSize, unsigned long (*h_f)(const char *));
	void insertFromList(List<Entry> *);
	List<Entry *> search(Word *, int n = 0);
	~Index();
};



#endif
