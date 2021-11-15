#include <gtest/gtest.h>
#include "../include/vector.hpp"
#include "../include/hash_functions.hpp"
#include <stdexcept>
#include <ctime>
#include <cstdlib>

using namespace std;

class VectorTest: public ::testing::Test {
    protected:
        Vector<int>* int_vec;
        int data_size;
        int ** vec_data;
        Vector<int*>* ptr_vec;

        virtual void SetUp(){
            int arr[]={10,11,12,13,14,15,16,17,18,19};
            this->data_size=10;
            VectorErrorCode err_val;
            vec_data=new int*[data_size];
            int_vec=new Vector<int>;
            ptr_vec=new Vector<int*>;
            for(int i=0;i<data_size;i++){
                vec_data[i]=new int(arr[i]);
                err_val=int_vec->insert(*vec_data[i]);
                ASSERT_TRUE(err_val==V_SUCCESS);
                err_val=ptr_vec->insert(vec_data[i]);
                ASSERT_TRUE(err_val==V_SUCCESS);
            }

        }

        virtual void TearDown(){
            delete int_vec;
            delete ptr_vec;
            for(int i=0;i<data_size;i++)
                delete vec_data[i];
            delete[] vec_data;
        }
};

TEST_F(VectorTest,EmptyTest){
    Vector<int> vec;
    ASSERT_TRUE(0==vec.getLen());
    ASSERT_TRUE(0==vec.getActualMemoryLen());
    EXPECT_THROW({
        try{
            vec.getItem(0);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);

}

TEST_F(VectorTest,InsertTest){
    Vector<int> my_vec;
    Vector<int*> my_ptrvec;
    VectorErrorCode err_val1,err_val2;
    int actual_len=2;
    for(int i=0;i<data_size;i++){
        err_val1=my_vec.insert(*vec_data[i]);
        err_val2=my_ptrvec.insert(vec_data[i]);
        ASSERT_TRUE(err_val1==V_SUCCESS);
        ASSERT_TRUE(err_val2==V_SUCCESS);
        ASSERT_TRUE(i+1==my_vec.getLen());
        ASSERT_TRUE(i+1==my_ptrvec.getLen());
        if(i==actual_len){
            actual_len*=2;
            // this checks if array size is double when apropriate

            // firstly actual array size is cut in half
            int_vec->remove(*vec_data[i]);
            ptr_vec->remove(vec_data[i]);
            // and then must be doubled
            err_val1=int_vec->insert(*vec_data[i]);
            err_val2=ptr_vec->insert(vec_data[i]);
            ASSERT_TRUE(err_val1==V_SUCCESS);
            ASSERT_TRUE(err_val2==V_SUCCESS);
            ASSERT_TRUE(i+1==my_vec.getLen());
            ASSERT_TRUE(i+1==my_ptrvec.getLen());
            ASSERT_TRUE(true==int_vec->exists(*vec_data[i]));
            ASSERT_TRUE(true==ptr_vec->exists(vec_data[i]));
        }

        ASSERT_TRUE(actual_len==my_ptrvec.getActualMemoryLen());
        ASSERT_TRUE(actual_len==my_ptrvec.getActualMemoryLen());
        ASSERT_TRUE(vec_data[i]==my_ptrvec.getItem(i));
        ASSERT_TRUE(*vec_data[i]==my_vec.getItem(i));
        EXPECT_THROW({
            try{
                my_vec.getItem(i+1);
            }
            catch( const std::invalid_argument& e ){
                // and this tests that it has the correct message
                EXPECT_STREQ( "Index out of range", e.what() );
                throw;
            }
        },std::invalid_argument);
        EXPECT_THROW({
            try{
                my_ptrvec.getItem(i+1);
            }
            catch( const std::invalid_argument& e ){
                // and this tests that it has the correct message
                EXPECT_STREQ( "Index out of range", e.what() );
                throw;
            }
        },std::invalid_argument);
    }

}

TEST_F(VectorTest,RemoveTest){
    // removing from empty vector
    srand(time(NULL));
    Vector<int> empty_vec;
    VectorErrorCode err_val1,err_val2;;
    for(int i=0;i<data_size;i++){
        err_val1=empty_vec.remove(*vec_data[i]);
        ASSERT_TRUE(err_val1==V_EMPTY);
    }
    int old_actual_len=this->int_vec->getActualMemoryLen();
    for(int i=0;i<data_size;i++){
        // cout<<"to be rm: "<<*vec_data[i]<<endl;
        err_val1=int_vec->remove(*vec_data[i]);
        // int_vec->print();
        err_val2=ptr_vec->remove(vec_data[i]);
        ASSERT_TRUE(err_val1==V_SUCCESS);
        ASSERT_TRUE(err_val2==V_SUCCESS);
        ASSERT_TRUE(data_size-1-i==int_vec->getLen());
        ASSERT_TRUE(data_size-1-i==ptr_vec->getLen());
        ASSERT_TRUE(false==int_vec->exists(*vec_data[i]));
        ASSERT_TRUE(false==ptr_vec->exists(vec_data[i]));
        // checking in edge cases-> when inserting and size is doubled
        // check if remove cuts array size in half
        if((data_size-1-i)%2==0){
            // this also checks if removing from the end of array works
            int *val_ptr=new int(9999);
            int_vec->insert(*val_ptr);
            ptr_vec->insert(val_ptr);
                // int_vec->print();
                // cout<<"___________"<<endl;
            err_val1=int_vec->remove(*val_ptr);
            err_val2=ptr_vec->remove(val_ptr);
                // int_vec->print();
            ASSERT_TRUE(err_val1==V_SUCCESS);
            ASSERT_TRUE(err_val2==V_SUCCESS);
            ASSERT_TRUE(data_size-1-i==int_vec->getLen());
            ASSERT_TRUE(data_size-1-i==ptr_vec->getLen());
            ASSERT_TRUE(false==int_vec->exists(*val_ptr));
            ASSERT_TRUE(false==ptr_vec->exists(val_ptr));
            delete val_ptr;
        }

        //check if array downsize correct
        if(int_vec->getLen()==old_actual_len/2 && int_vec->getLen()!=1){
            // int_vec->print();
            old_actual_len/=2;
            ASSERT_TRUE(old_actual_len==int_vec->getActualMemoryLen());
        }else if (int_vec->getLen()==0){
            ASSERT_TRUE(0==int_vec->getActualMemoryLen());
        }else{
            ASSERT_TRUE(old_actual_len==int_vec->getActualMemoryLen());
        }


    }
    ASSERT_TRUE(0==int_vec->getLen());
    ASSERT_TRUE(0==ptr_vec->getLen());
    for(int i=0;i<data_size;i++){
        int_vec->insert(*vec_data[i]);
        ptr_vec->insert(vec_data[i]);
    }
    ASSERT_TRUE(data_size==int_vec->getLen());
    ASSERT_TRUE(data_size==ptr_vec->getLen());
    // now check removing from the middle
    err_val1=int_vec->remove(*vec_data[data_size/2]);
    err_val2=ptr_vec->remove(vec_data[data_size/2]);
    ASSERT_TRUE(err_val1==V_SUCCESS);
    ASSERT_TRUE(err_val2==V_SUCCESS);
    ASSERT_TRUE(data_size-1==int_vec->getLen());
    ASSERT_TRUE(data_size-1==ptr_vec->getLen());
    ASSERT_TRUE(false==int_vec->exists(*vec_data[data_size/2]));
    ASSERT_TRUE(false==ptr_vec->exists(vec_data[data_size/2]));

    err_val1=int_vec->remove(*vec_data[data_size/2+1]);
    err_val2=ptr_vec->remove(vec_data[data_size/2+1]);
    ASSERT_TRUE(err_val1==V_SUCCESS);
    ASSERT_TRUE(err_val2==V_SUCCESS);
    ASSERT_TRUE(data_size-2==int_vec->getLen());
    ASSERT_TRUE(data_size-2==ptr_vec->getLen());
    ASSERT_TRUE(false==int_vec->exists(*vec_data[data_size/2+1]));
    ASSERT_TRUE(false==ptr_vec->exists(vec_data[data_size/2+1]));
}



TEST_F(VectorTest,GetItemTest){
    for(int i=0;i<data_size;i++){
        int& item=int_vec->getItem(i);
        int*& item_ptr=ptr_vec->getItem(i);
        item++;
        item_ptr=NULL;
        ASSERT_TRUE(item==int_vec->getItem(i));
        ASSERT_TRUE(item_ptr==ptr_vec->getItem(i));
    }
    EXPECT_THROW({
        try{
            int_vec->getItem(1000);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            int_vec->getItem(-1);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            ptr_vec->getItem(-1);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            ptr_vec->getItem(1000);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
}

TEST_F(VectorTest,GetItemCopyTest){
    for(int i=0;i<data_size;i++){
        int item=int_vec->getItem(i);
        int* item_ptr=ptr_vec->getItem(i);
        item++;
        item_ptr=NULL;
        ASSERT_FALSE(item==int_vec->getItem(i));
        ASSERT_FALSE(item_ptr==ptr_vec->getItem(i));
    }
    EXPECT_THROW({
        try{
            int_vec->getItem(1000);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            int_vec->getItem(-1);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            ptr_vec->getItem(-1);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);
    EXPECT_THROW({
        try{
            ptr_vec->getItem(1000);
        }
        catch( const std::invalid_argument& e ){
            // and this tests that it has the correct message
            EXPECT_STREQ( "Index out of range", e.what() );
            throw;
        }
    },std::invalid_argument);

}

TEST_F(VectorTest,ExistsTest){
    for(int i=0;i<data_size;i++){
        ASSERT_TRUE(int_vec->exists(*vec_data[i]));
        ASSERT_TRUE(ptr_vec->exists(vec_data[i]));
    }
    int not_exists=99999;
    ASSERT_FALSE(int_vec->exists(not_exists));
    int *ptr_not_exists=new int(-1000);
    ASSERT_FALSE(ptr_vec->exists(ptr_not_exists));
    delete ptr_not_exists;
}

TEST_F(VectorTest,CopyConstructorTest){
    Vector<int> copied_int_vec(*int_vec);
    Vector<int*> copied_ptr_vec(*ptr_vec);
    ASSERT_TRUE(int_vec->getLen()==copied_int_vec.getLen());
    ASSERT_TRUE(ptr_vec->getLen()==copied_ptr_vec.getLen());
    ASSERT_TRUE(int_vec->getActualMemoryLen()==copied_int_vec.getActualMemoryLen());
    ASSERT_TRUE(ptr_vec->getActualMemoryLen()==copied_ptr_vec.getActualMemoryLen());
    for(int i=0;i<data_size;i++){
        ASSERT_TRUE(copied_int_vec.exists(*vec_data[i]));
        ASSERT_TRUE(copied_ptr_vec.exists(vec_data[i]));
    }
    int not_exists=99999;
    ASSERT_FALSE(copied_int_vec.exists(not_exists));
    int *ptr_not_exists=new int(-1000);
    ASSERT_FALSE(copied_ptr_vec.exists(ptr_not_exists));
    delete ptr_not_exists;
}

TEST_F(VectorTest,CopyVectorTest){

    {
        // copy to an empty vector an empty vector
        Vector<int> empty_vec1;
        Vector<int> empty_vec2;
        empty_vec1.copyVector(empty_vec2);
        ASSERT_TRUE(empty_vec1.getLen()==empty_vec2.getLen());
        ASSERT_TRUE(empty_vec1.getActualMemoryLen()==empty_vec2.getActualMemoryLen());
    }

    {
        //try copy with empty vec
        Vector<int> copied_int_vec;
        Vector<int*> copied_ptr_vec;
        copied_int_vec.copyVector(*int_vec);
        copied_ptr_vec.copyVector(*ptr_vec);

        ASSERT_TRUE(int_vec->getLen()==copied_int_vec.getLen());
        ASSERT_TRUE(ptr_vec->getLen()==copied_ptr_vec.getLen());
        ASSERT_TRUE(int_vec->getActualMemoryLen()==copied_int_vec.getActualMemoryLen());
        ASSERT_TRUE(ptr_vec->getActualMemoryLen()==copied_ptr_vec.getActualMemoryLen());
        for(int i=0;i<data_size;i++){
            ASSERT_TRUE(copied_int_vec.exists(*vec_data[i]));
            ASSERT_TRUE(copied_ptr_vec.exists(vec_data[i]));
        }
        int not_exists=99999;
        ASSERT_FALSE(copied_int_vec.exists(not_exists));
        int *ptr_not_exists=new int(-1000);
        ASSERT_FALSE(copied_ptr_vec.exists(ptr_not_exists));
        delete ptr_not_exists;
    }
    // try copy with non empty vec
    Vector<int> copied_int_vec;
    Vector<int*> copied_ptr_vec;
    int *val=new int(9999);
    copied_int_vec.insert(*val);
    copied_ptr_vec.insert(val);
    copied_int_vec.copyVector(*int_vec);
    copied_ptr_vec.copyVector(*ptr_vec);
    delete val;
    ASSERT_TRUE(int_vec->getLen()==copied_int_vec.getLen());
    ASSERT_TRUE(ptr_vec->getLen()==copied_ptr_vec.getLen());
    ASSERT_TRUE(int_vec->getActualMemoryLen()==copied_int_vec.getActualMemoryLen());
    ASSERT_TRUE(ptr_vec->getActualMemoryLen()==copied_ptr_vec.getActualMemoryLen());
    for(int i=0;i<data_size;i++){
        ASSERT_TRUE(copied_int_vec.exists(*vec_data[i]));
        ASSERT_TRUE(copied_ptr_vec.exists(vec_data[i]));
    }
    int not_exists=99999;
    ASSERT_FALSE(copied_int_vec.exists(not_exists));
    int *ptr_not_exists=new int(-1000);
    ASSERT_FALSE(copied_ptr_vec.exists(ptr_not_exists));
    delete ptr_not_exists;
}
//
// TEST_F(VectorTest,AppendVectorTest){
//     //append to a non empty vector a non empty vector
//     {
//         Vector<int> vec;
//         for(int i=0;i<1000;i++)
//             vec.insert(i);
//         int old_actual_len=vec.getActualMemoryLen();
//         vec.append(*int_vec);
//         ASSERT_TRUE(vec.getLen()==int_vec->getLen()+1000);
//         ASSERT_TRUE(vec.getActualMemoryLen()==int_vec->getActualMemoryLen()+);
//
//
//     }
//     //append to a non empty vector an ampty vector
//     {
//
//     }
//      // append to an empty vector a non empty vector
//      {
//
//      }
//      // append to an empty vector and empty vector
// }
