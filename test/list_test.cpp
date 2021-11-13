#include <gtest/gtest.h>
#include "../include/list.hpp"
#include "../include/word.hpp"
#include <stdexcept>


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
        int **arr;
        List<int *> *ptr_list;

        virtual void SetUp(){
            // for constructor assertion
            // for int list
            ListErrorCode err_val1,err_val2;
            integer_list=new List<int>;
            ptr_list=new List<int*>;
            arr=new int*[6];
            for(int i=0;i<6;i++)
                arr[i]=new int(50+i);
            for(int i=0;i<6;i++){
                err_val1=integer_list->insert(*arr[i]);
                ASSERT_TRUE(err_val1==L_SUCCESS);//succesful rm
                err_val2=ptr_list->insert(arr[i]);
                ASSERT_TRUE(err_val2==L_SUCCESS);//succesful rm
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
    for(int i=0;i<6;i++)
        ASSERT_TRUE(50+i==integer_list->getItem(i));
    ListErrorCode err_val;
    int *val;
    int new_insert_val=800;
    err_val=integer_list->insert(new_insert_val,&val);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful insert
    ASSERT_TRUE(7==integer_list->getLen());
    ASSERT_TRUE(800==integer_list->getItem(6));
    ASSERT_TRUE(800==*val);
    *val=799;
    ASSERT_TRUE(799==integer_list->getItem(6));
    for(int i=0;i<6;i++)
        ASSERT_TRUE(arr[i]==ptr_list->getItem(i));
    EXPECT_THROW({
        try{
            integer_list->getItem(7);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    // stress the list
    List<int> stressed_list;
    for(int i=0;i<1000;i++){
        err_val=stressed_list.insert(i);
        ASSERT_TRUE(err_val==L_SUCCESS);//succesful insert
        ASSERT_TRUE(i+1==stressed_list.getLen());//check len
        ASSERT_TRUE(i==stressed_list.getItem(i));
    }


}

TEST_F(ListTest,RemoveTest){
    int to_be_rm=100000;
    ASSERT_TRUE(6==integer_list->getLen());
    ListErrorCode err_val;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_NOT_EXISTS);//item doesn't exist
    ASSERT_TRUE(6==integer_list->getLen());
    to_be_rm=50;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful rm
    ASSERT_TRUE(5==integer_list->getLen());
    ASSERT_TRUE(51==integer_list->getItem(0));
    ASSERT_TRUE(52==integer_list->getItem(1));
    to_be_rm=52;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful rm
    ASSERT_TRUE(4==integer_list->getLen());
    ASSERT_TRUE(53==integer_list->getItem(1));
    to_be_rm=55;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful rm
    ASSERT_TRUE(3==integer_list->getLen());
    ASSERT_TRUE(54==integer_list->getItem(2));
    to_be_rm=51;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful rm
    ASSERT_TRUE(2==integer_list->getLen());
    ASSERT_TRUE(53==integer_list->getItem(0));
    ASSERT_TRUE(54==integer_list->getItem(1));
    to_be_rm=53;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful rm
    ASSERT_TRUE(1==integer_list->getLen());
    ASSERT_TRUE(54==integer_list->getItem(0));
    to_be_rm=54;
    err_val=integer_list->remove(to_be_rm);
    ASSERT_TRUE(err_val==L_SUCCESS);//succesful rm
    ASSERT_TRUE(0==integer_list->getLen());
    ASSERT_TRUE(L_EMPTY==integer_list->remove(to_be_rm));

    // stress the list
    List<int> stressed_list;
    for(int i=0;i<1000;i++)
        stressed_list.insert(i);
    srand(time(NULL));
    int rand_indx;
    int sz=1000;
    // remove from start
    for(int i=0;i<300;i++){
        err_val=stressed_list.remove(i);
        sz--;
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(sz==stressed_list.getLen());
        ASSERT_FALSE(stressed_list.exists(i));
    }
    //now list contains [300-999]
    // remove from end
    int k;
    for(int i=0;i<399;i++){
        k=999-i;
        err_val=stressed_list.remove(k);
        sz--;
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(sz==stressed_list.getLen());
        ASSERT_FALSE(stressed_list.exists(k));
    }
    //now list contains [300-600]
    //remove rom middle
    for(int i=400;i<500;i++){
        err_val=stressed_list.remove(i);
        sz--;
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(sz==stressed_list.getLen());
        ASSERT_FALSE(stressed_list.exists(i));
    }


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
    EXPECT_THROW({
        try{
            integer_list->getItem(6);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            integer_list->getItem(-1);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);

}

TEST_F(ListTest,GetDataCopyTest){
    int val_copy=integer_list->getItemCopy(2);
    val_copy=9000;
    ASSERT_FALSE(val_copy==integer_list->getItem(2));
    int * ptr_copy=ptr_list->getItemCopy(5);
    ptr_copy=NULL;
    ASSERT_FALSE(ptr_copy==ptr_list->getItem(5));
    EXPECT_THROW({
        try{
            integer_list->getItem(6);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            integer_list->getItem(-1);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
}

TEST_F(ListTest,EmptyConstructorTest){
    List<int> empty_list1;
    ASSERT_TRUE(0==empty_list1.getLen());
    int v=99999;
    ASSERT_TRUE(L_EMPTY==empty_list1.remove(v));
    EXPECT_THROW({
        try{
            empty_list1.getItem(0);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
}

TEST_F(ListTest,CopyConstructorTest){
    List<int> empty_list1;
    List<int> empty_list2(empty_list1);
    ASSERT_TRUE(0==empty_list1.getLen());
    List<int> lst(*integer_list);
    ASSERT_TRUE(6==lst.getLen());
    for(int i=0;i<6;i++)
        ASSERT_TRUE(50+i==lst.getItem(i));

    EXPECT_THROW({
        try{
            integer_list->getItem(6);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
}

TEST_F(ListTest,CopyTest){
    {
        //copy to a non empty list a non empty list
        List<int> lst;
        int val=10;
        lst.insert(val);
        val++;
        lst.insert(val);
        lst.copyList(*integer_list);
        ASSERT_TRUE(6==lst.getLen());
        for(int i=0;i<6;i++)
            ASSERT_TRUE(50+i==lst.getItem(i));
        EXPECT_THROW({
            try{
                lst.getItem(6);
            }
            catch( const std::invalid_argument& e ){
                // and this tests that it has the correct message
                EXPECT_STREQ( "Index out of range", e.what() );
                throw;
            }
        },std::invalid_argument);
    }
    {
        // copy to an empty list a non empty list
        List<int> lst;
        lst.copyList(*integer_list);
        ASSERT_TRUE(6==lst.getLen());
        for(int i=0;i<6;i++)
            ASSERT_TRUE(50+i==lst.getItem(i));
    }
    {
        // copy to an empty list an empty list
        List<int> lst;
        List <int> empty;
        lst.copyList(empty);
        ASSERT_TRUE(0==lst.getLen());
        ListErrorCode err;
        int not_exists=0;
        err=lst.remove(not_exists);
        ASSERT_TRUE(err==L_EMPTY);

    }

    {
        // copy to a non empty list an empty list
        List <int> empty;
        integer_list->copyList(empty);
        ASSERT_TRUE(0==integer_list->getLen());
        ListErrorCode err;
        int not_exists=0;
        err=integer_list->remove(not_exists);
        ASSERT_TRUE(err==L_EMPTY);

    }

}

TEST_F(ListTest,AppendListTest){
    {
        //apend to a non empty a non empty
        List<int> lst;
        int val;
        ListErrorCode err_val;

        for(int i=0;i<3;i++){
            val=10+i;
            lst.insert(val);
        }
        err_val=lst.append(integer_list);
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(9==lst.getLen());
        for(int i=0;i<3;i++)
            ASSERT_TRUE(10+i==lst.getItem(i));
        for(int i=3;i<9;i++)
            ASSERT_TRUE(47+i==lst.getItem(i));

        EXPECT_THROW({
            try{
                lst.getItem(9);
            }
            catch( const std::invalid_argument& e ){
                // and this tests that it has the correct message
                EXPECT_STREQ( "Index out of range", e.what() );
                throw;
            }
        },std::invalid_argument);
    }
    {
        //append to a non empty an empty
        List <int> empty;
        ListErrorCode err_val;
        err_val=integer_list->append(&empty);
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(6==integer_list->getLen());
    }
    {
        //append to an empty a non empty
        List <int> empty;
        ListErrorCode err_val;
        err_val=empty.append(integer_list);
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(6==empty.getLen());
        for(int i=0;i<6;i++)
            ASSERT_TRUE(50+i==empty.getItem(i));
    }
    {
        //append to an empty an empty
        List <int> empty;
        List <int> empty2;
        ListErrorCode err_val;
        err_val=empty.append(&empty2);
        ASSERT_TRUE(err_val==L_SUCCESS);
        ASSERT_TRUE(0==empty.getLen());
    }
}

TEST_F(ListTest,ItemExistTest){
    int search_val;
    for(int i=0;i<6;i++){
        search_val=50+i;
        ASSERT_TRUE(integer_list->exists(search_val));
    }
    search_val=999;
    ASSERT_FALSE(integer_list->exists(search_val));
    List<int> empty;
    ASSERT_FALSE(empty.exists(search_val));

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
    EXPECT_THROW({
        try{
            integer_list->getItem(6);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
}
