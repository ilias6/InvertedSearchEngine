#include "../include/job.hpp"
#include "../include/result.hpp"
#include <iostream>


using namespace std;
void Args::print(){}
Args::Args(){}
Args::~Args(){}
Document * Args::getDocument(){return NULL;}
QueryID Args::getQueryId(){return -1;}


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

/* Job ---------------------------------------*/
Job::Job(JobId id, Args * a) {
    this->status=PENDING;
    this->id = id;
    args=a;
}

Job::~Job() {
    delete this->args;
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
        case EXACTSEARCH:
            cout<<"EXACTSEARCH "<<endl;
            break;
        case EDITSEARCH:
            cout<<"EDITSEARCH "<<endl;
            break;
        case HAMMINGSEARCH:
            cout<<"HAMMINGSEARCH "<<endl;
            break;
        default:
            cout<<" - "<<endl;
            break;
    }
}

JobId Job::getId() {
    return this->id;
}

Args * Job::getArgs() {
    return this->args;
}

