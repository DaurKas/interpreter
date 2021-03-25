#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>
using namespace std;
enum OPERATOR {
    LBRACKET, RBRACKET,
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
extern int PRIORITY[];
extern string OPERTEXT[];
extern int OP_NUM; 
