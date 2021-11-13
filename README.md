# ***Inverted Search Engine*** (SIGMOD 2013)
## *sdi1700072* & *sdi1700055*

## Structure of the project:
As you can see above the project has the following directories:
\t 1) bin
\t 2) build
\t 3) input
\t 4) src
\t 5) include
\t 6) lib
\t 7) test

Each directory includes:
\t 1) the binary files
\t 2) the object files (.o)
\t 3) the input files to run the program
\t 4) the source files (.cpp)
\t 5) the header files (.hpp)
\t 6) the source files for unit-testing

## Structure of the project (on level of classes)

   Word   |List\<T\> |Vector\<T\>| HashTable |   Query  |   BKTree  | EntryList |  Index
--------- | -------- | --------- | --------- | -------- | --------- | --------- | --------
    _	  |     _    |     _     |  Entry *  |  Word ** |   Entry * |
    _     |     _    |     _     |     _     |     _    |Vector BKT |            | ----
