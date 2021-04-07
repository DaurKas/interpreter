#include "const.h"
int PRIORITY[] = {
    -2, -2,
    -2, -2,
    -2, -1,
    -1, -1, -1, -1,
    0,
    1,
    3,
    4,
    5,
    6, 6,
    7, 7,
    7, 7,
    8, 8,
    9, 9,
    10, 10, 10
};
string OPERTEXT[] = {
    "if", "then",
    "else", "endif",
    "while", "endwhile",
    "goto", "(", ")", "?",
    ":=",
    "or",
    "and",
    "|",
    "^",
    "&",
    "==", "!=",
    "<=", "<",
    ">=", ">",
    "shl", "shr",
    "+", "-",
    "*", "/", "%"
};
int OP_NUM = sizeof(PRIORITY) / sizeof(int);
