#ifndef __BK_TREE_HPP__
#define __BK_TREE_HPP__

#include "list.hpp"
#include "word.hpp"
#include "entry.hpp"
#include "vector.hpp"
#include <pthread.h>
using namespace std;

enum BKErrorCode {BK_SUCCESS, BK_FAIL};

typedef Entry Data;
typedef Word Key;

class BKNode {
    private:
        Data * data;
        int dist;
        //BKNode * parent;
        Vector<BKNode *> children;
    public:
        pthread_mutex_t mutex;
        BKNode(Data *, int);
        ~BKNode();
        Data * getData();
        int getDist();
        Vector<BKNode *> & getChildren();
        void print();

};

class BKTree {
    private:
        int size;
        BKNode * root;
        // int height;
        int(Word::*distanceFunc) (Word &);
    
        BKErrorCode insert(BKNode **, Data *, int);
        void print(BKNode *, int);
        List<Data *> search(BKNode *, Key *, int);
    public:
        int getSize(void);
        BKTree(int(Word::*distanceFunc) (Word &));
        ~BKTree();
        BKErrorCode destroy(BKNode *);
        List<Data *> search(Key *, int);
        BKErrorCode insert(Data *);
        void print();
};

#endif
