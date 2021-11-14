# **Inverted Search Engine** *(SIGMOD 2013)*
### **sdi1700072** & **sdi1700055**

## Structure of the project:
As you can see above the project has the following directories:
 1) bin        -->   the binary files
 2) build      -->   the object files (.o)
 3) input      -->   the input files to run the program
 4) src        -->   the source files (.cpp)
 5) include    -->   the header files (.hpp)
 6) lib        -->   the libraries that are required (only gtest)
 7) test       -->   the source files for unit-testing

## Structure of the project (class diagram)

### Our basic classes:
Word | ListNode\<T\> | List\<T\> | Vector\<T\>
| :---: | :---: | :---: | :---:
char\* string | T data | ListNode\<T\>\* head | T[Actual Size]
int length | ListNode\<T\>* next | ListNode\<T\>\* tail | int length
_  | _ | int length | int actual_size |

### And the composite ones:
Entry | Bucket | HashTable | Query | BKNode | BKTree | EntryList | Index
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
Word w | List\<Entry\*\> | Bucket\* array | Word\*\* | Entry\* e | metric | List\<Entry\> list | MatchType
List\<int\> | _ | int size | int id | int distance (from parent) | BKNode\* root | HashTable t | BKTree\*\* trees (multiple trees for manhattan distance)
_ | _ | hash function | int numOfWords | Vector\<BKTreeNode\*\> children | int size | _ | HashTable \*


## Make it run!
For this first part of the project, the input to test our program has the following struct: one file represents one query. The query file
has five words at maximum (whatever whitespaces are skipped).\
So a bash script is written that for a given file of words, produces files with >=5 words.\
The script (make_query_files.sh) is located in the input directory. Also, a file that contains a lot of words is provided for this purpose.\
### Execution example:
```bash
./input/make_query_files.sh ./input/words 10000
```
The second parameter stands for the number of files to be made.

### For the main program, run the Makefile first:
```bash
make
```
In the Makefile, the command:
```bash
sudo apt-get install libgtest-dev
```
is needed, as we used the gtest framework for unit-testing. The two .a files in lib/ are linked at the compilation of the unit-test binary, so that is the only thing that you must install to your system.\
\
As we said before, the bin/ directory contains the "out" and the "test" binary files.\
Execution example for the first one:
```bash
./bin/out ./queries/ 5000
```
*or*
```bash
./bin/out ./input/queries/ 10000
```
The queries directory is made by the script, so check where it is created before running this one.\
Execution example for the second one:
```bash
./bin/test
```
