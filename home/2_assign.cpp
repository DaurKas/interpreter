#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <map>
using namespace std;
enum OPERATOR {
    LBRACKET, RBRACKET,
    ASSIGN,
    PLUS, MINUS,
    MULTIPLY
};
int PRIORITY[] = {
    -1, -1,
    0,
    1, 1,
    2
};
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
    Oper(char ch) {
        if (ch == '(')
            opertype = LBRACKET;
        if (ch == ')')
            opertype = RBRACKET;
        if (ch == '+') 
            opertype = PLUS;
        if (ch == '-')
            opertype = MINUS;
        if (ch == '*')
            opertype = MULTIPLY;
        if (ch == '=')
            opertype = ASSIGN;
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
        if (opertype == PLUS) 
            return a + b;
        else if (opertype == MINUS) 
                return a - b;
             else if (opertype == MULTIPLY) 
                    return a * b;
                else if (opertype == ASSIGN) {
                        if (left->getClass() == "Variable") {
                            ((Variable*)left) -> setValue(b);
                            cout << "HERE >>>>>>>> " << b << " <<<<<<<HERE" << endl;
                            cout << "_____ " << ((Variable*)left)->getValue() << " ________" << endl;
                            return b;
                        }
                    }
        return 0;
    }
    virtual const string getClass() const {
        return "Oper";
    }
    
};
   bool isOper(char ch) {
    bool c1 = (ch == '+');
    bool c2 = ch == '-';
    bool c3 = ch == '/';
    bool c4 = ch == '*';
    bool c5 = ch == '=';
    return c1 || c2 || c3 || c4 || c5;
}
map <string, Variable*> variables;
bool isDeclared(string name) {
    return variables.count(name) > 0;
}
vector<Lexem*> parseLexem(
	std::string codeline) {
        vector<Lexem *> infix;
        vector<string> lexems;
        string tmp = "";
        for (int i = 0; i < codeline.size(); i++) {
           if (codeline[i] != ' ' && codeline[i] != '\t') { 
                tmp += codeline[i];
           } else {
                if (tmp.size() > 0) {
                    cout << tmp << endl;
                    lexems.push_back(tmp);
                    tmp = "";
                }
           }
        }
        cout << tmp << endl;
        lexems.push_back(tmp);
        for (int i = 0; i < lexems.size(); i++) {
            if (lexems[i][0] >= '0' && lexems[i][0] <= '9') {
                int num = 0;
                for (int j = 0; j < lexems[i].size(); j++) {
                    num = num * 10 + lexems[i][j] - '0';
                }
                infix.push_back(new Number(num));
            } else 
                if (isOper(lexems[i][0])) {
                    infix.push_back(new Oper(lexems[i][0]));
                } else {
                    if (isDeclared(lexems[i])) {
                        infix.push_back(variables[lexems[i]]);
                    } else {
                        Variable *new_var = new Variable(lexems[i]);
                        infix.push_back(new_var);
                        variables[lexems[i]] = new_var;
                    }
                }
        }
        return infix;
}

std::vector<Lexem *> buildPoliz(
	std::vector<Lexem *> infix) {
        stack <Oper*> opstack;
        vector<Lexem *> poliz;
        for (int i = 0; i < infix.size(); i++) {
            cout << infix[i]->getClass() << endl;
            if (infix[i]->getClass() == "Number") {
                poliz.push_back(infix[i]);
                //cout << ((Number*)infix[i])->getValue() << endl;
            } else if (infix[i]->getClass() == "Oper") {
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
                    } else if (infix[i]->getClass() == "Variable") {
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
            cout << poliz[i]->getClass() << " "  << endl;
            if (typeid(*(poliz[i])) == typeid(Number)) {
                evalue.push(((Number*)poliz[i]));
                cout << ((Number*)evalue.top())->getValue();
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
            printVariables();
        }
	}
	return 0;
}
