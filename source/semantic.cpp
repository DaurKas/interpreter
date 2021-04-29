#include "semantic.h"
//#include "functions.h"
//#include "lexem.h"
//#include "lexical.h"
int evaluatePoliz(vector<Lexem *> &poliz, int row, Function *curFun) {
    stack <Lexem*> evalue;
    vector <Lexem*> toDelete;
    vector <Lexem*> args;
    stack <Function*> funStack;
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
                return lexemgoto->getRow() - curFun->getRow();
            } else if (lexemop->getType() == IF || lexemop->getType() == WHILE) {
                    Goto *lexemgoto = (Goto*)lexemop;
                    if (evalue.top()->getClass() == NUMBER) {
                        int rvalue = evalue.top()->getValue();
                        evalue.pop();
                        if (!rvalue) {
                            for (const auto &lexem: toDelete) {
                                delete lexem;
                            }
                            return lexemgoto->getRow() - curFun->getRow();
                        }
                    }
            } else if (lexemop->getType() == DEREF) {
                Pointer *a = (Pointer*)evalue.top();
                evalue.pop();
                if (a->getPtr() != nullptr) {
                    evalue.push(a->getPtr());
                } else { 
                    evalue.push(a);
                }
                
            } else if (lexemop->getType() == DELIM) {
                Lexem *arg = evalue.top();
                evalue.pop();
                funStack.top()->pushNewArg(arg);
            } else if (lexemop->getType() == ENDARGS) {
                Lexem *arg = evalue.top();
                evalue.pop();
                funStack.top()->pushNewArg(arg);
                Function *fun = (Function*)evalue.top();
                evalue.pop();
                curFun->saveVars();
                Number *ret = fun->getValue();
                curFun->loadVars();
                evalue.push(ret);
            } else if (lexemop->getType() == ENDFUNCTION) {
                Lexem *ret = evalue.top();
                Number *res = new Number(ret->getValue());
                curFun->pushEval(res);
                curFun->pushToDelete(res);
            } else {
                Lexem *a, *b;
                b = evalue.top();
                evalue.pop();
                a = evalue.top();
                evalue.pop();
                Lexem *res = (lexemop)->getRes(a, b);
                evalue.push(res);
                if (res != nullptr && res->getClass() != POINTER && res->getClass() != VARIABLE)
                    toDelete.push_back(res);
            }
        } else if (lexem->getClass() == NUMBER) {
            Number *lexemnum = (Number*)lexem;
            evalue.push(lexemnum);
        } else if (lexem->getClass() == VARIABLE || lexem->getClass() == POINTER) {
            evalue.push(lexem);
        } else if (lexem->getClass() == FUNCTION) {
            funStack.push((Function*)lexem);
            evalue.push(lexem);
        }
    }
    for (const auto &lexem: toDelete) {
        delete lexem;
    }
    return row + 1;
}
Number* Function::getValue() {
    for (int i = (int)args.size() - 1; i >= 0; i--) {
        args[i]->setValue((argStack.top())->getValue());
        argStack.pop();
    }
    int row = 0;
    while (row >= 0 && row < (int)poliz.size()) {
        row = evaluatePoliz(poliz[row], row, this);
    }
    Number *ret = evalStack.top();
    evalStack.pop();
    return ret;
}
