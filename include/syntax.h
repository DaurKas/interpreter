#ifndef SYNTAX_H
#define SYNTAX_H
#include "functions.h"
std::vector<Lexem *> buildPoliz(const std::vector<Lexem *> &infix, Function *func);
void joinGotoAndLabel(Variable *lexemvar, stack<Oper*> stack);
void buildFunctions(vector<vector<Lexem*>> &infixlines);
#endif
