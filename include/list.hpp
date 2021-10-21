#ifndef __LIST_HPP__
#define __LIST_HPP__


template <typename T>
class ListNode {
    private:
	T data;
	ListNode<T> * next;
    public:
	ListNode<T>(T);
	void print() const;
	ListNode<T> * getNext() const;
	T & getData();
	void setNext(ListNode<T> *);
	void setData(T);
};

template <typename T>
class List {
    private:
	int len;
	ListNode<T> * head;
	ListNode<T> * tail;
    public:
	List();
	~List();
	void print() const;
	void insert(T, T ** t = NULL);
	bool exists(T) const;
	void remove(T);
	T & getItem(int);

};

template <typename T>
List<T>::List() {
    this->head = NULL;
    this->tail = NULL;
    this->len = 0;
}

template <typename T>
List<T>::~List() {
    ListNode<T> * lst = this->head;
    while (lst != NULL) {
	ListNode<T> * t = lst->getNext();
	delete lst;
	lst = t;
    }
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
T & List<T>::getItem(int index) {
    if (index >= this->len) {
	T t = {0};
	return t;
    }

    ListNode<T> * lst = this->head;
    for (int i = 0; i <= index; ++i)
	lst = lst->next;

    return lst->getData();

}


template <typename T>
void List<T>::insert(T item, T ** itemPtr) {
    ListNode<T> * node = new ListNode<T>(item);
    *itemPtr = &node->getData();

    if (this->head == NULL) {
	this->head = node;
	this->tail = node;
	this->len = 1;
	return;
    }

    this->tail->setNext(node);
    this->tail = node;
    this->len++;
}

template <typename T>
void List<T>::remove(T item) {
    if (this->head == NULL) {
	return;
    }

    if (this->head->getData() == item) {
	ListNode<T> * t = this->head;
	this->head = this->head->getNext();
	delete t;
	this->len--;
	if (this->len == 0)
	    this->tail = NULL;
	return;
    }

    ListNode<T> * n1 = this->head;
    ListNode<T> * n2 = this->head->getNext();
    while (n2 != NULL) {
	if (n2->getData() == item) {
	    n1->setNext(n2->getNext());
	    delete n2;
	    this->len--;
	    return;
	}
	n1 = n2;
	n2 = n2->getNext();
    }

}

template <typename T>
bool List<T>::exists(T item) const {
    ListNode<T> * lst = this->head;
    while (lst != NULL) {
	if (lst->getData() == item)
	    return true;
	lst = lst->getNext();
    }
    return false;

}

template <typename T>
ListNode<T>::ListNode(T data) {
    this->data = data;
    this->next = NULL;
}

template <typename T>
void ListNode<T>::setNext(ListNode<T> * newNode) {
    this->next = newNode;
}

template <typename T>
void ListNode<T>::setData(T item) {
    this->data = item;
}

template <typename T>
void ListNode<T>::print() const {
    std::cout << this->data << std::endl;
}

template <typename T>
ListNode<T> * ListNode<T>::getNext() const {
    return this->next;
}

template <typename T>
T & ListNode<T>::getData() {
    return this->data;
}


#endif
