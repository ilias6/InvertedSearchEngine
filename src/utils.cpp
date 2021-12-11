#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "../include/utils.hpp"
#include "../include/entry_list.hpp"
#include <sys/time.h>

using namespace std;


bool isPrime(int n) {
    if (n % 2 == 0)
        return false;

    for (int i = 3; i < n/2; i += 2)
        if (n % i == 0)
            return false;

    return true;

}

int findNextPrime(int n) {
    int canditatePrime = n;
    while (!isPrime(canditatePrime))
        canditatePrime++;
    return canditatePrime;

}

bool satisfy(bool * arr, int size) {
    for (int i = 0; i < size; ++i)
        if (!arr[i])
            return false;
    return true;
}

bool charInWhitespace(char c){
    if(c=='\n'||c=='\t'||c==' '||c=='\f'||c=='\r')
        return true;
    return false;
}

int countSpaces(const char * str) {
    int len = strlen(str);
    int counter = 0;
    for (int i = 0; i < len; ++i)
        if (str[i] == ' ')
            counter++;
    return counter;
}

int scan(int n,const char* str,Word ***w_arr,int * different_words,int max_word_length,int min_word_length){
    //returns 0 in case of success
    //this function reads n strings from str and returns w_arr filled
    // -2 indicates corruption
    // -1 indicates word bigger than max_word_length
    // -3 indicates word smaller than min_word_length
    // cout<<"---->"<<max_word_length<<" "<<min_word_length<<endl;
    char *buff =new char[10*max_word_length];
    int str_len=strlen(str);
    int bytes_read=0;
    int index=0;
    *w_arr=new Word *[n];
    Word **r_arr=*w_arr;
    HashTable hashtable(findNextPrime(n),djb2);
    for(int i=0;i<n;i++)
        if(bytes_read<str_len){
            sscanf(str+bytes_read,"%s",buff);

            //cout<<buff<<endl;
            int len=strlen(buff);
            if(len>max_word_length){
                for(int j=0;j<index;j++)
                    delete r_arr[j];
                delete[] *w_arr;
                delete[] buff;
                *different_words=0;
                hashtable.deleteData();

                *w_arr=NULL;
                return -1;
            }
            else if(len<min_word_length){
                for(int j=0;j<index;j++)
                    delete r_arr[j];
                delete[] *w_arr;
                delete[] buff;
                *different_words=0;
                hashtable.deleteData();

                *w_arr=NULL;
                return -3;
            }
            bytes_read+=len+1;
            r_arr[index]=new Word(buff);

            if(hashtable.getEntry(r_arr[index])==NULL){
                PayloadEntry p(0,NULL);
                Entry * e=new Entry(*r_arr[index],p, MT_EXACT_MATCH,0);
                hashtable.insert(e);
                index++;
            }else{
                delete r_arr[index];
            }
        }else{
            for(int j=0;j<index;j++)
                delete r_arr[j];
            delete[] *w_arr;
            delete[] buff;
            hashtable.deleteData();
            *different_words=0;

            *w_arr=NULL;
            return -2;
        }
    delete[] buff;
    *different_words=index;
    // resize array to appropriate len
    //if duplicates exist
    if(index<n){
        Word **tmp=*w_arr;
        *w_arr=new Word*[*different_words];
        for(int i=0;i<*different_words;i++){
            *(*w_arr+i)=tmp[i];
        }
        delete[] tmp;
    }
    hashtable.deleteData();
    return 0;
}

// returns query pointer
Query * biSearchQuery(Vector<Query *> * queries, QueryID id) {
    int start = 0;
    int end = queries->getLen();
    Query * qPtr = NULL;

    if (queries->getItem(0)->getId() > id || queries->getItem(end-1)->getId() < id)
        return qPtr;

    int middle = 0;
    while (start <= end) {
        middle = (end-start)/2 + start;
        QueryID tId = queries->getItem(middle)->getId();
        if (id < tId) {
            end = middle-1;
        }
        else if (id > tId) {
            start = middle+1;
        }
        else {
            qPtr = queries->getItem(middle);
            break;
        }
    }
    return qPtr;
}
// returns index else -1 if not found
int biSearchQueryIndex(Vector<Query *> * queries, QueryID id) {
    int start = 0;
    int indx=-1;
    int end = queries->getLen();
    Query * qPtr = NULL;

    if (queries->getItem(0)->getId() > id || queries->getItem(end-1)->getId() < id)
        return indx;

    int middle = 0;
    while (start <= end) {
        middle = (end-start)/2 + start;
        QueryID tId = queries->getItem(middle)->getId();
        if (id < tId) {
            end = middle-1;
        }
        else if (id > tId) {
            start = middle+1;
        }
        else {
            // qPtr = queries->getItem(middle);
            indx=middle;
            break;
        }
    }
    return indx;
}

char * genRandStr(const int len) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    char * str = new char[len+1];

    /* this one is because the query files for input have words staring with a mostly */
    /* without it search will give empty results */
    str[0] = 'a';
    for (int i = 1; i < len; ++i)
        str[i] = alpha[rand() % (sizeof(alpha) - 1)];
    str[len] = '\0';

    return str;
}
