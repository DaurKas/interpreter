#ifndef SPACE_H
#define SPACE_H
#include <lexem.h>
struct Space {
    map<string, Variable*> variables;
    map<string, int> labels;
    stack<Lexem*> evalue;
}
#endif
