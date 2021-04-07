#include "semantic.h"
#include "lexem.h"
#include "lexical.h"
int evaluatePoliz(vector<Lexem *> &poliz, int row) {
    stack <Lexem*> evalue;
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
                                return lexemgoto->getRow();
                            }
                        }
            } else {
                    Lexem *a, *b;
                    b = evalue.top();
                    evalue.pop();
                    a = evalue.top();
                    evalue.pop();
                    evalue.push(new Number((lexemop)->getValue(a, b)));
                }
        } else if (lexem->getClass() == NUMBER) {
                    Number *lexemnum = (Number*)lexem;
                    evalue.push(lexemnum);
        } else if (lexem->getClass() == VARIABLE) {
                    Variable *lexemvar = (Variable*)lexem;
                    evalue.push(lexemvar);
        }
    }
    return row + 1;
}
