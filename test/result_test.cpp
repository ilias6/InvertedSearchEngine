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
            const char *str_arr[4]={"this is the first query","this is the t second","this is the third query","fourth and final query"};
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

TEST_F(ResultTest, fetchTest){
    DocID result_id;
    unsigned int size;
    QueryID * q_res_arr;
    ASSERT_TRUE(this->res->fetch(&result_id,&size,&q_res_arr)==R_EMPTY);
    ASSERT_TRUE(q_res_arr==NULL);
    ASSERT_TRUE(size==0);
    ASSERT_TRUE(result_id==this->d_id);

    //for(int i=0;i<16;i++)
    //    this->res->increaseCounter(i%4);
    //ASSERT_TRUE(R_SUCCESS==this->res->fetch(&result_id,&size,&q_res_arr));
    //ASSERT_TRUE(size==1);
    //ASSERT_TRUE(result_id==this->d_id);
    //ASSERT_TRUE(q_res_arr[0]==3);
    //// this->res->print();
    //delete[] q_res_arr;

    //for(int i=0;i<16;i++)
    //    this->res->increaseCounter(i%4);
    //// this->res->print();

    //ASSERT_TRUE(R_SUCCESS==this->res->fetch(&result_id,&size,&q_res_arr));
    //ASSERT_TRUE(size==4);
    //ASSERT_TRUE(result_id==this->d_id);
    //for(int i=0;i<4;i++)
    //    ASSERT_TRUE(q_res_arr[i]==i);

    //ASSERT_TRUE(this->res->increaseCounter(111111111)==R_FAIL);


    delete[] q_res_arr;

}
