#include "semantic.h"
#include "lexem.h"
#include "lexical.h"
int evaluatePoliz(std::vector<Lexem *> poliz) {
    stack <Lexem*> evalue;
    for (int i = 0; i < (int)poliz.size(); i++) {
        if (typeid(*(poliz[i])) == typeid(Number)) {
            evalue.push(((Number*)poliz[i]));
        } else if (typeid(*(poliz[i])) == typeid(Variable)) {
                evalue.push((Variable*)poliz[i]);
                } else if (typeid(*(poliz[i])) == typeid(Oper)) {
                        Lexem *a, *b;
                        b = evalue.top();
                        evalue.pop();
                        a = evalue.top();
                        evalue.pop();
                        evalue.push(new Number(((Oper*)poliz[i])->getValue(a, b)));
                    }
        }
    return (evalue.top())->getValue();
}
