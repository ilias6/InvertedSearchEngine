#include "../include/gtest.h"
#include "../include/core_wrapper.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class CoreWrapperTest: public ::testing::Test {
    protected:
        CoreWrapper * core;
        const char * queries[12][2]={{"first","query"},
        {"second","query"},{"third","query"},{"fourth","query"},{"fifth","query"},
        {"sixth","query"},{"seventh","query"},{"eighth","query"},{"ninth","query"},
        {"tenth","query"},{"eleventh","query"},{"twelfth","query"}};
        const MatchType queries_type[12]={
            MT_EXACT_MATCH,MT_EXACT_MATCH,MT_EXACT_MATCH,MT_EXACT_MATCH,
            MT_EDIT_DIST,MT_EDIT_DIST,MT_EDIT_DIST,MT_EDIT_DIST,
            MT_HAMMING_DIST,MT_HAMMING_DIST,MT_HAMMING_DIST,MT_HAMMING_DIST};
        const int dist[12]={
            0,0,0,0,
            1,2,3,1,
            1,2,3,1
        };
        virtual void SetUp() {
            core=new CoreWrapper();
            const char * q[12]={"first query",
            "second query","third query","fourth query","fifth query",
            "sixth query","seventh query","eighth query","ninth query",
            "tenth query","eleventh query","twelfth query"};
            for(int i=0;i<12;i++)
                ASSERT_TRUE(C_W_SUCCESS==core->addQuery((QueryID)i,q[i],queries_type[i],dist[i]));


        }

        virtual void TearDown() {
            delete core;
        }
};

TEST_F(CoreWrapperTest,ConstructorTest){
    CoreWrapper *c=new CoreWrapper();
    ASSERT_TRUE(NULL==c->pullDocument());
    ASSERT_TRUE(NULL==c->pullResult());

    delete c;
}

TEST_F(CoreWrapperTest,addQueryAndMatchTest){
// lets see if add where made by Constructor
    ASSERT_TRUE(C_W_FAIL==this->core->deactivateQuery((QueryID)12));
    ASSERT_TRUE(C_W_FAIL==this->core->deactivateQuery((QueryID)13));
    ASSERT_TRUE(C_W_FAIL==this->core->deactivateQuery((QueryID)99));
    ASSERT_TRUE(C_W_FAIL==this->core->deactivateQuery((QueryID)1000));
    // we will get results for a doc
    // aand then add a query
    // and then get result that should contain the new query
    const char *doc_str="first second third fourth fifth sixth seventh eighth ninth tenth eleventh twelfth query 13th query";
    DocID d_id=999;
    ASSERT_TRUE(C_W_SUCCESS==core->addDocument(d_id,doc_str));
    Document * doc=core->pullDocument();
    // check document
    ASSERT_TRUE(doc->getId()==d_id);
    ASSERT_TRUE(doc->getWordsInDoc()==14);
    // now match document and get results
    Result * res=core->matchDocument(doc);
    delete doc;
    DocID fetched_doc;
    unsigned int matched_count;
    QueryID * query_arr;
    ASSERT_TRUE(R_SUCCESS==res->fetch(&fetched_doc,&matched_count,&query_arr));
    ASSERT_TRUE(fetched_doc==d_id);
    ASSERT_TRUE(matched_count==12);
    for(unsigned int i=0;i<matched_count;i++)
        ASSERT_TRUE((QueryID)i==query_arr[i]);

    // now add a 13nth query and check again
    delete res;
    free(query_arr);
    const char * last_query="13th query";
    ASSERT_TRUE(C_W_SUCCESS==this->core->addQuery(12,last_query,MT_EXACT_MATCH,0));
    ASSERT_TRUE(C_W_SUCCESS==core->addDocument(d_id,doc_str));
    doc=core->pullDocument();
    res=core->matchDocument(doc);
    delete doc;
    ASSERT_TRUE(R_SUCCESS==res->fetch(&fetched_doc,&matched_count,&query_arr));
    ASSERT_TRUE(fetched_doc==d_id);
    ASSERT_TRUE(matched_count==13);
    for(unsigned int i=0;i<matched_count;i++)
        ASSERT_TRUE((QueryID)i==query_arr[i]);
    delete res;
    free(query_arr);

}
TEST_F(CoreWrapperTest,deactivateQueryAndMatchTest){
    // deactivate the first query
    ASSERT_TRUE(C_W_SUCCESS==this->core->deactivateQuery(0));

    // get all queries ass result for doc except id 0
    const char *doc_str="first second third fourth fifth sixth seventh eighth ninth tenth eleventh twelfth query 13th query";
    DocID d_id=999;
    ASSERT_TRUE(C_W_SUCCESS==core->addDocument(d_id,doc_str));
    Document * doc=core->pullDocument();
    // check document
    ASSERT_TRUE(doc->getId()==d_id);
    ASSERT_TRUE(doc->getWordsInDoc()==14);
    // now match document and get results
    Result * res=core->matchDocument(doc);
    delete doc;
    DocID fetched_doc;
    unsigned int matched_count;
    QueryID * query_arr;
    ASSERT_TRUE(R_SUCCESS==res->fetch(&fetched_doc,&matched_count,&query_arr));
    ASSERT_TRUE(fetched_doc==d_id);
    ASSERT_TRUE(matched_count==11);
    for(unsigned int i=0;i<matched_count;i++)
        ASSERT_TRUE(query_arr[i]==i+1);
    free(query_arr);
    delete res;
    // deactivate all queries and get empty result
    for(int i=0;i<12;i++)
        ASSERT_TRUE(C_W_SUCCESS==this->core->deactivateQuery(i));

    ASSERT_TRUE(C_W_SUCCESS==core->addDocument(d_id,doc_str));
    doc=core->pullDocument();
    res=core->matchDocument(doc);
    delete doc;
    ASSERT_TRUE(R_SUCCESS==res->fetch(&fetched_doc,&matched_count,&query_arr));
    ASSERT_TRUE(fetched_doc==d_id);
    ASSERT_TRUE(matched_count==0);
    ASSERT_TRUE(query_arr==NULL);
    delete res;
}

// pullResult and add result do the same thing

TEST_F(CoreWrapperTest,addDocumentTest){
    const char *doc_str="first second third fourth fifth sixth seventh eighth ninth tenth eleventh twelfth query 13th query";
    for(int i=0;i<100;i++)
        ASSERT_TRUE(C_W_SUCCESS==core->addDocument((DocID)i,doc_str));

    for(unsigned int i=0;i<100;i++){
        Document *d=core->pullDocument();
        ASSERT_TRUE(d->getId()==i);
        delete d;
    }
    Document *d=core->pullDocument();
    ASSERT_TRUE(d==NULL);
    d=core->pullDocument();
    ASSERT_TRUE(d==NULL);
}
TEST_F(CoreWrapperTest,pullDocumentTest){
    const char *doc_str="first second third fourth fifth sixth seventh eighth ninth tenth eleventh twelfth query 13th query";
    for(int i=0;i<100;i++)
        ASSERT_TRUE(C_W_SUCCESS==core->addDocument((DocID)i,doc_str));

    for(unsigned int i=0;i<100;i++){
        Document *d=core->pullDocument();
        ASSERT_TRUE(d->getId()==i);
        delete d;
    }
    Document *d=core->pullDocument();
    ASSERT_TRUE(d==NULL);
    d=core->pullDocument();
    ASSERT_TRUE(d==NULL);
}
