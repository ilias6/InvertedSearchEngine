#ifndef __BK_TREE_HPP__
#define __BK_TREE_HPP__

#include "list.hpp" 
#include "word.hpp"

using namespace std;

typedef Word Data;

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
    public:
	BKTree();
	~BKTree();
	void destroy(BKNode *);
	void insert(Data *);
	void print();
};

#endif
