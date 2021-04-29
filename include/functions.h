#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//#include "lexem.h"
//#include "lexiacl.h"
#include "lexem.h"
class Function: public Lexem {
public:
    Function(string name);
    ~Function();
    Lexem *getArg(int N);
    Number *getValue();
    Space getSpace();
    void pushPoliz(vector<Lexem*> line);
    void pushToDelete(Lexem* lexem);
    void pushArg(Variable* var);
    void pushEval(Number *num);
    void pushNewArg(Lexem* arg);
    void addToSpace(Variable *var);
    void initArgs(vector<Lexem*> _args);
    void setRow(int row);
    void setEnd(int row);
    void loadVars();
    void saveVars();
    int getRow();
    int getEnd();
    bool isDeclared(string name);
    vector<Variable*> getArgs();
    vector<Lexem*> getDelete();
    Lexem* getVar(string name);
    LEXEM_TYPE getClass() const;
private:
    string name;
    Space space;
    vector<Variable*> args;
    stack<int> varStack;
    stack<Number*> evalStack;
    stack<Lexem*> argStack;
    vector<Lexem*> toDelete;
    int argc;
    int beginRow;
    int endRow;
    vector<vector<Lexem*>> poliz;
};  
extern map<string, Function*> functions;
void initFunctions(vector<vector<Lexem*>> &infixlines);
void freeFunctions();
void freeAll(vector<vector<Lexem*>> &infixlines);
#endif
