#include "const.h"
int PRIORITY[] = {
    -1, -1,
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
    "(", ")",
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

