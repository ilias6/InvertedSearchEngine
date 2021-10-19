#ifndef __LIST_HPP__
#define __LIST_HPP__


template <typename T>
class ListNode {
	private:
		T data;
		ListNode<T> * next;
	public:
		ListNode<T>(T);
		~ListNode<T>();
		void print();
		ListNode<T> & insert(ListNode<T> &);
		bool exists(T &);
};

template <typename T>
class List {
	private:
		ListNode<T> * head;
		ListNode<T> * tail;
		int len;
	public:
		List();
		~List();
		void print();
		void insert(T);
		bool exists(T &);
		
};

#endif

