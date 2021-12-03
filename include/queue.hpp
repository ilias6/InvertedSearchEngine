#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <stdexcept>
#include <cstring>
#include <iostream>

using namespace std;

enum  QueueErrorCode{Q_SUCCESS, Q_FAIL, Q_EMPTY, Q_NOT_EXISTS};

template <typename T>
class Queue {
    private:
	Vector<T> vector;
    public:
        Queue();
        Queue(const Queue &);
        ~Queue();
        QueueErrorCode push(T&);
	T & pop() const;
	Vector<T> & getVector() {
	    return this->vector;
	}

};

template <typename T>
Queue<T>::Queue():vector() {}

template <typename T>
Queue<T>::Queue(const Queue & q):vector(q.getVector()) {}

template <typename T>
Queue<T>::~Queue() {}

QueueErrorCode Queue::push(T & item) {
    if (V_SUCCESS != this->vector.insert(T))
	return Q_FAIL;
    return Q_SUCCESS;
}

T & Queue::pop() {
    return this->vector.getItem(0);
}
#endif
