#include "functions.h"
Function::Function(string name) {
    Function::name = name;
}
Function::~Function() {
    for (int i = 0; i < (int)toDelete.size(); i++) {
        if (toDelete[i] != nullptr) 
            delete toDelete[i];
    }
    for (int i = 0; i < (int)args.size(); i++) {
        delete args[i];
    }
}
void Function::initArgs(vector<Lexem*> _args) {
    for (int i = 0; i < (int) _args.size(); i++) {
        string argName = ((Variable*) _args[i])->getName();
        Variable *newArg = new Variable(argName);
        space.variables[argName] = newArg;

    }
}
bool Function::isDeclared(string name) {
    return space.variables.count(name) > 0;
}
vector<Variable*> Function::getArgs() {
    return args;
}
Space Function::getSpace() {
    return space;
}
Lexem* Function::getVar(string name) {
    return space.variables[name];
}
void Function::pushArg(Variable *var) {
    args.push_back(var);
}
void Function::pushNewArg(Lexem* arg) {
    argStack.push(arg);
}
void Function::addToSpace(Variable* var) {
    space.variables[var->getName()] = var;
}
void Function::pushToDelete(Lexem* lexem) {
    toDelete.push_back(lexem);
}
void Function::setRow(int row) {
    beginRow = row;
}
void Function::setEnd(int row) {
    endRow = row;
}
int Function::getRow() {
    return beginRow;
}
int Function::getEnd() {
    return endRow;
}
void Function::pushPoliz(vector<Lexem*> line) {
    poliz.push_back(line);
}
vector<Lexem*> Function::getDelete() {
    return toDelete;
}
map <string, Function*> functions;
LEXEM_TYPE Function::getClass() const {
    return FUNCTION;
}
void Function::saveVars() {
    for (auto it = space.variables.begin(); it != space.variables.end(); ++it) {
        varStack.push(it->second->getValue());
    }
}
void Function::loadVars() {
    for (auto it = space.variables.end(); it != space.variables.begin(); it--) {
        if (it != space.variables.end()) {
            it->second->setValue(varStack.top());
            varStack.pop();
        }
    }
}
void Function::pushEval(Number *num) {
    evalStack.push(num);
}
void initFunctions(vector<vector<Lexem*>> &infixlines) {
    Function *curFun = nullptr;
    int row = 0;
    for (auto &infix: infixlines) {
        if (infix[0]->getClass() == OPER) {
            if (((Oper*)infix[0])->getType() == INIT_FUNCTION) {
                Function *fun = (Function*)infix[1];
                curFun = fun;
                vector<Lexem*> toDelete = curFun->getDelete();
                fun->setRow(row);
                for (int i = 2; i < (int)infix.size(); i++) {
                    int argc = 0;
                    if (infix[i]->getClass() == VARIABLE) {
                        Variable *newVar = new Variable(((Variable*)infix[i])->getName());
                        vector<Variable*> args = fun->getArgs();
                        curFun->pushArg(newVar);
                        infix[i] = newVar;
                        curFun->addToSpace(newVar);
                        argc++;
                    }
                }
                row++;
                continue;
            } else if (((Oper*)infix[0])->getType() == ENDFUNCTION) {
                curFun->setEnd(row + 1);
            }
        }
        for (int i = 0; i < (int)infix.size(); i++) {
            if (infix[i]->getClass() == VARIABLE) {
                string name = ((Variable*)infix[i])->getName();
                if (!curFun->isDeclared(name)) {
                    Variable *newVar = new Variable(((Variable*)infix[i])->getName());
                    curFun->pushToDelete(newVar);
                    infix[i] = newVar;
                    curFun->addToSpace(newVar);
                } else {
                    infix[i] = curFun->getVar(name);
                }
            } else if (infix[i]->getClass() == POINTER) {
                string name = ((Pointer*)infix[i])->getName();
                if (!curFun->isDeclared(name)) {
                    Pointer *newVar = new Pointer(((Pointer*)infix[i])->getName());
                    curFun->pushToDelete(newVar);
                    infix[i] = newVar;
                    curFun->addToSpace(newVar);
                } else {
                    infix[i] = curFun->getVar(name);
                }
            } else {
                continue;
            }
        }
        row++;
    }
}
void freeFunctions() {
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        delete it->second;
    }
}
void freeAll(vector<vector<Lexem*>> &infixlines) {
    for (const auto &infix: infixlines) {
        for (int i = 0; i < (int)infix.size(); i++) {
            if (infix[i] != nullptr) {
                if(infix[i]->getClass() == NUMBER 
                    || infix[i]->getClass() == OPER) {
                    delete infix[i];
                }
            }
        }
    }
    freeFunctions();
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        delete it->second;
    }   
}
