#include <iostream>
#include <cstring>
#include "../include/query.hpp"
#include "../include/core.hpp"
#include "../include/hash_table.hpp"
#include "../include/hash_functions.hpp"
#include <fstream>
#include <cstring>
#include <cerrno>
#include "../include/utils.hpp"

using namespace std;


Query::Query(int id, const char * path){
    this->id=id;
    this->wordsInQuery=0 ;
    this->queryPath=new char[strlen(path)+1];
    this->word=new Word*[MAX_QUERY_WORDS];
    if(this->word==NULL || this->queryPath==NULL){
        cerr << "Failed to allocate memmory to fetch query words!"<<endl;
        return;
    }
    strcpy(queryPath,path);
    // this is for finding duplicates in 0(1)
    HashTable hashtable(findNextPrime(MAX_QUERY_WORDS), djb2);
    // MAYBE CHECK IF FILE IS SMALLER THAN MAX_QUERY_LENGTH AND OPEN OR THROW ERROR MESSAGE
    ifstream input(queryPath);

    if (!input.is_open()) {
           cerr << "Failed to open file."<<strerror(errno)<<":" << path << endl;
           return;
    }

    int buffIndex;
    char * buffer = new char[MAX_WORD_LENGTH+1];
    while (!input.eof()) {
        buffIndex=0;
        input.get(buffer[buffIndex]);
        while(!charInWhitespace(buffer[buffIndex]) && !input.eof()){
            //we dont want new lines
            buffIndex++;
            input.get(buffer[buffIndex]);
            if(buffIndex==MAX_WORD_LENGTH){
                cout<<buffer<<endl;
                cerr << "Query contains words with len exceeding MAX_WORD_LENGTH (" << MAX_WORD_LENGTH <<")"<< endl;
                return;
            }

        }
        if(buffIndex==0)
            continue;
        // we dont want space char or any whitspace
        buffIndex--;
        if(buffIndex<MIN_WORD_LENGTH-1){
            cerr << "Query contains words with len smaller than MIN_WORD_LENGTH (" << MIN_WORD_LENGTH <<")"<< endl;
            return;
        }
        buffer[buffIndex+1]='\0';//terminate string
        Word * w=new Word(buffer);
        Entry * e=hashtable.getEntry(w);
        if(e!=NULL){
            // means word already exists
            // cout<<*w<<" already exists!"<<endl;
            delete w;
            continue;
        }
        //word doen't exist so add it to array and to hashtable
        this->word[this->wordsInQuery]=w;
        e=new Entry(*w,this->id);
        hashtable.insert(e);
        this->wordsInQuery++;
        if(this->wordsInQuery>MAX_QUERY_WORDS){
            cerr << "Document contains more words than MAX_DOC_WORDS (" << MAX_QUERY_WORDS <<")"<< endl;
            return;
        }
    }
    // now that we know the size of word array
    // make a smaller array containing the exact number of words
    Word **tmp=this->word;
    this->word=new Word*[wordsInQuery];
    if(this->word==NULL){
        cerr << "Failed to allocate memmory to fetch query words!"<<endl;
        return;
    }
    for(int i=0;i<wordsInQuery;i++)
    this->word[i]=tmp[i];
    delete[] tmp;
    delete[] buffer;
    hashtable.deleteData();
}

Query::~Query(){
    delete[] queryPath;
    for(int i=0;i<wordsInQuery;i++)
        delete this->word[i];
    delete[] this->word;
}

int Query::getId(){
    return this->id;
}

int Query::getWordsInQuery(){
    return this->wordsInQuery;
}

Word * Query::getWord(int indx){
    if(indx<this->wordsInQuery){
        return word[indx];
    }
    return NULL;
}

void Query::print(){
    cout<<"------------------------"<<endl;
    cout<<"QueryPath: "<<queryPath<<endl;
    cout<<"Id: "<<this->id<<endl;
    cout<<"WordsInQuery: "<<wordsInQuery<<endl;
    for(int i=0;i<wordsInQuery;i++)
        cout<<"\t"<<*word[i]<<" "<<word[i]->getLen()<<endl;

    return ;
}
