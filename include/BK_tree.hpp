#ifndef __BK_TREE_HPP__
#define __BK_TREE_HPP__

#include "list.hpp" 
#include "word.hpp"
#include "entry.hpp"

using namespace std;

typedef Entry Data;
typedef Word Key;

class BKNode {
    private:
	Data * data;
	int dist;
	BKNode * parent;
	List<BKNode *> children;
    public:
	BKNode(Data *, int);
	~BKNode();
	Data * getData();
	int getDist();
	List<BKNode *> & getChildren();
	void print();

};

class BKTree {
    private:
	BKNode * root;
	int height;		
	void insert(BKNode **, Data *, int);
	void print(BKNode *, int);
	List<Data *> search(BKNode *, Key *, int);
    public:
	BKTree();
	~BKTree();
	void destroy(BKNode *);
	List<Data *> search(Key *, int);
	void insert(Data *);
	void print();
};

#endif
