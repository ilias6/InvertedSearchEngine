#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "list.hpp"

using namespace std;

enum QueueErrorCode{Q_SUCCESS, Q_FAIL, Q_EMPTY, Q_NOT_EXISTS};

template <typename T>
class Queue {
    private:
        List<T> lst;
    public:
        Queue();
        Queue(const Queue &);
        ~Queue();
        QueueErrorCode push(T&);
        QueueErrorCode destroyData();
        T pop();
        List<T> & getList() {
            return this->lst;
        }

};

template <typename T>
Queue<T>::Queue():lst() {}

template <typename T>
Queue<T>::Queue(const Queue & q):lst(q.getList()) {}

template <typename T>
Queue<T>::~Queue() {}

template <typename T>
QueueErrorCode Queue<T>::push(T & item) {
    if (L_SUCCESS != this->lst.insert(item))
        return Q_FAIL;
    return Q_SUCCESS;
}

template <typename T>
T Queue<T>::pop(){
    try{
        T item = lst.getItem(0);
        lst.removeIdx(0);
        return item;
    }catch(invalid_argument& ia){
        throw invalid_argument("Index out of range");
    }
}

template <typename T>
QueueErrorCode Queue<T>::destroyData(){
    ListErrorCode err=lst.destroyData();
    if(err!=L_SUCCESS)
        return Q_FAIL;
    return Q_SUCCESS;
}
#endif
