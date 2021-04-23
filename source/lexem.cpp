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
Variable::Variable() {
    name = "test";
}
int Variable::getValue() const {
    return value;
}
void Variable::setValue(int _value) {
    value = _value;
}
string Variable::getName() {
    return name;
}
bool Variable::inLabelTable(Space localSpace) {
    return localSpace.labels.find(Variable::name) != labels.end(); 
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
Lexem* Oper::getRes (Lexem* left, Lexem* right) const {
    int a, b;
    if (left != nullptr) {
        a = left->getValue();
    }
    if (right->getClass() == POINTER) {
        b = (((Pointer*)right)->getValue());
    } else {
        b = right->getValue();
    }
    switch(opertype) {
        case SIZE: {
            Pointer *ptr = (Pointer*)left;
            ptr->allocate(b);
            return ptr;
        }
        case DEREF: {
            Pointer *ptr = (Pointer *)left;
            return ptr->getPtr();
        }
        case PRINT:
            cout << b << endl;
            return 0;
        case PLUS: {
            if (left->getClass() == POINTER) {
                Pointer *ptr = (Pointer*)left;
                ptr->setPos(b);
                return ptr;
            }
            return new Number(a + b);
        }
        case MINUS:
            return new Number(a - b);
        case MULTIPLY:
            return new Number(a * b);
        case OR:
            return new Number((int) a || b);
        case AND:
            return new Number((int) a && b);
        case BITOR:
            return new Number(a | b);
        case XOR:
            return new Number(a ^ b);
        case BITAND:
            return new Number(a & b);
        case EQ:
            return new Number((int) a == b);
        case NEQ:
            return new Number((int) a != b);
        case LEQ:
            return new Number((int) a <= b);
        case LT:
            return new Number((int) a < b);
        case GEQ:
            return new Number((int) a >= b);
        case GT:
            return new Number((int) a > b);
        case SHL:
            return new Number(a << b);
        case SHR:
            return new Number(a >> b);
        case DIV:
            return new Number(a / b);
        case MOD:
            return new Number(a % b);
        case ASSIGN:
            if (left->getClass() == POINTER) {
                (((Pointer*)left) ->getPtr()) -> setValue(b);
                return left;
            }
            if (left->getClass() == VARIABLE) {
                ((Variable*)left) -> setValue(b);
                return new Number(b);
            }
        default:
            break;
            
        }
    return new Number(0);
    }
LEXEM_TYPE Oper::getClass() const {
    return OPER;
}
Goto::Goto(int op) : Oper(op){
    Goto::row = UNDEFINED;
    //opertype = (OPERATOR)op;
}
void Goto::setRow(int row) {
   Goto::row = row;
}
int Goto::getRow() {
    return row;
}
Pointer::Pointer(string name): Variable(name) {
    ptr = nullptr;
    pos = 0;
    size = 0;
}
void Pointer::setPtr(Variable *var_ptr) {
    *ptr = var_ptr;
}
Variable* Pointer::getPtr() const{
    if (size > 0)
        return ptr[pos];
    return nullptr;
}
void Pointer::allocate(int size) {
    Pointer::size = size;
    ptr = new Variable*[size];
    for (int i = 0; i < size; i++) {
        string name = "el";
        ptr[i] = new Variable(name);
    }
}
int Pointer::getValue() const{
    if (ptr != nullptr) {
        return (*(ptr + pos))->getValue();
    }
    return 0;
}
void Pointer::setValue(int val) {
    (*(ptr))->setValue(val);
}
LEXEM_TYPE Pointer::getClass() const{
    return POINTER;
}
void Pointer::setPos(int pos) {
    Pointer::pos = pos;
}
void Pointer::deletePtr() {
    if (ptr != nullptr)
        delete ptr;
}
int Pointer::getSize() {
    return size;
}
int Pointer::getPos() {
    return pos;
}
Pointer::~Pointer() {
    if (ptr != nullptr) {
        for (int i = 0; i < size; i++) {
            delete ptr[i];
        }
        delete[] ptr;
    }
}
