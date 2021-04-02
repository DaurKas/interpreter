#ifndef SYNTAX_H
#define SYNTAX_H
#include "lexem.h"
std::vector<Lexem *> buildPoliz(const std::vector<Lexem *> &infix);
void joinGotoAndLabel(Variable *lexemvar, stack<Oper*> stack);
#endif
