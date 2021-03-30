#ifndef LEXEM_H
#define LEXEM_H
#include "const.h"
class Lexem {
public:
    Lexem();
    virtual LEXEM_TYPE getClass() const;
    virtual int getValue() const;
};
class Number: public Lexem {
    int value;
public:
    Number(int n);
    virtual int getValue() const;
    LEXEM_TYPE getClass() const;
};
class Variable: public Lexem {
    string name;
    int value;
public:
    Variable(string _name);
    int getValue() const;
    void setValue(int _value); 
    LEXEM_TYPE getClass() const;
};
 
class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper(int op);
    virtual OPERATOR getType() const;
    int getPriority() const;
    int getValue (Lexem* left, Lexem* right) const;
    LEXEM_TYPE getClass() const;
    
};
extern map<string, Variable*> variables;
#endif
