#include "lexem.h"
Lexem::Lexem() { };
virtual const string Lexem::getClass() const {
    return "Lexem";
}
Number::Number(int n) {
    value = n;
}
virtual int Number::getValue() const{
    return value;
}
virtual const string Number::getClass() const {
    return "Number";
}

Variable::Variable(string _name) {
    name = _name;
}
virtual int Variable::getValue() {
    return value;
}
void Variable::setValue(int _value) {
    value = _value;
    cout << name << " CHANGING VALUE TO " << _value << endl;
}
virtual const string Variable::getClass() const {
    return "Variable";
}
 
Oper::Oper(int op) {
    opertype = (OPERATOR)op;
}
virtual OPERATOR Oper::getType() const {
    return opertype;
}
int Oper::getPriority() const {
    return PRIORITY[opertype]; 
}
virtual int Oper::getValue (Lexem* left, Lexem* right) const {
    int a, b;
    if (left->getClass() == "Variable")
        a = ((Variable*)left)->getValue();
    else    
        a = ((Number*)left)->getValue();
    if (left->getClass() == "Variable")
        b = ((Variable*)right)->getValue();
    else
        b = ((Number*)right)->getValue();
    switch(opertype) {
        case PLUS:
            return a + b;
        case MINUS:
            return a - b;
        case MULTIPLY:
            return a * b;
        case OR:
            return (int) a || b;
        case AND:
            return (int) a && b;
        case BITOR:
            return a | b;
        case XOR:
            return a ^ b;
        case BITAND:
            return a & b;
        case EQ:
            return (int) a == b;
        case NEQ:
            return (int) a != b;
        case LEQ:
            return (int) a <= b;
        case LT:
            return (int) a < b;
        case GEQ:
            return (int) a >= b;
        case GT:
            return (int) a > b;
        case SHL:
            return a << b;
        case SHR:
            return a >> b;
        case DIV:
            return a / b;
        case MOD:
            return a % b;
        case ASSIGN:                        
            if (left->getClass() == "Variable") {
                ((Variable*)left) -> setValue(b);
                return b;
            }     
            
        }
    return 0;
    }
virtual const string Oper::getClass() const {
    return "Oper";
}
    
};
bool isDeclared(string name) {
    return variables.count(name) > 0;
}
