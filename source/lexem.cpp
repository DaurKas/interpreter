#include "lexem.h"
#include "lexical.h"
Lexem::Lexem() { };
int Lexem::getValue() const {
    cout << "You should not see this message" << endl;
    return 0;
}
Lexem::~Lexem() {
}
LEXEM_TYPE Lexem::getClass() const {
    return LEXEM;
}

Number::Number(int n) {
    value = n;
}
int Number::getValue() const{
    return value;
}
LEXEM_TYPE Number::getClass() const {
    return NUMBER;
}

Variable::Variable(string _name) {
    name = _name;
}
int Variable::getValue() const {
    return value;
}
void Variable::setValue(int _value) {
    value = _value;
    cout << name << " CHANGING VALUE TO " << _value << endl;
}
string Variable::getName() {
    return name;
}
bool Variable::inLabelTable() {
    return labels.find(Variable::name) != labels.end(); 
}
LEXEM_TYPE Variable::getClass() const {
    return VARIABLE;
}
 
Oper::Oper(int op) {
    opertype = (OPERATOR)op;
}
OPERATOR Oper::getType() const {
    return opertype;
}
int Oper::getPriority() const {
    return PRIORITY[opertype]; 
}
int Oper::getValue (Lexem* left, Lexem* right) const {
    int a, b;
    /* if (left->getClass() == "Variable")
        a = ((Variable*)left)->getValue();
    else    
        a = ((Number*)left)->getValue();
    if (left->getClass() == "Variable")
        b = ((Variable*)right)->getValue();
    else
        b = ((Number*)right)->getValue();
    */
    a = left->getValue();
    b = right->getValue();
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
            if (left->getClass() == VARIABLE) {
                ((Variable*)left) -> setValue(b);
                return b;
            }
        default:
            break;
            
        }
    return 0;
    }
LEXEM_TYPE Oper::getClass() const {
    return OPER;
}
Goto::Goto(int row, int op): Oper::Oper(op) {
    Goto::row = row;
}
void Goto::setRow(string label) {
   Goto::row = labels[label]; 
}
int Goto::getRow() {
    return row;
}

