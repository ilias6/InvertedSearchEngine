#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <stdexcept>
#include <iostream>

enum ListErrorCode { L_SUCCESS, L_FAIL, L_EMPTY, L_NOT_EXISTS};

using namespace std;

template <typename T>
class ListNode {
    private:
        T data;
        ListNode<T> * next;
    public:
        ListNode<T>(T &);
        ~ListNode<T>();
        void print() const;
        void printAddr() const;
        ListNode<T> * getNext() const;
        T & getData();
        T getDataCopy();
        void setNext(ListNode<T> *);
        void setData(T&);
};

template <typename T>
class List {
    private:
        int len;
        ListNode<T> * head;
        ListNode<T> * tail;
    public:
        List();
        List(const List &);
        ~List();
        ListErrorCode destroyData();
        void print() const;
        void printAddr() const;
        int getLen() const;
        ListErrorCode copyList(List &);
        ListErrorCode insert(T&, T ** t = NULL);
        ListErrorCode append(List<T> *);
        bool exists(T&) const;
        ListErrorCode remove(T&);
        ListErrorCode removeIdx(int);
        T & getItem(int) const;
        T * getItemPtr(int) const;
        T getItemCopy(int);

};

template <typename T>
List<T>::List() {
    this->head = NULL;
    this->tail = NULL;
    this->len = 0;
}

template <typename T>
List<T>::List(const List & lst) {
    this->len = lst.len;

    if (lst.head == NULL) {
        this->head = NULL;
        this->tail = NULL;
        return;
    }

    // create new root:
    this->head = new ListNode<T>(lst.head->getData());

    ListNode<T> * lst_currentNode = lst.head;
    ListNode<T> * this_currentNode = this->head;
    while (lst_currentNode->getNext() != NULL) {
        // create new successor:
        ListNode<T> * newNode = new ListNode<T>(lst_currentNode->getNext()->getData());
        this_currentNode->setNext(newNode);
        this_currentNode = this_currentNode->getNext();
        lst_currentNode = lst_currentNode->getNext();
    }
    this->tail = this_currentNode;
    //cout << "List Copied!\n";
}

template <typename T>
ListErrorCode List<T>::copyList(List & lst) {
    if(this->len!=0){
        ListNode<T> * lst_currentNode = this->head;
        while(lst_currentNode!=NULL){
            ListNode<T> * tmp=lst_currentNode->getNext();
            delete lst_currentNode;
            lst_currentNode=tmp;
        }
    }

    this->len = lst.len;

    if (lst.head == NULL) {
        this->head = NULL;
        this->tail = NULL;
        return L_SUCCESS;
    }

    // create new root:
    try {
        this->head = new ListNode<T>(lst.head->getData());
    }
    catch (bad_alloc & exc) {
        return L_FAIL;
    }

    ListNode<T> * lst_currentNode = lst.head;
    ListNode<T> * this_currentNode = this->head;
    while (lst_currentNode->getNext() != NULL) {
        // create new successor:
        ListNode<T> * newNode = NULL;
        try {
            newNode = new ListNode<T>(lst_currentNode->getNext()->getData());
        }
        catch (bad_alloc & exc) {
            return L_FAIL;
        }
        this_currentNode->setNext(newNode);
        this_currentNode = this_currentNode->getNext();
        lst_currentNode = lst_currentNode->getNext();
    }
    this->tail = this_currentNode;
    return L_SUCCESS;
    //cout << "List Copied!\n";
}

template <typename T>
List<T>::~List() {
    ListNode<T> * lst = this->head;
    while (lst != NULL) {
        //cout << "Deleting: ";
        //cout << lst->getData() << endl;
        ListNode<T> * t = lst;
        lst = lst->getNext();
        delete t;
    }
}

template <typename T>
ListErrorCode List<T>::destroyData() {
    for (int i = 0; i < this->len; ++i)
        delete this->getItem(i);
    return L_SUCCESS;
}

template <typename T>
void List<T>::print() const {
    ListNode<T> * lst = this->head;
    while (lst != NULL) {
        lst->print();
        lst = lst->getNext();
    }
}

template <typename T>
void List<T>::printAddr() const {
    ListNode<T> * lst = this->head;
    while (lst != NULL) {
        lst->printAddr();
        lst = lst->getNext();
    }
}

template <typename T>
int List<T>::getLen() const {
    return this->len;
}

template <typename T>
T & List<T>::getItem(int index) const {
    if (index >= this->len || index < 0)
        throw invalid_argument("Index out of range");

    ListNode<T> * lst = this->head;
    for (int i = 0; i < index; ++i)
        lst = lst->getNext();

    return lst->getData();

}

