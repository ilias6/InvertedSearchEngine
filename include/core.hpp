#ifndef __CORE_HPP__
#define __CORE_HPP__
#define 	MAX_DOC_LENGTH   (1<<22)
#define 	MAX_WORD_LENGTH   31
#define 	MIN_WORD_LENGTH   4
#define 	MAX_QUERY_WORDS   5
#define     MAX_DOC_WORDS     ((MAX_DOC_LENGTH)/(MIN_WORD_LENGTH))
#define 	MAX_QUERY_LENGTH   ((MAX_WORD_LENGTH+1)*MAX_QUERY_WORDS)
#define SHOW_DEFINE(x) printf("%s=%d\n", #x,x);
#define PRINT_CORE_SETTINGS()\
{\
    SHOW_DEFINE(MAX_DOC_LENGTH)\
    SHOW_DEFINE(MAX_WORD_LENGTH)\
    SHOW_DEFINE(MIN_WORD_LENGTH)\
    SHOW_DEFINE(MAX_QUERY_WORDS)\
    SHOW_DEFINE(MAX_DOC_WORDS)\
    SHOW_DEFINE(MAX_QUERY_LENGTH)\
}
#endif