#include <gtest/gtest.h>
#include "../include/list.hpp"
#include "../include/word.hpp"


// class myTestFixture1: public ::testing::Test {
// public:
//    myTestFixture1( ) {
//        // initialization code here
//    }
//
//    void SetUp( ) {
//        // code here will execute just before the test ensues
//    }
//
//    void TearDown( ) {
//        // code here will be called just after the test completes
//        // ok to through exceptions from here if need be
//    }

class ListTest: public ::testing::Test {
    protected:
        List<int> *integer_list;
        // List<Word> *integer_list;
        int **arr;
        List<int *> *ptr_list;
        // ListTest(){
        //
        // }

        virtual void SetUp(){
            // for constructor assertion
            // for int list
            integer_list=new List<int>;
            ptr_list=new List<int*>;
            arr=new int*[6];
            for(int i=0;i<6;i++)
                arr[i]=new int(50+i);
            for(int i=0;i<6;i++){
                integer_list->insert(*arr[i]);
                ptr_list->insert(arr[i]);
            }
        }

        virtual void TearDown(){
            delete integer_list;
            for(int i=0;i<6;i++)
                delete arr[i];
            delete[] arr;
            delete ptr_list;
        }
};

TEST_F(ListTest,InsertTest){
    ASSERT_TRUE(6==integer_list->getLen());
    ASSERT_TRUE(6==ptr_list->getLen());
    ASSERT_TRUE(50==integer_list->getItem(0));
    ASSERT_TRUE(51==integer_list->getItem(1));
    ASSERT_TRUE(52==integer_list->getItem(2));
    ASSERT_TRUE(53==integer_list->getItem(3));
    ASSERT_TRUE(54==integer_list->getItem(4));
    ASSERT_TRUE(55==integer_list->getItem(5));
    int *val;
    int new_insert_val=800;
    integer_list->insert(new_insert_val,&val);
    ASSERT_TRUE(7==integer_list->getLen());
    ASSERT_TRUE(800==integer_list->getItem(6));
    ASSERT_TRUE(800==*val);
    *val=799;
    ASSERT_TRUE(799==integer_list->getItem(6));
    for(int i=0;i<6;i++)
        ASSERT_TRUE(arr[i]==ptr_list->getItem(i));

}

TEST_F(ListTest,RemoveTest){
    int to_be_rm=100000;
    ASSERT_TRUE(6==integer_list->getLen());
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(6==integer_list->getLen());
    to_be_rm=50;
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(5==integer_list->getLen());
    ASSERT_TRUE(51==integer_list->getItem(0));
    ASSERT_TRUE(52==integer_list->getItem(1));
    to_be_rm=52;
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(4==integer_list->getLen());
    ASSERT_TRUE(53==integer_list->getItem(1));
    to_be_rm=55;
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(3==integer_list->getLen());
    ASSERT_TRUE(54==integer_list->getItem(2));
    to_be_rm=51;
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(2==integer_list->getLen());
    ASSERT_TRUE(53==integer_list->getItem(0));
    ASSERT_TRUE(54==integer_list->getItem(1));
    to_be_rm=53;
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(1==integer_list->getLen());
    ASSERT_TRUE(54==integer_list->getItem(0));
    to_be_rm=54;
    integer_list->remove(to_be_rm);
    ASSERT_TRUE(0==integer_list->getLen());
}

TEST_F(ListTest,GetDataRefTest){
    int &val_ref=integer_list->getItem(2);
    //change data of 3rd node (index 2)
    val_ref=9999;
    ASSERT_TRUE(9999==integer_list->getItem(2));
    val_ref=52;
    ASSERT_TRUE(52==integer_list->getItem(2));

    int *& ptr_ref=ptr_list->getItem(5);
    ptr_ref=NULL;
    ASSERT_TRUE(NULL==ptr_list->getItem(5));
    ptr_ref=arr[5];
    ASSERT_TRUE(arr[5]==ptr_list->getItem(5));

}

