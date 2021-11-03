cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(../bin/wordTests test_main.cpp word_test.cpp ../src/word.cpp)
# add_executable(../bin/entryTests test_main.cpp entry_test.cpp ../src/word.cpp ../src/entry.cpp)
# add_executable(../bin/listTests test_main.cpp word_test.cpp ../src/word.cpp ../src/entry.cpp ../include/list.hpp)
target_link_libraries(../bin/wordTests ${GTEST_LIBRARIES} pthread)
