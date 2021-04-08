#include "semantic.h"
#include "lexem.h"
#include "lexical.h"
int evaluatePoliz(vector<Lexem *> &poliz, int row) {
    stack <Lexem*> evalue;
    vector <Lexem*> toDelete;
    /* if (poliz[0] == nullptr) {
        cout << "NULL" << endl;
        return 0;
    }*/
    for (const auto &lexem: poliz) {
        if (lexem == nullptr) {
            return 0;
        }
        if (lexem->getClass() == OPER) {
            Oper *lexemop = (Oper*)lexem;
            if (lexemop->getType() == GOTO || 
                lexemop->getType() == ELSE || 
                lexemop->getType() == ENDWHILE) {
                Goto *lexemgoto = (Goto*)lexemop;
                return lexemgoto->getRow();
            } else if (lexemop->getType() == IF || lexemop->getType() == WHILE) {
                        Goto *lexemgoto = (Goto*)lexemop;
                        if (evalue.top()->getClass() == NUMBER) {
                            int rvalue = evalue.top()->getValue();
                            evalue.pop();
                            if (!rvalue) {
                                for (const auto &lexem: toDelete) {
                                    delete lexem;
                                }
                                return lexemgoto->getRow();
                            }
                        }
            } else {
                    Lexem *a, *b;
                    b = evalue.top();
                    evalue.pop();
                    a = evalue.top();
                    evalue.pop();
                    Number *newnum = new Number((lexemop)->getValue(a, b));
                    evalue.push((Number*)newnum);
                    toDelete.push_back(newnum);
                }
        } else if (lexem->getClass() == NUMBER) {
                    Number *lexemnum = (Number*)lexem;
                    evalue.push(lexemnum);
        } else if (lexem->getClass() == VARIABLE) {
                    Variable *lexemvar = (Variable*)lexem;
                    evalue.push(lexemvar);
        }
    }
    for (const auto &lexem: toDelete) {
        delete lexem;
    }
    return row + 1;
}
