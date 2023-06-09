// My structures - For Bison and Lex files

#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <stdbool.h>

typedef enum { MY_RELOP, MY_PLUS, MY_MINUS, MY_MUL, MY_DIV, MY_OR, MY_AND, MY_ASSIGN } Op;

typedef struct Val {
    char* sval;
    char* reg_name;
    char type; // 'i'-int , 'r'-real , 's'-string
    bool res_bool_exp;
    bool is_num; // is number
    bool is_exp; // is expression -> x+2
    bool is_paran; // is ()
} Val;

#endif
