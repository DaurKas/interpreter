#include "syntax.h"
std::vector<Lexem *> buildPoliz(const std::vector<Lexem *> &infix, Function *func) {
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
        } else if (lexem->getClass() == FUNCTION) {
            poliz.push_back((Function*)lexem);
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
                    } else if (type == ARR_LBRACKET) {
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
                        func->pushToDelete(plus);
                        func->pushToDelete(deref);
                    } else if (type == F_LBRACKET) {
                       opstack.push((Oper*)lexem); 
                    } else if (type == F_RBRACKET) {
                        while (opstack.top()->getType() != F_LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.pop();
                        Oper *endarg = new Oper(ENDARGS);
                        poliz.push_back(endarg);
                        func->pushToDelete(endarg);
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
void buildFunctions(vector<vector<Lexem*>> &infixlines) {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        int start = it->second->getRow();
        int end = it->second->getEnd();
        for (int i = start + 1; i < end; i++) {
           it->second->pushPoliz(buildPoliz(infixlines[i], it->second)); 
        }
    }
}
