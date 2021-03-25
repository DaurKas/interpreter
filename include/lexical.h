#include "lexem.h"
bool isDeclared(string name);
bool isAbc(char ch);
Lexem* get_oper(string codeline, int &pos);
Lexem* get_number(string codeline, int &pos);
Lexem* get_variable(string codeline, int &pos);
vector<Lexem*> parseLexem(std::string codeline);