#include "../include/result.hpp"
#include "../include/gtest.h"
#include <stdexcept>
#include <iostream>

using namespace std;

class ResultTest: public ::testing::Test {
    protected:
        int size;
        DocID d_id;
        Vector<Query *>* queries;
        Result * res;
        virtual void SetUp(){
            this->size=4;
            d_id=999;
            this->queries=new Vector<Query *>;
            const char *str_arr[4]={"this isis thee first query","this isis thee tttt second","this isis thee third query","fourth andd final query"};
            for(int i=0;i<this->size;i++){
                Query * t=new Query(i,str_arr[i],MT_EXACT_MATCH,0);
                queries->insertSorted(t,t->getId());
            }
            res=new Result(d_id,*queries);
        }

        virtual void TearDown(){
            queries->destroyData();
            delete queries;
            delete res;
        }
};

TEST_F(ResultTest, increaseCounterAndFetchTest){
    DocID result_id;
    unsigned int size;
    QueryID * q_res_arr;

    ASSERT_TRUE(this->res->fetch(&result_id,&size,&q_res_arr)==R_SUCCESS);
    ASSERT_TRUE(q_res_arr==NULL);
    ASSERT_TRUE(size==0);
    ASSERT_TRUE(result_id==this->d_id);
    const char *str_arr[4][10]={{"this","isis","thee","first","query"},{"this","isis","thee","tttt","second"},{"this","isis","thee","third","query"},{"fourth","andd","final","query"}};
    Word *w=new Word("not-set");
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            w->set(str_arr[j][i]);
            this->res->increaseCounter(j,w);
        }

    ASSERT_TRUE(R_SUCCESS==this->res->fetch(&result_id,&size,&q_res_arr));
    ASSERT_TRUE(size==1);
    ASSERT_TRUE(result_id==this->d_id);
    ASSERT_TRUE(q_res_arr[0]==3);
    // this->res->print();
    free(q_res_arr);

    for(int j=0;j<3;j++){
        w->set(str_arr[j][4]);
        this->res->increaseCounter(j,w);
    }

    ASSERT_TRUE(R_SUCCESS==this->res->fetch(&result_id,&size,&q_res_arr));
    ASSERT_TRUE(size==4);
    ASSERT_TRUE(result_id==this->d_id);
    for(unsigned int i=0;i<4;i++)
       ASSERT_TRUE(q_res_arr[i]==i);
    w->set("ID NOT EXISTS");
    ASSERT_TRUE(this->res->increaseCounter(1111111,w)==R_FAIL);

    delete w;
    free(q_res_arr);
}

TEST_F(ResultTest,ConstructorTest){
    Result * r=new Result(1999,*this->queries);
    ASSERT_TRUE(r->getId()==1999);
    // CHECK IF RESULT IS INITIALIZE WTH QUERIES 0,1,2,3
    // WILL CHECK VIA increaseCounter
    Word * w=new Word("this");

    for(int i=0;i<3;i++)
        ASSERT_TRUE(R_SUCCESS==r->increaseCounter(i,w));
    w->set("query");
    ASSERT_TRUE(R_SUCCESS==r->increaseCounter(3,w));
    ASSERT_TRUE(R_FAIL==r->increaseCounter(4,w));
    delete w;
    delete r;
}
