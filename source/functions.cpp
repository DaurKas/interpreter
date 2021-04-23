#include "functions.h"
Function::Function(string name, int start) {
    Function::name = name;
    beginRow = start;
}
void Function::initArgs(vector<Lexem*> _args) {
    for (int i = 0; i < (int) _args.size(); i++) {
        string argName = ((Variable*) _args)->getName();
        Variable *newArg = new Variable(argName);
        space.variables[argName] = newArg;

    }
}
map <string, Function*> functions;
void Function::buildFunction(vector<vector<Lexem*>> &infixLines) {
    for (int i = beginRow; ; i++) {
        if (infixLines[i][0]->getClass() == OPER 
            && ((Oper*)infixLines[i][0])->getType() == ENDFUNCTION) {
            endRow = i;
            break;
        }
    }
    for (int i = beginRow; i < endRow; i++) {
        initLabels(infixLines[i], i);
    }

    for (int i = beginRow; i < endRow; i++) {
        poliz.push_back(buildPoliz(infixLines[i], toDelete));
    }
}
Number *getValue(vector<Lexem*> arguments) {
    int row = 0;
    vector<int> currentArgs;
    for (int i = 0; i < (int)args.size(); i++) {
        args[i].setValue(arguments.getValue());
        currentArgs.push_back(arguments.getValue());
    }
    while (row >= 0 && row < (int)poliz.size()) {
        row = evaluatePoliz(poliz[row], row, *this);
    }
    Number *ret = valStack.top();
    valStack.pop();
    return ret;
}
