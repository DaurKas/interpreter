#ifndef LEXEM_H
#define LEXEM_H
#include "const.h"
class Lexem {
public:
    Lexem();
    virtual LEXEM_TYPE getClass() const;
    virtual int getValue() const;
    virtual ~Lexem();
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
    Variable();
    int getValue() const;
    void setValue(int _value);
    string getName();
    bool inLabelTable();
    LEXEM_TYPE getClass() const;
};
 
class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper(int op);
    virtual OPERATOR getType() const;
    int getPriority() const;
    Lexem *getRes (Lexem* left, Lexem* right) const;
    LEXEM_TYPE getClass() const;
    
};

class Goto: public Oper {
    int row;
public:
    enum { UNDEFINED = -INT32_MAX };
    Goto(int op);
    void setRow(int row);
    int getRow();
};

class Pointer: public Variable {
    Variable **ptr;
    int pos;
    int size;
public:
    Pointer(string name);
    void setPtr(Variable *var_ptr);
    void allocate(int size);
    LEXEM_TYPE getClass() const;
    int getValue() const;
    Variable *getPtr() const;
    void setValue(int val);
    void setPos(int pos);
    void deletePtr();
    int getSize();
    int getPos();
    ~Pointer();
};
struct Space {
    map<string, Variable*> variables;
    map<string, int> labels;
    stack<Lexem*> evalue;
};
extern map<string, Variable*> variables;
extern map<string, int> labels;
#endif
