#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <stdexcept>
#include <cstring>
#include <iostream>

enum VectorErrorCode { V_SUCCESS, V_FAIL, V_EMPTY, V_NOT_EXISTS};

using namespace std;

typedef int CmpKey;

template <typename T>
class Vector {
    private:
        int len;//num of data
        int actual_arr_size;//2,4,8,16,32 etc..
        T*arr;
    public:
        Vector();
        Vector(int);
        Vector(const Vector &);
        ~Vector();
        VectorErrorCode destroyData();
        int getActualMemoryLen() const;
        void print() const;
        int getLen() const;
        VectorErrorCode copyVector(Vector &);
        VectorErrorCode insert(T&);
        VectorErrorCode insertSorted(T&, CmpKey key);
        // VectorErrorCode append(Vector<T> *);
        bool exists(T&) const;
        VectorErrorCode remove(T&);
        VectorErrorCode removeHead();
        T & getItem(int) const;
        T getItemCopy(int);

};

template <typename T>
Vector<T>::Vector() {
    this->len = 0;
    this->actual_arr_size=0;
    arr=NULL;
}

template <typename T>
Vector<T>::Vector(int size) {
    this->len = 0;
    this->actual_arr_size=size;
    arr=new T[size];
}

template <typename T>
Vector<T>::Vector(const Vector & vec) {
    if(vec.len==0)
        return ;
    this->len = vec.len;
    this->actual_arr_size = vec.actual_arr_size;
    arr=new T[vec.actual_arr_size];
    for(int i=0;i<vec.len ;i++)
        arr[i]=vec.arr[i];
}

template <typename T>
VectorErrorCode Vector<T>::copyVector(Vector & vec) {
    if(this->len!=0){
        // delete previous alloc
        delete[] arr;
        arr=NULL;
    }
    this->len=vec.len;
    this->actual_arr_size=vec.actual_arr_size;
    if(this->actual_arr_size!=0)
        arr=new T[this->actual_arr_size];
    for(int i=0;i<vec.len;i++)
        arr[i]=vec.arr[i];
    return V_SUCCESS;
}

template <typename T>
Vector<T>::~Vector() {
    if(this->actual_arr_size!=0)
        delete[] arr;
    len=0;
    actual_arr_size=0;
}

template <typename T>
VectorErrorCode Vector<T>::destroyData() {
    for (int i = 0; i < this->len; ++i) {
        delete this->arr[i];
        this->arr[i] = NULL;
    }
    return V_SUCCESS;
}

template <typename T>
void Vector<T>::print() const {
    cout<<"Data size: "<<this->len<<endl;
    cout<<"Actual array size: "<<this->actual_arr_size<<endl;
    cout<<"-----------DATA----------------"<<endl;
    for(int i=0;i<this->len;i++)
        cout<<i<<" : "<<arr[i]<<endl;
    cout<<"-------------------------------"<<endl;

}


template <typename T>
int Vector<T>::getLen() const {
    return this->len;
}
template <typename T>
int Vector<T>::getActualMemoryLen() const {
    return this->actual_arr_size;
}

template <typename T>
T & Vector<T>::getItem(int index) const {
    if (index >= (int)this->len || index < 0)
        throw invalid_argument("Index out of range");
    return arr[index];
}


template <typename T>
T Vector<T>::getItemCopy(int index) {
    if (index >= this->len || index < 0)
        throw invalid_argument("Index out of range");
    return arr[index];

}

template <typename T>
VectorErrorCode Vector<T>::insert(T & item) {
    if(this->len==0){
        this->actual_arr_size=2;
        this->arr=new T[2];
    }
    if(this->len<this->actual_arr_size){
        arr[this->len]=item;
        this->len++;
        return V_SUCCESS;
    }
    // double actual arr size
    this->actual_arr_size*=2;
    T* tmp=arr;
    this->arr=new T[this->actual_arr_size];
    memcpy(this->arr,tmp,this->len*sizeof(T));
    delete[] tmp;
    this->arr[this->len]=item;
    this->len++;
    return V_SUCCESS;
}

template <typename T>
VectorErrorCode Vector<T>::insertSorted(T & item, CmpKey key) {
    if(this->len==0){
        this->actual_arr_size=2;
        this->arr=new T[2];
    }

    // Double actual arr size
    if(this->len >= this->actual_arr_size){
        this->actual_arr_size*=2;
        T* tmp=arr;
        this->arr=new T[this->actual_arr_size];
        memcpy(this->arr,tmp,this->len*sizeof(T));
        delete[] tmp;
    }

    if (this->len == 0 || (int)this->arr[this->len-1]->getId() <= key) {
        this->arr[this->len] = item;
        this->len++;
        return V_SUCCESS;
    }

    // Find the position of the new item
    // O(logn)
    int index;
    int start = 0;
    int end = this->len-1;
    int cond = false;
    while (!cond) {
        int middle = start + (end - start)/2;
        int cmpKey = this->arr[middle]->getId();
        if (start >= end-1 || cmpKey == key) {
            index = middle;
            cond = true;
        }
        else if (cmpKey > key) {
            end = middle;
        }
        else {
            start = middle;
        }

    }
    // O(n)
    /*
       for (int i = 0; i < this->len; ++i)
       if (this->arr[i]->getId() >= key) {
       index = i;
       break;
       }
       */

    // Shift elements to make space for the new item
    for (int i = this->len; i > index; --i)
        this->arr[i] = this->arr[i-1];

    this->arr[index]=item;
    this->len++;
    return V_SUCCESS;
}

template <typename T>
VectorErrorCode Vector<T>::removeHead() {
    if(this->len==0)
        return V_EMPTY;
    for (int i = 1; i < this->len; ++i)
        arr[i-1] = arr[i];
    this->len--;
    return V_SUCCESS;
}

template <typename T>
VectorErrorCode Vector<T>::remove(T& item) {
    bool exists=false;
    int indx=-1;
    if(this->len==0)
        return V_EMPTY;
    for(int i=0;i<this->len;i++)
        if(arr[i]==item){
            indx=i;
            exists=true;
            break;
        }
    if(exists){
        this->len--;
        if(this->len==this->actual_arr_size/2&&this->len!=1){
            this->actual_arr_size=this->len;
            T * tmp=arr;
            this->arr=new T[this->actual_arr_size];
            for(int i=0;i<indx;i++)
                this->arr[i]=tmp[i];
            int start=indx+1;
            int end=this->actual_arr_size+1;
            for(int i=start;i<end;i++)
                this->arr[i-1]=tmp[i];
            delete[] tmp;
            return V_SUCCESS;
        }else if(this->len==0){
            this->actual_arr_size=0;
            delete[] this->arr;
            this->arr=NULL;
            return V_SUCCESS;

        }
        for(int i=indx;i<this->len;i++)
            this->arr[i]=this->arr[i+1];
        return V_SUCCESS;

    }
    return V_NOT_EXISTS;
}

template <typename T>
bool Vector<T>::exists(T& item) const {
    for(int i=0;i<this->len;i++)
        if(arr[i]==item)
            return true;
    return false;
}

#endif
