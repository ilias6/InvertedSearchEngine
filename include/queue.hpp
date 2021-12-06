#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "vector.hpp"
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
        QueueErrorCode destroyData();
        T pop();
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

template <typename T>
QueueErrorCode Queue<T>::push(T & item) {
    if (V_SUCCESS != this->vector.insert(item))
	return Q_FAIL;
    return Q_SUCCESS;
}

template <typename T>
T Queue<T>::pop(){
    try{
	T item = vector.getItem(0);
	vector.removeHead();
        return item;
    }catch(invalid_argument& ia){
	    throw invalid_argument("Index out of range");
    }
}

template <typename T>
QueueErrorCode Queue<T>::destroyData(){
    VectorErrorCode err=vector.destroyData();
    if(err!=V_SUCCESS)
        return Q_FAIL;
    return Q_SUCCESS;
}
#endif
