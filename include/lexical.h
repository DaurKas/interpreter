#ifndef LEXICAL_H
#define LEXICAL_H
#include "lexem.h"
#include "functions.h"
bool isDeclared(string name, Space localSpace);
bool isAbc(char ch);
Lexem* get_oper(string codeline, int &pos);
Lexem* get_number(string codeline, int &pos);
Lexem* get_variable(string codeline, int &pos);
Function *initFunction(string codeline, Space &localSpace);
vector<Lexem*> parseLexem(std::string codeline, vector<Lexem*> &toDelete, Space &currentSpace);
void initLabels(vector<Lexem*> &infix, int row);
void initJumps(vector<vector<Lexem*>> &infixLines);
#endif
