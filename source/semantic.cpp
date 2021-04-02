#include "semantic.h"
#include "lexem.h"
#include "lexical.h"
int evaluatePoliz(std::vector<Lexem *> &poliz, int row) {
    stack <Lexem*> evalue;
    if (poliz[0] == nullptr) {
        cout << "NULL" << endl;
        return 0;
    }
    for (const auto &lexem: poliz) {
        if (lexem == nullptr) {
            cout << "NULLL " << endl;
            return 0;
        }
        cout << "CLASS : " << lexem->getClass() << endl;
        if (lexem->getClass() == OPER) {
            Oper *lexemop = (Oper*)lexem;
            if (lexemop->getType() == GOTO) {
                cout << "GOTO CASE" << endl;
                Goto *lexemgoto = (Goto*)lexemop;
                return lexemgoto->getRow();
            } else {
                cout << "OPER PUSH CASE" << endl;
                Lexem *a, *b;
                b = evalue.top();
                evalue.pop();
                a = evalue.top();
                evalue.pop();
                evalue.push(new Number((lexemop)->getValue(a, b)));
            }
        } else if (lexem->getClass() == NUMBER) {
                    cout << "PUSHING NUM" << endl;
                    Number *lexemnum = (Number*)lexem;
                    evalue.push(lexemnum);
                } else if (lexem->getClass() == VARIABLE) {
                            cout << "PUSHING VARIABLE" << endl;
                            Variable *lexemvar = (Variable*)lexem;
                            evalue.push(lexemvar);
                        }
    }
    cout << "ROW:: " << row << endl;
    return row + 1;

   /* for (int i = 0; i < (int)poliz.size(); i++) {
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
    */
}
