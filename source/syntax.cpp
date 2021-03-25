#include "syntax.h"
std::vector<Lexem *> buildPoliz(
	std::vector<Lexem *> infix) {
        stack <Oper*> opstack;
        vector<Lexem *> poliz;
        for (int i = 0; i < infix.size(); i++) {
            string lexem_class = infix[i]->getClass();
            if (lexem_class == "Number") {
                poliz.push_back(infix[i]);
            } else if (lexem_class == "Oper") {
                        OPERATOR type = ((Oper*)infix[i])->getType();
                        if (type == LBRACKET) {
                            opstack.push((Oper*)infix[i]);
                        } else if (type == RBRACKET) {
                                    while (opstack.top()->getType() != LBRACKET) {
                                        poliz.push_back(opstack.top());
                                        opstack.pop();
                                    }
                                    opstack.pop();
                                } else {
                                    int priority = ((Oper*)infix[i])->getPriority();
                                    while (!opstack.empty() && opstack.top()->getPriority() >= priority) {
                                        poliz.push_back(opstack.top());
                                        opstack.pop();
                                    }
                                    opstack.push((Oper*)infix[i]);
                                }
                    } else if (lexem_class == "Variable") {
                                poliz.push_back(infix[i]);
                            }

        }
        while (!opstack.empty()) {
            poliz.push_back(opstack.top());
            opstack.pop();
        }
        return poliz;
}
