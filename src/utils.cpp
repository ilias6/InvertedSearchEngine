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

bool charInWhitespace(char c){
    if(c=='\n'||c=='\t'||c==' '||c=='\f'||c=='\r')
        return true;
    return false;
}

int scan(int n,const char* str,Word ***w_arr,int * different_words){
        //returns 0 in case of success
        //this function reads n strings from str and returns w_arr filled
        // -2 indicates corruption
        // -1 indicates word bigger than MAX_WORD_LENGTH
        // -3 indicates word smaller than MIN_WORD_LENGTH
        char *buff =new char[2*MAX_WORD_LENGTH];
        int bytes_read=0;
        int index=0;
        *w_arr=new Word *[n];
        Word **r_arr=*w_arr;
        HashTable hashtable(findNextPrime(n),djb2);
        for(int i=0;i<n;i++){
            if(sscanf(str+bytes_read,"%s",buff)==EOF)
                return -2;
            int len=strlen(buff);
            if(len>MAX_WORD_LENGTH)
                return -1;
            else if(len<MIN_WORD_LENGTH)
                return -3;
            bytes_read+=len+1;
            r_arr[index]=new Word(buff);
            if(hashtable.getEntry(r_arr[index])==NULL){
                PayloadEntry p(0,0,MT_EXACT_MATCH,0,NULL);
                Entry * e=new Entry(*r_arr[index],p);
                hashtable.insert(e);
                index++;
           }else{
               delete r_arr[index];
           }
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

Query * biSearchQuery(Vector<Query *> * queries, QueryID id) {
    int start = 0;
    int end = queries->getLen();
    Query * qPtr = NULL;
    while (start < end) {
	int middle = (end-start)/2;
    	QueryID tId = queries->getItem(middle)->getId();
	if (id < tId) {
	    end = middle;
	}
	else if (id > tId) {
	    start = middle;
	}
	else {
	    qPtr = queries->getItem(middle);
	    break;
	}
    }
    return qPtr;
}

/*
Vector<char> * countQueries(ifstream & inFile, int * counter) {
    cout << "Counting queries...\n";
    Vector<char> * vec = new Vector<char>();
    *counter = 0;
    char c;
    while (!inFile.eof()) {
        inFile.get(c);
        if (c == '\n') {
            vec->insert(c);
            inFile.get(c);
            if (c == 's')
                (*counter)++;
        }
        vec->insert(c);
    }
    cout << "Done---->Total queries: " << *counter << "\n";
    return vec;
}
*/

        /*
Query ** makeQueries(Vector<char> & vec, int numOfQueries) {
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^\nReading queries..." << endl;

    Query ** qs = new Query*[numOfQueries];
    int i = 0;

    int start = 0;
    int end = 0;
    while (i < numOfQueries) {
        if (vec.getItem(end) == '\n' && ((vec.getItem(end+1) == 'e')
                                          || (vec.getItem(end+1) == 'r'))
                                          || (vec.getItem(end+1) == 'm')) {

            cout << "Not a query skipped\n";
            while (vec.getItem(end) != '\n' && vec.getItem(end+1) != 's')
                end++;
            start = end++ +2;
            continue;
        }
        while (vec.getItem(end) != '\n' || vec.getItem(end+1) != 's')
            end++;
        cout << "start: " <<  start << " end: " << end << endl;
        qs[i] = new Query(i, vec, start);
        qs[i]->print();
        ++i;
        start = end++ +2;
    }

    cout << "Done!\n^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    return qs;
}
        */

/*
Query ** makeQueries(char ** paths, int pathsNum) {
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^\nReading queries..." << endl;
    Query ** qs = new Query*[pathsNum];
    for (int i = 0; i < pathsNum; ++i)
        qs[i] = new Query(i, paths[i]);
    cout << "Done!\n^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    return qs;
}
*/

void destroyQueries(Query ** qs, int qNum) {
    for (int i = 0; i < qNum; ++i)
        delete qs[i];
    delete[] qs;
}

/*
EntryList * makeEntryList(Query ** qs, int qNum) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int cur = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    // time_t cur;
    // cur = time(NULL);
    cout << "###########################\nBuilding entry list in: ";
    // This is the correct one
    EntryList * eList = new EntryList(qNum*MAX_QUERY_WORDS);
    // EntryList * eList = new EntryList(10000);
    for (int i = 0; i < qNum; ++i)
        eList->insert(*qs[i]);
    gettimeofday(&tp, NULL);
    long int elapsed= tp.tv_sec * 1000 + tp.tv_usec / 1000 -cur;
    // float elapsed = time(NULL) - cur;
    // elapsed /= 60;
    cout << (long int)elapsed << " milliseconds\n###########################\n\n";
    return eList;
}

Index * makeIndex(MatchType type, EntryList * eList) {
    time_t cur;
    cur = time(NULL);
    if (type == MT_HAMMING_DIST)
        cout << "---------------------------\nBuilding hamming-distance index in: ";
    else if (type == MT_EDIT_DIST)
        cout << "---------------------------\nBuilding edit-distance index in: ";
    else
        cout << "---------------------------\nBuilding exact-match index in: ";
    Index * index = new Index(*eList, type);
    float elapsed = time(NULL) - cur;
    // elapsed /= 60;
    cout << (long int)elapsed << " seconds\n---------------------------\n\n";
    return index;
}

void search(Index * index, Word * word, int threshold) {
    List<Entry *> res = index->search(word, threshold);
    int len = res.getLen();
    for (int i = 0; i < len; ++i) {
        if (i > 0 && !(i % 10))
            cout << endl;
        cout << res.getItem(i)->getWord().getStr();
        if (i < len-1)
            cout << ", ";
    }
    cout << endl;
}

void multipleSearch(Index * index, Word ** words, int wordsNum, int threshold) {

    if (index->getType() == MT_HAMMING_DIST)
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nSearching in hamming-distance index:\n";
    else if (index->getType() == MT_EDIT_DIST)
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nSearching in edit-distance index:\n";
    else
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nSearching in exact-match index:\n";
    cout<<"THRESHOLD: "<<threshold<<endl;
    for (int i = 0; i < wordsNum; ++i) {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        long int cur = tp.tv_sec * 1000 + tp.tv_usec / 1000;
        // time_t cur;
        // cur = time(NULL);
        cout << "***************************\nSearching for : " << words[i]->getStr() << endl << "Results:\n";
        search(index, words[i], threshold);
        gettimeofday(&tp, NULL);
        long int elapsed= tp.tv_sec * 1000 + tp.tv_usec / 1000 -cur;
        // float elapsed = time(NULL) - cur;
        // elapsed /= 60;
        cout << "In :" << elapsed << " milliseconds\n***************************\n";
    }
    cout << endl;
}*/

/*
    this function finds the opened fd and count the start queries to know how many queries exist in file
*/
// #include <dirent.h>
// #include <stdio.h>
// #include <unistd.h>
// int getNumOfQueriesFromFd(){
//     char path[100];
//     sprintf(path,"/proc/%d/fd",getpid());
//     DIR *d;
//     int count=0;
//     struct dirent *dir;
//     d = opendir(path);
//     int new_fd;
//     if(d)
//         while ((dir = readdir(d)) != NULL)
//             if(strcmp("0",dir->d_name) && strcmp("1",dir->d_name) &&strcmp(".",dir->d_name) &&strcmp("..",dir->d_name)&&strcmp("2",dir->d_name)){
//                 new_fd=dup(atoi(dir->d_name));
//                 char c;
//                 int bytes_read;
//                 while((bytes_read=read(new_fd,&c,1))==1){
//                     // printf("ok: %d\n",bytes_read);
//                     if(c=='\n'){
//                         bytes_read=read(new_fd,&c,1);
//                         //check for s
//                         if(bytes_read==1){
//                             if(c=='s')
//                                 count++;
//                         }
//                     }
//                 }
//
//                 //move cursor at the beggining of file
//                 lseek(new_fd,0,SEEK_SET);
//                 break;
//
//             }
//
//     close(new_fd);
//     return count;
//
// }

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
