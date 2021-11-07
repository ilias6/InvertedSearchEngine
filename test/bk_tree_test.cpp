#include <gtest/gtest.h>
#include "../include/BK_tree.hpp"
#include <stdexcept>

class BKTreeTest: public ::testing::Test {
    protected:
        BKTree * edit_tree;//edit distance tree
        int edit_data_size;
        Data ** edit_data;//data for edit distance insertion
        BKTree * hamming_tree;//hamming distance tree
        int hamming_data_size;
        Data ** hamming_data;//data for hamming distance
        virtual void SetUp(){
            edit_tree=new BKTree(&Word::editDist);
            edit_data=new Data *[10];
            edit_data_size=8;
            hamming_tree=new BKTree(&Word::hammingDist);
            hamming_data=new Data *[8];
            hamming_data_size=8;
            const char str_arr[][8]={{"hell"},{"help"},{"fall"},{"felt"},{"fell"},{"small"},
            {"melt"},{"swall"}};
            BKErrorCode err_val;
            for(int i=0;i<edit_data_size;i++){
                edit_data[i]=new Data(str_arr[i],0);
                err_val=edit_tree->insert(edit_data[i]);
                ASSERT_TRUE(err_val==BK_SUCCESS);//succesful insert
            }
            const char str1_arr[][4]={{"aaa"},{"aab"},{"abb"},{"aba"},{"baa"},{"bab"},
            {"bba"},{"bbb"}};
            for(int i=0;i<hamming_data_size;i++){
                hamming_data[i]=new Data(str1_arr[i],0);
                err_val=hamming_tree->insert(hamming_data[i]);
                ASSERT_TRUE(err_val==BK_SUCCESS);//succesful insert
            }
        }

        virtual void TearDown(){
            delete edit_tree;
            delete hamming_tree;
            for(int i=0;i<edit_data_size;i++)
                delete edit_data[i];
            delete[] edit_data;
            for(int i=0;i<hamming_data_size;i++)
                delete hamming_data[i];
            delete[] hamming_data;
        }
};

TEST_F(BKTreeTest,InsertTest){
    // added int size to tree to hold num of nodes to test insert
    BKTree e_tree(&Word::editDist);
    BKTree h_tree(&Word::hammingDist);
    BKErrorCode err_val;
    // begin with empty tree -> insert->check size==1 and search
    //insert ->size==2 and search
    //insert-> size==3 and search

}

TEST_F(BKTreeTest,SearchTest){
    //search to instance of class BKTreeTest
}
