#include "syntax.h"
std::vector<Lexem *> buildPoliz(const std::vector<Lexem *> &infix) {
    stack <Oper*> opstack;
    vector<Lexem *> poliz;
    for (const auto lexem: infix) {
        if (lexem == nullptr) {
            continue;
        }
        if (lexem->getClass() == VARIABLE) {
            Variable *lexemvar = (Variable*)lexem;
            if (lexemvar->inLabelTable()) {
                joinGotoAndLabel(lexemvar, opstack);
            } else {
                poliz.push_back(lexem);
            }
        } else if (lexem->getClass() == NUMBER) {
                    poliz.push_back(lexem);
                } else if (lexem->getClass() == OPER) {
                            OPERATOR type = ((Oper*)lexem)->getType();
                            if (type == ENDIF) 
                                continue;
                            if (type == LBRACKET) {
                                opstack.push((Oper*)lexem);
                            } else if (type == RBRACKET) {
                                        while (opstack.top()->getType() != LBRACKET) {
                                            poliz.push_back(opstack.top());
                                            opstack.pop();
                                        }
                                        opstack.pop();
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
