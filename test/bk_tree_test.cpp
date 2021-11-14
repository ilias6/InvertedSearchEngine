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
            edit_data=new Data *[8];
            edit_data_size=8;
            hamming_tree=new BKTree(&Word::hammingDist);
            hamming_data=new Data *[10];
            hamming_data_size=10;
            const char str_arr[][8]={{"hell"},{"help"},{"fall"},{"felt"},{"fell"},{"small"},
            {"melt"},{"swall"}};
            BKErrorCode err_val;
            for(int i=0;i<edit_data_size;i++){
                edit_data[i]=new Data(str_arr[i],0);
                err_val=edit_tree->insert(edit_data[i]);
                ASSERT_TRUE(err_val==BK_SUCCESS);//succesful insert
            }
            const char str1_arr[][4]={{"aaa"},{"aab"},{"abb"},{"aba"},{"baa"},{"bab"},
            {"bba"},{"bbb"},{"aa"},{"e"}};
            for(int i=0;i<hamming_data_size;i++){
                hamming_data[i]=new Data(str1_arr[i],0);
                if(i<8){
                    err_val=hamming_tree->insert(hamming_data[i]);
                    ASSERT_TRUE(err_val==BK_SUCCESS);//succesful insert
                }
            }

        }
        void checkInsert(BKTree * tree,int size,int indx,Data **data,BKErrorCode err_val){
            List<Data *> *data_list;
            ASSERT_TRUE(err_val==BK_SUCCESS);//succesful insert
            ASSERT_TRUE(size==tree->getSize());
            data_list=new List<Data*>(tree->search(&data[indx]->getWord(),0));
            ASSERT_TRUE(1==data_list->getLen());
            ASSERT_TRUE(data[indx]==data_list->getItem(0));
            delete data_list;
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

    for(int i=0;i<edit_data_size;i++){
        err_val=e_tree.insert(edit_data[i]);
        checkInsert(&e_tree,i+1,i,edit_data,err_val);
    }

    for(int i=0;i<hamming_data_size-2;i++){
        err_val=h_tree.insert(hamming_data[i]);
        checkInsert(&h_tree,i+1,i,hamming_data,err_val);
    }
    ASSERT_TRUE(8==h_tree.getSize());
    err_val=h_tree.insert(hamming_data[8]);
    ASSERT_TRUE(err_val==BK_FAIL);//failed insert because word len is different
    ASSERT_TRUE(8==h_tree.getSize());
    err_val=h_tree.insert(hamming_data[8]);
    ASSERT_TRUE(err_val==BK_FAIL);//failed insert because word len is different
    ASSERT_TRUE(8==h_tree.getSize());
    // h_tree.print();
}

TEST_F(BKTreeTest, EmptySearchTest) {
    Word * w = new Word("");
    List<Data *> lst = edit_tree->search(w, 0);
    ASSERT_TRUE(lst.getLen() == 0);
}