template <typename T>
T * List<T>::getItemPtr(int index) const {
    if (index >= this->len || index < 0)
        return NULL;

    ListNode<T> * lst = this->head;
    for (int i = 0; i < index; ++i)
        lst = lst->getNext();

    return &lst->getData();

}

template <typename T>
T List<T>::getItemCopy(int index) {
    if (index >= this->len || index < 0)
        throw invalid_argument("Index out of range");

    ListNode<T> * lst = this->head;
    for (int i = 0; i < index; ++i)
        lst = lst->getNext();

    return lst->getDataCopy();

}

template <typename T>
ListErrorCode List<T>::append(List<T> * lst) {
    /*The dump way*/
    int len = lst->getLen();
    for (int i = 0; i < len; ++i) {
        T & item = lst->getItem(i);
        if (this->insert(item) == L_FAIL)
            return L_FAIL;
    }
    return L_SUCCESS;
    /*
       if (lst.head == NULL)
       return;

       this->tail->setNext(lst.head);
       this->tail = lst.tail;
       */
}

template <typename T>
ListErrorCode List<T>::insert(T & item, T ** itemPtr) {
    ListNode<T> * node = NULL;
    try {
        node = new ListNode<T>(item);
    }
    catch (bad_alloc & exc) {
        return L_FAIL;
    }

    if(itemPtr != NULL)
        *itemPtr = &node->getData();

    if (this->head == NULL) {
        this->head = node;
        this->tail = node;
        this->len = 1;
        return L_SUCCESS;
    }

    this->tail->setNext(node);
    this->tail = node;
    this->len++;
    return L_SUCCESS;
}

template <typename T>
ListErrorCode List<T>::remove(T& item) {
    if (this->head == NULL) {
        return L_EMPTY;
    }

    if (this->head->getData() == item) {
        ListNode<T> * t = this->head;
        this->head = this->head->getNext();
        delete t;
        this->len--;
        if (this->len == 0)
            this->tail = NULL;
        return L_SUCCESS;
    }

    ListNode<T> * n1 = this->head;
    ListNode<T> * n2 = this->head->getNext();
    while (n2 != NULL) {
        if (n2->getData() == item) {
            n1->setNext(n2->getNext());
            if (n2 == this->tail)
                this->tail = n1;
            delete n2;
            this->len--;
            return L_SUCCESS;
        }
        n1 = n2;
        n2 = n2->getNext();
    }
    return L_NOT_EXISTS;

}

template <typename T>
ListErrorCode List<T>::removeIdx(int idx) {
    if (this->head == NULL) {
        return L_EMPTY;
    }

    if (idx == 0) {
        ListNode<T> * t = this->head;
        this->head = this->head->getNext();
        delete t;
        this->len--;
        if (this->len == 0)
            this->tail = NULL;
        return L_SUCCESS;
    }

    ListNode<T> * n1 = this->head;
    ListNode<T> * n2 = this->head->getNext();
    int counter = 1;
    while (n2 != NULL) {
        if (idx == counter) {
            n1->setNext(n2->getNext());
            if (n2 == this->tail)
                this->tail = n1;
            delete n2;
            this->len--;
            return L_SUCCESS;
        }
        counter++;
        n1 = n2;
        n2 = n2->getNext();
    }
    return L_NOT_EXISTS;

}

template <typename T>
bool List<T>::exists(T& item) const {
    ListNode<T> * lst = this->head;
    while (lst != NULL) {
        if (lst->getData() == item)
            return true;
        lst = lst->getNext();
    }
    return false;

}

template <typename T>
ListNode<T>::ListNode(T& data):data(data){
    // this->data=data;
    this->next = NULL;
}

template <typename T>
ListNode<T>::~ListNode() {}

template <typename T>
void ListNode<T>::setNext(ListNode<T> * newNode) {
    this->next = newNode;
}


template <typename T>
void ListNode<T>::setData(T& item){
    this->data.set(item);
}

template <typename T>
void ListNode<T>::print() const {
    std::cout << this->data << std::endl;
}

template <typename T>
void ListNode<T>::printAddr() const {
    std::cout << &this->data << std::endl;
}

template <typename T>
ListNode<T> * ListNode<T>::getNext() const {
    return this->next;
}

template <typename T>
T & ListNode<T>::getData() {
    return this->data;
}

template <typename T>
T ListNode<T>::getDataCopy() {
    return this->data;
}


#endif
