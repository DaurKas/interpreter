#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>
using namespace std;
enum OPERATOR {
    LBRACKET, RBRACKET,
    ASSIGN,
    OR,
    AND,
    BITOR,
    XOR,
    BITAND,
    EQ, NEQ,
    LEQ, LT,
    GEQ, GT,
    SHL, SHR,
    PLUS, MINUS,
    MULTIPLY, DIV, MOD
};
int PRIORITY[] = {
    -1, -1,
    0,
    1,
    3,
    4,
    5,
    6, 6,
    7, 7,
    7, 7,
    8, 8,
    9, 9,
    10, 10, 10
};
string OPERTEXT[] = {
    "(", ")",
    ":=",
    "or",
    "and",
    "|",
    "^",
    "&",
    "==", "!=",
    "<=", "<",
    ">=", ">",
    "shl", "shr",
    "+", "-",
    "*", "/", "%"
};
int OP_NUM = sizeof(PRIORITY) / sizeof(int);
class Lexem {
public:
    Lexem() { };
    virtual const string getClass() const {
        return "Lexem";
    }
};
class Number: public Lexem {
    int value;
public:
    Number(int n) {
        value = n;
    }
    virtual int getValue() const{
        return value;
    }
    virtual const string getClass() const {
        return "Number";
    }
};
class Variable: public Lexem {
    string name;
    int value;
public:
    Variable(string _name) {
        name = _name;
    }
    virtual int getValue() {
        return value;
    }
    void setValue(int _value) {
        value = _value;
        cout << name << " CHANGING VALUE TO " << _value << endl;
    }
    virtual const string getClass() const {
        return "Variable";
    }
};
 
class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper(int op) {
        opertype = (OPERATOR)op;
    }
    virtual OPERATOR getType() const {
        return opertype;
    }
    int getPriority() const {
        return PRIORITY[opertype]; 
    }
    virtual int getValue (Lexem* left, Lexem* right) const {
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
    virtual const string getClass() const {
        return "Oper";
    }
    
};
map <string, Variable*> variables;
bool isDeclared(string name) {
    return variables.count(name) > 0;
}
bool isAbc(char ch) {
    bool c1 = (ch >= 'a' && ch <= 'z');
    bool c2 = (ch >= 'A' && ch <= 'Z');
    return c1 || c2;
}
Lexem* get_oper(string codeline, int &pos) {
    for (int op = 0; op < OP_NUM; op++) {
        string subcodeline = codeline.substr(pos, OPERTEXT[op].size());
        if (OPERTEXT[op] == subcodeline) {
            pos += OPERTEXT[op].size();
            return new Oper(op);
        }
    }
    return nullptr;
}
Lexem* get_number(string codeline, int &pos) {
    int num = 0;
    int begin = pos;
    int j = pos;
    int cnt = 0;
    for (; codeline[j] >= '0' && codeline[j] <= '9'; j++) {
        num = num * 10 + codeline[j] - '0';
        cnt++;
    }
    pos += cnt;
    if ((pos - begin) == 0) {
        return nullptr;
    }
    return new Number(num);
}
Lexem* get_variable(string codeline, int &pos) {
    int begin = pos;
    for (; isAbc(codeline[pos]); pos++) {
    }
    string subcode = codeline.substr(begin, pos - begin);
    if ((pos - begin) == 0)
        return nullptr;
    if (isDeclared(subcode)) {
        return variables[subcode];
    } else {
        Variable *new_var = new Variable(subcode);
        variables[subcode] = new_var;
        return new_var;
    }
}
vector<Lexem*> parseLexem(
	std::string codeline) {
        vector<Lexem *> infix;
        vector<string> lexems;
        string tmp = "";
        Lexem *lexem;
        for (int i = 0; i < codeline.size();) {
            if (codeline[i] == ' ' || codeline[i] == '\t') {
                i++;
                continue;
            }
            lexem = get_oper(codeline, i);
            if (lexem != nullptr) {
                 infix.push_back(lexem);
                 continue;
            }
            lexem = get_number(codeline, i);
            if (lexem != nullptr) {
                 infix.push_back(lexem);
                 continue;
            }
            lexem = get_variable(codeline, i);
            if (lexem != nullptr) {
                 infix.push_back(lexem);
                 continue;
            }
            i++;
        }
        return infix;
}

std::vector<Lexem *> buildPoliz(
	std::vector<Lexem *> infix) {
        stack <Oper*> opstack;
        vector<Lexem *> poliz;
        for (int i = 0; i < infix.size(); i++) {
            string lexem_class = infix[i]->getClass();
            if (lexem_class == "Number") {
                poliz.push_back(infix[i]);
            } else if (lexem_class == "Oper") {
                        OPERATOR type = ((Oper*)infix[i])->getType();
                        if (type == LBRACKET) {
                            opstack.push((Oper*)infix[i]);
                        } else if (type == RBRACKET) {
                                    while (opstack.top()->getType() != LBRACKET) {
                                        poliz.push_back(opstack.top());
                                        opstack.pop();
                                    }
                                    opstack.pop();
                                } else {
                                    int priority = ((Oper*)infix[i])->getPriority();
                                    while (!opstack.empty() && opstack.top()->getPriority() >= priority) {
                                        poliz.push_back(opstack.top());
                                        opstack.pop();
                                    }
                                    opstack.push((Oper*)infix[i]);
                                }
                    } else if (lexem_class == "Variable") {
                                poliz.push_back(infix[i]);
                            }

        }
        while (!opstack.empty()) {
            poliz.push_back(opstack.top());
            opstack.pop();
        }
        return poliz;
    }

int evaluatePoliz(
	std::vector<Lexem *> poliz) {
        stack <Lexem*> evalue;
        for (int i = 0; i < poliz.size(); i++) {
            //cout << poliz[i]->getClass() << " "  << endl;
            if (typeid(*(poliz[i])) == typeid(Number)) {
                evalue.push(((Number*)poliz[i]));
            } else if (typeid(*(poliz[i])) == typeid(Variable)) {\
                        evalue.push((Variable*)poliz[i]);
                    } else if (typeid(*(poliz[i])) == typeid(Oper)) {
                            OPERATOR type = ((Oper*)poliz[i])->getType();
                            Lexem *a, *b;
                            b = evalue.top();
                            evalue.pop();
                            a = evalue.top();
                            evalue.pop();
                            evalue.push(new Number(((Oper*)poliz[i])->getValue(a, b)));
                        }
        }
        return ((Number*)evalue.top())->getValue();
    }
void printVariables() {
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        cout << it->first << "___" << it->second->getValue() << endl;
    }
}
int main() {
	std::string codeline;
	std::vector<Lexem *> infix;
	std::vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix = parseLexem(codeline);
        if (infix.size() > 1) {
		    postfix = buildPoliz(infix);
		    value = evaluatePoliz(postfix);
		    std::cout << value << std::endl;
            //variables["x"]->setValue(10);
            //printVariables();
        }
	}
	return 0;
}
