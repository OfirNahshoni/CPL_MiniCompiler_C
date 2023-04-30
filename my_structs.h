// My structures - For Bison and Lex files

#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

typedef enum { MY_RELOP, MY_PLUS, MY_MINUS, MY_MUL, MY_DIV, MY_OR, MY_AND, MY_ASSIGN } Op;

typedef struct Val {
    char* sval;
    char type; // 'i'-int , 'r'-real , 's'-string
} Val;

#endif
