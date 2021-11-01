#ifndef __LIST_HPP__
#define __LIST_HPP__


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
	T * getDataAddr();
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
	void print() const;
	void printAddr() const;
	int getLen() const;
    void copyList(List &);
	void insert(T&, T ** t = NULL);
	void append(List<T> *);
	bool exists(T&) const;
	void remove(T&);
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
void List<T>::copyList(List & lst) {
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

    ListNode<T> * lst = this->head;
    for (int i = 0; i < index; ++i)
	lst = lst->getNext();

    return lst->getData();

}

template <typename T>
T * List<T>::getItemPtr(int index) const {
    ListNode<T> * lst = this->head;
    for (int i = 0; i < index; ++i)
	lst = lst->getNext();

    return &lst->getData();

}

template <typename T>
T List<T>::getItemCopy(int index) {
    // if (index >= this->len) {
	// T t = {0};
	// return t;
    // }

    ListNode<T> * lst = this->head;
    for (int i = 0; i < index; ++i)
	lst = lst->getNext();

    return lst->getDataCopy();

}

template <typename T>
void List<T>::append(List<T> * lst) {
    /*The dump way*/
    int len = lst->getLen();
    for (int i = 0; i < len; ++i) {
	T & item = lst->getItem(i);
	this->insert(item);
    }
    /*
    if (lst.head == NULL)
	return;

    this->tail->setNext(lst.head);
    this->tail = lst.tail;
    */
}

template <typename T>
void List<T>::insert(T & item, T ** itemPtr) {
    ListNode<T> * node = new ListNode<T>(item);
    if(itemPtr != NULL)
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
void List<T>::remove(T& item) {
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
	    if (n2 == this->tail)
		this->tail = n1;
	    delete n2;
	    this->len--;
	    return;
	}
	n1 = n2;
	n2 = n2->getNext();
    }

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
T * ListNode<T>::getDataAddr() {
    this->data;
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
