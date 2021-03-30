#include "lexical.h"

map <string, Variable*> variables;
bool isDeclared(string name) {
    return variables.count(name) > 0;
}
bool isAbc(char ch) {
    bool isLow = (ch >= 'a' && ch <= 'z');
    bool isUpper = (ch >= 'A' && ch <= 'Z');
    return isLow || isUpper;
}
Lexem* get_oper(string codeline, int &pos) {
    for (int op = 0; op < OP_NUM; op++) {
        string subcodeline = codeline.substr(pos, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            pos += OPERTEXT[op].size();
            return new Oper(op);
        }
    }
    return nullptr;
}
Lexem* get_number(string codeline, int &pos) {
    int num = 0;
    int begin = pos;
    int j = pos;
    int cnt = 0;
    for (; codeline[j] >= '0' && codeline[j] <= '9'; j++) {
        num = num * 10 + codeline[j] - '0';
        cnt++;
    }
    pos += cnt;
    if ((pos - begin) == 0) {
        return nullptr;
    }
    return new Number(num);
}
Lexem* get_variable(string codeline, int &pos) {
    int begin = pos;
    for (; isAbc(codeline[pos]); pos++) {
    }
    string subcode = codeline.substr(begin, pos - begin);
    if ((pos - begin) == 0)
        return nullptr;
    if (isDeclared(subcode)) {
        return variables[subcode];
    } else {
        Variable *new_var = new Variable(subcode);
        variables[subcode] = new_var;
        return new_var;
    }
}
vector<Lexem*> parseLexem(
	std::string codeline) {
        vector<Lexem *> infix;
        vector<string> lexems;
        string tmp = "";
        Lexem *lexem;
        for (int i = 0; i < (int)codeline.size();) {
            if (codeline[i] == ' ' || codeline[i] == '\t') {
                i++;
                continue;
            }
            lexem = get_oper(codeline, i);
            if (lexem != nullptr) {
                 infix.push_back(lexem);
                 continue;
            }
            lexem = get_number(codeline, i);
            if (lexem != nullptr) {
                 infix.push_back(lexem);
                 continue;
            }
            lexem = get_variable(codeline, i);
            if (lexem != nullptr) {
                 infix.push_back(lexem);
                 continue;
            }
            i++;
        }
        return infix;
}
