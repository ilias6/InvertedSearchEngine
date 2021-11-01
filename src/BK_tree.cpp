#include <iostream>
#include <cstdlib>
#include "../include/BK_tree.hpp"
#include "../include/word.hpp"


BKTree::BKTree(int(Word::*distanceFunc) (Word &)) {
    this->root = NULL;
    this->height = 0;
    this->distanceFunc = distanceFunc;
}

BKTree::~BKTree() {
    destroy(this->root);
}

void BKTree::destroy(BKNode * node) {
    if (node == NULL)
        return;

    List<BKNode *> & children = node->getChildren();
    int childrenNum = children.getLen();
    for (int i = 0; i < childrenNum; ++i) {
        BKNode * n = children.getItem(i);
        destroy(n);
    }

    delete node;
}

void BKTree::insert(Data * data) {
    insert(&this->root, data, 0);
}

void BKTree::print() {
    print(this->root, 0);
}

void printTabs(int tabsNum) {
    for (int i = 0; i < tabsNum; ++i)
        cout << "\t";
}

void BKTree::print(BKNode * node, int tabsNum) {
    if (node == NULL)
        return;

    List<BKNode *> & children = node->getChildren();
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

void BKTree::insert(BKNode ** node, Data * data, int distWithParent) {
    if (*node == NULL) {
        *node = new BKNode(data, distWithParent);
        return;
    }

    Word * word1 = &data->getWord();
    Word * word2 = &(*node)->getData()->getWord();
    int distWithThisNode = word1->distanceFunc(*word2);

    List<BKNode *> & children = (*node)->getChildren();
    int childrenNum = children.getLen();
    for (int i = 0; i < childrenNum; ++i) {
        BKNode * n = children.getItem(i);
        int childDist = n->getDist();
        if (distWithThisNode == childDist) {
            insert(&n, data, distWithThisNode);
            return;
        }
    }

    BKNode * newBranchNode = NULL;
    insert(&newBranchNode, data, distWithThisNode);
    children.insert(newBranchNode);
}

List<Data *> BKTree::search(BKNode * node, Key * word1, int n) {
    List<Data *> results;

    if (node == NULL) {
        return results;
    }

    Data * data2 = node->getData();
    Word * word2 = &data2->getWord();
    int d = word1->distanceFunc(*word2);
    if (d <= n)
        results.insert(data2);

    int lowerBound = d-n;
    int upperBound = d+n;

    List<BKNode *> & children = node->getChildren();
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
    return search(this->root, key, n);
}

BKNode::BKNode(Data * data, int distance):children() {
    this->data = data;
    this->dist = distance;
}

BKNode::~BKNode() {};

Data * BKNode::getData() {
    return this->data;
}

int BKNode::getDist() {
    return this->dist;
}

List<BKNode *> & BKNode::getChildren() {
    return this->children;
}

void BKNode::print() {
    cout << (*this->data) << endl;
}