TEST_F(BKTreeTest,SearchTest){
    //search to instance of class BKTreeTest
    // edit tree contains:"hell","help","fall","felt","fell","small","melt","swall";
    List<Data *> *data_list;
    /*
                        EDIT TREE SEARCH START
                                                        */
    //search "hell" with threshold 1
    //must return "hell","help","fell"
    data_list=new List<Data*>(edit_tree->search(&edit_data[0]->getWord(),1));
    ASSERT_TRUE(3==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));//hell
    ASSERT_TRUE(data_list->exists(edit_data[1]));//help
    ASSERT_TRUE(data_list->exists(edit_data[4]));//fell
    delete data_list;
    //search "hell" with threshold 2
    //must return "hell","help","fell","fall","felt","melt"
    data_list=new List<Data*>(edit_tree->search(&edit_data[0]->getWord(),2));
    ASSERT_TRUE(6==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));//hell
    ASSERT_TRUE(data_list->exists(edit_data[1]));//help
    ASSERT_TRUE(data_list->exists(edit_data[4]));//fell
    ASSERT_TRUE(data_list->exists(edit_data[2]));//fall
    ASSERT_TRUE(data_list->exists(edit_data[3]));//felt
    ASSERT_TRUE(data_list->exists(edit_data[6]));//melt
    delete data_list;
    //search "hell" with threshold 3
    //must return ALL WORDS

    data_list=new List<Data*>(edit_tree->search(&edit_data[0]->getWord(),3));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[5]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[7]));
    delete data_list;

    //search "melt" with threshold 0
    //must return "melt"
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),0));
    ASSERT_TRUE(1==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    delete data_list;
    //search "melt" with threshold 1
    //must return "felt","melt"
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),1));
    ASSERT_TRUE(2==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    delete data_list;
    //search "melt" with threshold 2
    //must return "felt","melt","fell","help","hell"
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),2));
    ASSERT_TRUE(5==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    delete data_list;
    //search "melt" with threshold 3
    //must return all words except swall
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),3));
    ASSERT_TRUE(7==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[5]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    delete data_list;
    //search "melt" with threshold 4
    //must return all words
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),4));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[5]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[7]));
    delete data_list;

    //search "melt" with threshold 5
    //must return all words
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),5));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[5]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[7]));
    delete data_list;
    //search "melt" with threshold 5
    //must return all words
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),5));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[5]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[7]));
    delete data_list;

    //search with negative threshold
    //must return empty list
    data_list=new List<Data*>(edit_tree->search(&edit_data[6]->getWord(),-1));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;

    //search "e" with threshold 0
    //must return empty list
    data_list=new List<Data*>(edit_tree->search(&hamming_data[9]->getWord(),0));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;
    //search "e" with threshold 1
    //must return empty list
    data_list=new List<Data*>(edit_tree->search(&hamming_data[9]->getWord(),1));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;
    //search "e" with threshold 2
    //must return empty list
    data_list=new List<Data*>(edit_tree->search(&hamming_data[9]->getWord(),2));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;

    //search "e" with threshold 3
    //must return "hell","help","fell","felt","melt"
    data_list=new List<Data*>(edit_tree->search(&hamming_data[9]->getWord(),3));
    ASSERT_TRUE(5==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    delete data_list;
    //search "e" with threshold 4
    //must return all words except "small" and "swall"
    data_list=new List<Data*>(edit_tree->search(&hamming_data[9]->getWord(),4));
    ASSERT_TRUE(6==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    delete data_list;

    //search "e" with threshold 5
    //must return all words
    data_list=new List<Data*>(edit_tree->search(&hamming_data[9]->getWord(),5));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(edit_data[0]));
    ASSERT_TRUE(data_list->exists(edit_data[1]));
    ASSERT_TRUE(data_list->exists(edit_data[2]));
    ASSERT_TRUE(data_list->exists(edit_data[3]));
    ASSERT_TRUE(data_list->exists(edit_data[4]));
    ASSERT_TRUE(data_list->exists(edit_data[5]));
    ASSERT_TRUE(data_list->exists(edit_data[6]));
    ASSERT_TRUE(data_list->exists(edit_data[7]));
    delete data_list;
    /*
                        EDIT TREE SEARCH END
                                                        */
    /*
                       HAMMING TREE SEARCH START
                                                        */


    //search "aaa" with threshold 0
    //must return "aaa"
    data_list=new List<Data*>(hamming_tree->search(&hamming_data[0]->getWord(),0));
    ASSERT_TRUE(1==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    delete data_list;
    //search "aaa" with threshold 1
    //must return "aaa","aab","aba","baa"
    data_list=new List<Data*>(hamming_tree->search(&hamming_data[0]->getWord(),1));
    ASSERT_TRUE(4==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    ASSERT_TRUE(data_list->exists(hamming_data[1]));
    ASSERT_TRUE(data_list->exists(hamming_data[3]));
    ASSERT_TRUE(data_list->exists(hamming_data[4]));
    delete data_list;

    //search "aaa" with threshold 2
    //must return "aaa","aab","aba","baa","abb","bab","bba"
    data_list=new List<Data*>(hamming_tree->search(&hamming_data[0]->getWord(),2));
    ASSERT_TRUE(7==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    ASSERT_TRUE(data_list->exists(hamming_data[1]));
    ASSERT_TRUE(data_list->exists(hamming_data[2]));
    ASSERT_TRUE(data_list->exists(hamming_data[3]));
    ASSERT_TRUE(data_list->exists(hamming_data[4]));
    ASSERT_TRUE(data_list->exists(hamming_data[5]));
    ASSERT_TRUE(data_list->exists(hamming_data[6]));
    delete data_list;
    //search "aaa" with threshold 3
    //must return all words
    data_list=new List<Data*>(hamming_tree->search(&hamming_data[0]->getWord(),3));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    ASSERT_TRUE(data_list->exists(hamming_data[1]));
    ASSERT_TRUE(data_list->exists(hamming_data[2]));
    ASSERT_TRUE(data_list->exists(hamming_data[3]));
    ASSERT_TRUE(data_list->exists(hamming_data[4]));
    ASSERT_TRUE(data_list->exists(hamming_data[5]));
    ASSERT_TRUE(data_list->exists(hamming_data[6]));
    ASSERT_TRUE(data_list->exists(hamming_data[7]));
    delete data_list;
    //search "aaa" with threshold 4
    //must return all words
    data_list=new List<Data*>(hamming_tree->search(&hamming_data[0]->getWord(),4));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    ASSERT_TRUE(data_list->exists(hamming_data[1]));
    ASSERT_TRUE(data_list->exists(hamming_data[2]));
    ASSERT_TRUE(data_list->exists(hamming_data[3]));
    ASSERT_TRUE(data_list->exists(hamming_data[4]));
    ASSERT_TRUE(data_list->exists(hamming_data[5]));
    ASSERT_TRUE(data_list->exists(hamming_data[6]));
    ASSERT_TRUE(data_list->exists(hamming_data[7]));
    delete data_list;

    //search "aaa" with negative threshold
    //must return empty list
    data_list=new List<Data*>(hamming_tree->search(&hamming_data[0]->getWord(),-1));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;

    Data * dd=new Data("ccc",0);
    // now lets search something that doesn't exist
    // -> result must be empty list
    data_list=new List<Data*>(hamming_tree->search(&dd->getWord(),0));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;

    data_list=new List<Data*>(hamming_tree->search(&dd->getWord(),1));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;

    data_list=new List<Data*>(hamming_tree->search(&dd->getWord(),2));
    ASSERT_TRUE(0==data_list->getLen());
    delete data_list;

    // if threshold 3
    // result will be all words
    data_list=new List<Data*>(hamming_tree->search(&dd->getWord(),3));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    ASSERT_TRUE(data_list->exists(hamming_data[1]));
    ASSERT_TRUE(data_list->exists(hamming_data[2]));
    ASSERT_TRUE(data_list->exists(hamming_data[3]));
    ASSERT_TRUE(data_list->exists(hamming_data[4]));
    ASSERT_TRUE(data_list->exists(hamming_data[5]));
    ASSERT_TRUE(data_list->exists(hamming_data[6]));
    ASSERT_TRUE(data_list->exists(hamming_data[7]));
    delete data_list;
    // if threshold bigger than len of word
    // result will be all words
    data_list=new List<Data*>(hamming_tree->search(&dd->getWord(),4));
    ASSERT_TRUE(8==data_list->getLen());
    ASSERT_TRUE(data_list->exists(hamming_data[0]));
    ASSERT_TRUE(data_list->exists(hamming_data[1]));
    ASSERT_TRUE(data_list->exists(hamming_data[2]));
    ASSERT_TRUE(data_list->exists(hamming_data[3]));
    ASSERT_TRUE(data_list->exists(hamming_data[4]));
    ASSERT_TRUE(data_list->exists(hamming_data[5]));
    ASSERT_TRUE(data_list->exists(hamming_data[6]));
    ASSERT_TRUE(data_list->exists(hamming_data[7]));
    delete data_list;

    delete dd;
    //OUR INDEX WILL MAKE SURE THAT WORDS BEING SEARCHED
    //WON;T BE OF DIFFERENT LENGTH

    /*
                       HAMMING TREE SEARCH END
                                                        */
}
