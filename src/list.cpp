#include <iostream>
#include "../include/list.hpp"

using namespace std;


template <typename T>
List<T>::List() {
    this->head = NULL;
    this->tail = NULL;
    this->len = 0;
}

template <typename T>
void List<T>::print() {
    this->head->print();
}

template <typename T>
void List<T>::insert(T item) {
    if (this->head == NULL) {
	ListNode<T> node = new ListNode<T>(item);
	this->head = node;
	this->tail = node;
	this->len = 1;
	return;
    }
    this->tail = this->tail->insert(item);
    this->len++;
}

template <typename T>
bool List<T>::exists(T & item) {
    return this->head->exists(item);
}

/*ListNode methods*/
template <typename T>
ListNode<T>::ListNode(T data) {
    this->data = data;
    this->next = NULL;
}

template <typename T>
ListNode<T>::~ListNode<T>() {
    while (this != NULL) {
	ListNode<T> t = this->next;
	delete this;
    }
}

template <typename T>
ListNode<T> & ListNode<T>::insert(ListNode<T> & newNode) {
    this->next = newNode;
}

template <typename T>
void ListNode<T>::print() {
    while (this != NULL) {
	this->data.print();
	ListNode<T> t = this->next;
    }
}

template <typename T>
bool ListNode<T>::exists(T & item) {
    while (this != NULL) {
	if (this->data == item)
	    return true;
	this = this->next;
    }
    return false;
}