TEST_F(ListTest,GetDataCopyTest){
    int val_copy=integer_list->getItemCopy(2);
    val_copy=9000;
    ASSERT_FALSE(9000==integer_list->getItem(2));
    int * ptr_copy=ptr_list->getItemCopy(5);
    ptr_copy=NULL;
    ASSERT_FALSE(NULL==ptr_list->getItem(5));
}

TEST_F(ListTest,EmptyConstructorTest){
    // no error
    List<int> empty_list1;
    ASSERT_TRUE(0==empty_list1.getLen());
    // error???????????????????????
    // List<int> empty_list1();
    // ASSERT_TRUE(0==empty_list1.getLen());
}

TEST_F(ListTest,CopyConstructorTest){
    //error?????????????????????????????????????????
    // List<int> empty_list1();
    // int val=1;
    // empty_list1.insert(val);
    //--------------------------
    List<int> empty_list1;
    List<int> empty_list2(empty_list1);
    ASSERT_TRUE(0==empty_list1.getLen());
    List<int> lst(*integer_list);
    ASSERT_TRUE(6==lst.getLen());
    ASSERT_TRUE(50==lst.getItem(0));
    ASSERT_TRUE(51==lst.getItem(1));
    ASSERT_TRUE(52==lst.getItem(2));
    ASSERT_TRUE(53==lst.getItem(3));
    ASSERT_TRUE(54==lst.getItem(4));
    ASSERT_TRUE(55==lst.getItem(5));
}

TEST_F(ListTest,CopyTest){
    List<int> lst;
    int val=10;
    lst.insert(val);
    val++;
    lst.insert(val);
    lst.copyList(*integer_list);
    ASSERT_TRUE(6==lst.getLen());
    ASSERT_TRUE(50==lst.getItem(0));
    ASSERT_TRUE(51==lst.getItem(1));
    ASSERT_TRUE(52==lst.getItem(2));
    ASSERT_TRUE(53==lst.getItem(3));
    ASSERT_TRUE(54==lst.getItem(4));
    ASSERT_TRUE(55==lst.getItem(5));
}

TEST_F(ListTest,AppendListTest){
    List<int> lst;
    int val=10;
    lst.insert(val);
    val++;
    lst.insert(val);
    val++;
    lst.insert(val);

    lst.append(integer_list);
    ASSERT_TRUE(9==lst.getLen());

    ASSERT_TRUE(10==lst.getItem(0));
    ASSERT_TRUE(11==lst.getItem(1));
    ASSERT_TRUE(12==lst.getItem(2));
    ASSERT_TRUE(50==lst.getItem(3));
    ASSERT_TRUE(51==lst.getItem(4));
    ASSERT_TRUE(52==lst.getItem(5));
    ASSERT_TRUE(53==lst.getItem(6));
    ASSERT_TRUE(54==lst.getItem(7));
    ASSERT_TRUE(55==lst.getItem(8));
}

TEST_F(ListTest,ItemExistTest){
    int search_val=50;
    ASSERT_TRUE(integer_list->exists(search_val));
    search_val++;
    ASSERT_TRUE(integer_list->exists(search_val));
    search_val++;
    ASSERT_TRUE(integer_list->exists(search_val));
    search_val++;
    ASSERT_TRUE(integer_list->exists(search_val));
    search_val++;
    ASSERT_TRUE(integer_list->exists(search_val));
    search_val++;
    ASSERT_TRUE(integer_list->exists(search_val));
    search_val++;
    ASSERT_FALSE(integer_list->exists(search_val));
    search_val++;
    ASSERT_FALSE(integer_list->exists(search_val));
}

TEST_F(ListTest,GetDataPtrTest){
    int *val_ptr=integer_list->getItemPtr(5);
    *val_ptr=11111;
    ASSERT_TRUE(11111==integer_list->getItem(5));
    *val_ptr=55;
    ASSERT_TRUE(55==integer_list->getItem(5));

    int ** ptr_addr=ptr_list->getItemPtr(5);
    *ptr_addr=NULL;
    ASSERT_TRUE(NULL==ptr_list->getItem(5));
    *ptr_addr=arr[5];
    ASSERT_TRUE(arr[5]==ptr_list->getItem(5));
}
