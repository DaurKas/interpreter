#include "syntax.h"
std::vector<Lexem *> buildPoliz(const std::vector<Lexem *> &infix, vector<Lexem*> &toDelete) {
    stack <Oper*> opstack;
    vector<Lexem *> poliz;
    for (const auto lexem: infix) {
        if (lexem == nullptr) {
            continue;
        }
        if (lexem->getClass() == VARIABLE || lexem->getClass() == POINTER) {
            Variable *lexemvar = (Variable*)lexem;
            if (lexemvar->inLabelTable()) {
                joinGotoAndLabel(lexemvar, opstack);
            } else {
                poliz.push_back(lexemvar);
            }
        } else if (lexem->getClass() == NUMBER) {
                    poliz.push_back((Number*)lexem);
        } else if (lexem->getClass() == OPER) {
                    OPERATOR type = ((Oper*)lexem)->getType();
                    if (type == ENDIF || type == THEN) 
                        continue;
                    if (type == LBRACKET) {
                        opstack.push((Oper*)lexem);
                    } else if (type == RBRACKET) {
                        while (opstack.top()->getType() != LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.pop();
                    } else if (type == ARR_LBRACKET || type == ARG_LBRACKET) {
                       opstack.push((Oper*)lexem); 
                    } else if (type == ARR_RBRACKET) {
                        while (opstack.top()->getType() != ARR_LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.pop();
                        Oper *plus = new Oper(PLUS);
                        Oper *deref = new Oper(DEREF);
                        poliz.push_back(plus);
                        poliz.push_back(deref);
                        toDelete.push_back(plus);
                        toDelete.push_back(deref);
                    } else if (type == ARG_RBRACKET) {
                        while (opstack.top()->getType() != ARR_LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.pop();
                        Oper *argend = new Oper(ENDARG);
                        poliz.push_back(argend)'
                        toDelete.push_back(argend);
                    } else {
                        int priority = ((Oper*)lexem) -> getPriority();
                        while (!opstack.empty() && opstack.top()->getPriority() >= priority) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.push((Oper*)lexem);

                    }
        }
    }
    while (!opstack.empty()) {
        poliz.push_back(opstack.top());
        opstack.pop();
    }
    return poliz;
}
void joinGotoAndLabel(Variable *lexemvar, stack<Oper*> stack) {
    if (stack.top() -> getType() == GOTO) {
        Goto *lexemgoto = (Goto*)stack.top();
        lexemgoto->setRow(labels[lexemvar->getName()]);
    }
}
