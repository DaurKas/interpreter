#include "lexical.h"
map <string, int> labels;
map <string, Variable*> variables;
bool isDeclared(string name) {
    return variables.count(name) > 0;
}
bool isAbc(char ch) {
    bool isLow = (ch >= 'a' && ch <= 'z');
    bool isUpper = (ch >= 'A' && ch <= 'Z');
    return isLow || isUpper;
}
bool isJump(OPERATOR op) {
    bool isIf = op == IF || op == ELSE;
    bool isWhile = op == WHILE || op == ENDWHILE;
    bool isGoto = op == GOTO;
    return isIf || isWhile || isGoto;
}
Lexem* get_oper(string codeline, int &pos) {
    for (int op = 0; op < OP_NUM; op++) {
        string subcodeline = codeline.substr(pos, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            pos += OPERTEXT[op].size();
            if (isJump((OPERATOR)op)) 
                return new Goto(op);
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
void initLabels(vector<Lexem*> &infix, int row) {
    for (int i = 1; i < (int)infix.size(); i++) {
        if ((infix[i - 1]->getClass() == VARIABLE) && (infix[i]->getClass() == OPER)) {
            Variable *lexemvar = (Variable*)infix[i - 1];
            Oper *lexemop = (Oper*)infix[i];
            if (lexemop->getType() == COLON) {
                labels[lexemvar->getName()] = row;
                infix[i - 1] = nullptr;
                infix[i] = nullptr;
                //infix.erase(infix.begin() + i - 1);
                //infix.erase(infix.begin() + i);
                delete infix[i - 1];
                delete infix[i];
                i++;
            }
        }
    }
}
void initJumps(vector<vector<Lexem*>> &infixLines) {
    stack <Goto*> stackIf;
    for (int row = 0; row < (int)infixLines.size(); row++) {
        for (int i = 0; i < (int)infixLines[row].size(); i++) {
            if (infixLines[row][i] == nullptr)
                continue;
            if (infixLines[row][i]->getClass() == OPER) {
                Oper *lexemop = (Oper*) infixLines[row][i];
                if (lexemop->getType() == IF) {
                    stackIf.push((Goto*)lexemop);
                }
                if (lexemop->getType() == ELSE) {
                    stackIf.top()->setRow(row + 1);
                    stackIf.pop();
                    stackIf.push((Goto*)lexemop);
                }
                if (lexemop->getType() == ENDIF) {
                    stackIf.top()->setRow(row + 1);
                    stackIf.pop();
                }
            }
        }
    
    }
    stack <Goto*> stackWhile;
    for (int row = 0; row < (int)infixLines.size(); row++) {
        for (int i = 0; i < (int)infixLines[row].size(); i++) {
            if (infixLines[row][i] == nullptr)
                continue;
            if (infixLines[row][i]->getClass() == OPER) {
                Oper *lexemop = (Oper*) infixLines[row][i];
                if (lexemop->getType() == WHILE) {
                    Goto *lexemgoto = (Goto*) lexemop;
                    lexemgoto->setRow(row);
                    stackWhile.push(lexemgoto);
                }
                if (lexemop->getType() == ENDWHILE) {
                    Goto *lexemgoto = (Goto*) lexemop;
                    lexemgoto->setRow(stackWhile.top()->getRow());
                    stackWhile.top()->setRow(row + 1);
                    stackWhile.pop();
                }
            }
        }
    
    }
}

