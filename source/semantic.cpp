#include "semantic.h"
int evaluatePoliz(
	std::vector<Lexem *> poliz) {
        stack <Lexem*> evalue;
        for (int i = 0; i < poliz.size(); i++) {
            //cout << poliz[i]->getClass() << " "  << endl;
            if (typeid(*(poliz[i])) == typeid(Number)) {
                evalue.push(((Number*)poliz[i]));
            } else if (typeid(*(poliz[i])) == typeid(Variable)) {\
                        evalue.push((Variable*)poliz[i]);
                    } else if (typeid(*(poliz[i])) == typeid(Oper)) {
                            OPERATOR type = ((Oper*)poliz[i])->getType();
                            Lexem *a, *b;
                            b = evalue.top();
                            evalue.pop();
                            a = evalue.top();
                            evalue.pop();
                            evalue.push(new Number(((Oper*)poliz[i])->getValue(a, b)));
                        }
        }
        return ((Number*)evalue.top())->getValue();
}
