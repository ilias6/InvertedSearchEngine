#include "../include/job.hpp"
#include "../include/result.hpp"
#include <iostream>


using namespace std;
void Args::print(){}
Args::Args(){}
Args::~Args(){}
Document * Args::getDocument(){return NULL;}
Result * Args::getRes(){return NULL;}
int Args::getType(){return -1;}
int Args::getDist(){return -1;}
int Args::getParentIndex(){return -1;}
Query * Args::getQuery(){return NULL;}


/* SearchArgs -------------------------------*/
SearchArgs::SearchArgs(Document * doc){
    this->doc = doc;
}

SearchArgs::~SearchArgs() {

}

Document * SearchArgs::getDocument() {
    return this->doc;
}

void SearchArgs::print(){
    cout<<"\t----SearchArgs-----\n";
    cout<<"\tdoc_id: "<<this->doc->getId()<<endl;
    // this->doc->print();
}


/* SearchMethodArgs --------------------------*/
SearchMethodArgs::SearchMethodArgs(Result * res, Document * doc, int i, int j, int idx) {
    this->res = res;
    this->doc = doc;
    this->typeIndex = i;
    this->distIndex = j;
    this->threadIndex = idx;
}
SearchMethodArgs::~SearchMethodArgs(){}

Result * SearchMethodArgs::getRes() {
    return this->res;
}

Document * SearchMethodArgs::getDocument() {
    return this->doc;
}

int SearchMethodArgs::getType() {
    return this->typeIndex;
}

int SearchMethodArgs::getDist() {
    return this->distIndex;
}

int SearchMethodArgs::getParentIndex() {
    return this->threadIndex;
}

/* DeactivateArgs--------------------*/

DeactivateArgs::DeactivateArgs(Query * q){
    this->qPtr=q;
}

DeactivateArgs::~DeactivateArgs(){

}

Query * DeactivateArgs::getQuery(){
    return qPtr;
}

/* Job ---------------------------------------*/
Job::Job(JobId id, Args * a) {
    this->status=PENDING;
    this->deactivated=NULL;
    this->id = id;
    args=a;
}

Job::~Job() {
    delete this->args;
    if(this->deactivated!=NULL)
        delete this->deactivated;
}

void Job::setStatus(enum Status s){
    this->status=s;
}

Status Job::getStatus() {
    return this->status;
}

void Job::print(){
    cout<<"\tTASK: ";
    switch(id){
        case SEARCH:
            cout<<"SEARCH "<<endl;
            args->print();
            break;
        case SEARCH_METHOD:
            cout<<"SEARCH_METHOD "<<endl;
            args->print();
            break;
        default:
            cout<<" - "<<endl;
            break;
    }
}

void Job::addDeactivated(Vector<Query *> * vec){
    this->deactivated=new Vector<Query *>(*vec);
    return ;
}

Vector<Query *> * Job::getDeactivated(){
    return deactivated;
}


JobId Job::getId() {
    return this->id;
}

Args * Job::getArgs() {
    return this->args;
}
