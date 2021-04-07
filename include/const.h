#ifndef CONST_H
#define CONST_H
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>
using namespace std;
enum OPERATOR {
    IF, THEN,
    ELSE, ENDIF,
    WHILE, ENDWHILE,
    GOTO, LBRACKET, RBRACKET, COLON,
    ASSIGN,
    OR,
    AND,
    BITOR,
    XOR,
    BITAND,
    EQ, NEQ,
    LEQ, LT,
    GEQ, GT,
    SHL, SHR,
    PLUS, MINUS,
    MULTIPLY, DIV, MOD
};
enum LEXEM_TYPE {
    NUMBER, OPER,
    VARIABLE, LEXEM
};
extern int PRIORITY[];
extern string OPERTEXT[];
extern int OP_NUM;
#endif
