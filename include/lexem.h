#include "const.h"
class Lexem {
public:
    Lexem();
    virtual const string getClass() const;
};
class Number: public Lexem {
    int value;
public:
    Number(int n);
    virtual int getValue() const;
    virtual const string getClass() const;
};
class Variable: public Lexem {
    string name;
    int value;
public:
    Variable(string _name);
    virtual int getValue();
    void setValue(int _value); 
    virtual const string getClass() const;
};
 
class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper(int op);
    virtual OPERATOR getType() const;
    int getPriority() const;
    virtual int getValue (Lexem* left, Lexem* right) const;
    virtual const string getClass() const;
    
};
map <string, Variable*> variables;
