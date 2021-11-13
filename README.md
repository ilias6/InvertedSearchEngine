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

  Word | List\<T\> | Vector\<T\> | HashTable | Query | BKTree | EntryList | Index
   | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: 
     skata	| skata | sk | Entry | Word  | Entry  | Entry | BKTree
        sk | sku | skun | skunk | skunky | Vector BKT | me | choco
        
        
        
Word | List\<T\> | Vector\<T\> | HashTable | Query | BKTree | EntryList | Index
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
Content Cell  | Content Cell | Content Cell | Content Cell | Content Cell | Content Cell | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell | Content Cell | Content Cell | Content Cell | Content Cell | Content Cell

