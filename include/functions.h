#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "space.h"
#include "semantic.h"
//#include "lexiacl.h"
#include "syntax.h"
class Function: Lexem {
public:
    Function(string name, int startRow);
    Lexem *getArg(int N);
    Number *getValue(vector<Lexem*> arguments);
    Space getSpace();
    void pushArg(Variable* var);
    void buildFunction(vector<vector<Lexem*>> &infixLines);
    LEXEM_TYPE getClass() const;
private:
    string name;
    Space space;
    vector<Variable*> args;
    stack<Vector<int>> argStack;
    stack<Number*> valStack;
    vector<Lexem*> toDelete;
    int argc;
    int beginRow;
    int endRow;
    vector<vector<Lexem*>> poliz;
}
extern map<string, Function*> functions;
#endif
