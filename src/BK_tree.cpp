#include <iostream>
#include <cstdlib>
#include "../include/BK_tree.hpp"
#include "../include/utils.hpp"
#include "../include/word.hpp"

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))
using namespace std;

BKTree::BKTree(int(Word::*distanceFunc) (Word &)) {
    this->root = NULL;
    this->size=0;
    this->distanceFunc = distanceFunc;
    this->mutex=PTHREAD_MUTEX_INITIALIZER;
}

BKTree::~BKTree() {
    destroy(this->root);
}

BKErrorCode BKTree::destroy(BKNode * node) {
    if (node == NULL)
        return BK_SUCCESS;

    Vector<BKNode *> & children = node->getChildren();
    int childrenNum = children.getLen();
    for (int i = 0; i < childrenNum; ++i) {
        BKNode * n = children.getItem(i);
        if (destroy(n) == BK_FAIL)
            return BK_FAIL;
    }

    delete node;
    return BK_SUCCESS;
}

BKErrorCode BKTree::insert(Data * data) {
    //this is useful for hamming dist
    //ex. if the tree contains words with len 3 and a word of
    //    bigger len is to be inserted then DONT INSERT
    if(this->root!=NULL){
        Word * word1 = &data->getWord();
        Word * word2 = &root->getData()->getWord();
        //int distWithThisNode = invoke(distanceFunc, *word1, *word2);
        int distWithThisNode = CALL_MEMBER_FN(*word1, distanceFunc)(*word2);
        if(distWithThisNode<0)
            return BK_FAIL;
    }
    return insert(&this->root, data, 0);
}

void BKTree::print() {
    print(this->root, 0);
}

void printTabs(int tabsNum) {
    for (int i = 0; i < tabsNum; ++i)
        cout << "\t";
}
int BKTree::getSize(void){
    return this->size;
}


void BKTree::print(BKNode * node, int tabsNum) {
    if (node == NULL)
        return;

    Vector<BKNode *> & children = node->getChildren();
    int childrenNum = children.getLen();
    printTabs(tabsNum);
    cout << "Children: " << endl;
    for (int i = 0; i < childrenNum; ++i) {
        BKNode * n = children.getItem(i);
        printTabs(tabsNum);
        cout << "Distance: " << n->getDist() << endl;
        print(n, tabsNum+1);
    }
    printTabs(tabsNum);
    cout << "End of children." << endl;
    printTabs(tabsNum);
    node->print();
    printTabs(tabsNum);
    cout << "Next branch: " << endl;
}

BKErrorCode BKTree::insert(BKNode ** node, Data * data, int distWithParent) {
    mutexDown(&this->mutex);
    if (*node == NULL) {
        try {
            *node = new BKNode(data, distWithParent);
        }
        catch (bad_alloc & exc) {
            return BK_FAIL;
        }
        this->size++;
        mutexUp(&this->mutex);
        return BK_SUCCESS;
    }
    mutexUp(&this->mutex);
    mutexDown(&(*node)->mutex);

    Word * word1 = &data->getWord();
    Word * word2 = &(*node)->getData()->getWord();
    //int distWithThisNode = invoke(distanceFunc, *word1, *word2);
    int distWithThisNode = CALL_MEMBER_FN(*word1, distanceFunc)(*word2);

    Vector<BKNode *> & children = (*node)->getChildren();
    int childrenNum = children.getLen();
    for (int i = 0; i < childrenNum; ++i) {
        BKNode * n = children.getItem(i);
        int childDist = n->getDist();
        if (distWithThisNode == childDist) {
            mutexUp(&(*node)->mutex);
            return insert(&n, data, distWithThisNode);
        }
    }

    BKNode * newBranchNode = NULL;
    insert(&newBranchNode, data, distWithThisNode);
    children.insert(newBranchNode);
    mutexUp(&(*node)->mutex);
    return BK_SUCCESS;
}

List<Data *> BKTree::search(BKNode * node, Key * word1, int n) {
    List<Data *> results;

    if (node == NULL) {
        return results;
    }

    Data * data2 = node->getData();
    Word * word2 = &data2->getWord();
    //int d = invoke(distanceFunc, *word1, *word2);
    int d = CALL_MEMBER_FN(*word1, distanceFunc)(*word2);
    //int d = word1->distanceFunc(*word2);
    if (d <= n)
        results.insert(data2);

    int lowerBound = d-n;
    int upperBound = d+n;

    Vector<BKNode *> & children = node->getChildren();
    int childrenNum = children.getLen();
    for (int i = 0; i < childrenNum; ++i) {
        BKNode * childNode = children.getItem(i);
        int childDist = childNode->getDist();
        if ((childDist <= upperBound) && (childDist >= lowerBound)) {
            List<Data *> lst(search(childNode, word1, n));
            results.append(&lst);
        }
    }

    return results;

}

List<Data *> BKTree::search(Key * key, int n) {
    if(n<0 || key == NULL || key->getLen() == 0) {
        List<Data *> empty_list;
        return empty_list;
    }

    List<Data *> res = search(this->root, key, n);
    return res;
}

BKNode::BKNode(Data * data, int distance):children() {
    this->data = data;
    this->dist = distance;
    this->mutex=PTHREAD_MUTEX_INITIALIZER;
}

BKNode::~BKNode() {
    if (pthread_mutex_destroy(&this->mutex))
        perror("mutex destroy (~)");
};

Data * BKNode::getData() {
    return this->data;
}

int BKNode::getDist() {
    return this->dist;
}

Vector<BKNode *> & BKNode::getChildren() {
    return this->children;
}

void BKNode::print() {
    cout << (*this->data) << endl;
}
