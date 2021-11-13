# **Inverted Search Engine** *(SIGMOD 2013)*
## **sdi1700072** & **sdi1700055**

## Structure of the project:
As you can see above the project has the following directories:
 1) bin        -->   the binary files
 2) build      -->   the object files (.o)
 3) input      -->   the input files to run the program
 4) src        -->   the source files (.cpp)
 5) include    -->   the header files (.hpp)
 6) lib        -->   the libraries that are required (only gtest)
 7) test       -->   the source files for unit-testing

## Structure of the project (on level of classes)

Our basic classes:
Word | ListNode\<T\> | List\<T\> | Vector\<T\>
| :---: | :---: | :---: | :---:
char\* string | T data | ListNode\<T\>\* head | T[Actual Size]
int length | ListNode\<T\>* next | ListNode\<T\>\* tail | int length
_  | _ | int length | int actual_size |

And the composite ones:
Entry | Bucket | HashTable | Query | BKNode | BKTree | EntryList | Index
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
Word w | List\<Entry\*\> | Bucket\* array | Word\*\* | Entry\* e | metric | List\<Entry\> list | MatchType
List\<int\> | _ | int size | int id | int distance | BKNode\* root | HashTable t | BKTree\*\* trees (multiple trees for manhattan distance)
_ | _ | hash function | int numOfWords | Vector\<BKTreeNode\*\> children | int size | _ | HashTable \*
