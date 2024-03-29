#ifndef LEXICAL_H
#define LEXICAL_H
#include "functions.h"
bool isDeclared(string name);
bool isDeclaredFunc(string name);
bool isAbc(char ch);
Lexem* get_oper(string codeline, int &pos);
Lexem* get_number(string codeline, int &pos);
Lexem* get_variable(string codeline, int &pos);
Lexem* getFunction(string codeline, int &pos);
vector<Lexem*> parseLexem(std::string codeline, vector<Lexem*> &toDelete);
void initLabels(vector<Lexem*> &infix, int row);
void initJumps(vector<vector<Lexem*>> &infixLines);
#endif
