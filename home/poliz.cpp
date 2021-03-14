#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
enum OPERATOR {
    LBRACKET, RBRACKET,
    PLUS, MINUS,
    MULTIPLY
};
int PRIORITY[] = {
    -1, -1,
    0, 0,
    1
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
    int getValue() const{
        return value;
    }
    virtual const string getClass() const {
        return "Number";
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
    }
    virtual OPERATOR getType() const {
        return opertype;
    }
    int getPriority() const {
        return PRIORITY[opertype]; 
    }
    int getValue (const Number& left, const Number& right) const {
        int a = left.getValue();
        int b = right.getValue();
        if (opertype == PLUS) 
            return a + b;
        else if (opertype == MINUS) 
                return a - b;
             else if (opertype == MULTIPLY) 
                    return a * b;
        return 0;
    }
    virtual const string getClass() const {
        return "Oper";
    }
    
};

vector<Lexem*> parseLexem(
	std::string codeline) {
        vector<Lexem *> infix;
        int num = 0;
        for (int i = 0; i < codeline.size(); i++) {
           if (codeline[i] == ' ' || codeline[i] == '\t') {

           } else if (codeline[i] >= '0' && codeline[i] <= '9') {
                  num = num * 10 + codeline[i] - '0';
                } else {
                    if (num != 0) {
                        infix.push_back(new Number(num));
                        num = 0;
                    }
                    infix.push_back(new Oper(codeline[i]));
                }
        }
        if (num != 0) {
            infix.push_back(new Number(num));
        }
        return infix;
    }

std::vector<Lexem *> buildPoliz(
	std::vector<Lexem *> infix) {
        stack <Oper*> opstack;
        vector<Lexem *> poliz;
        for (int i = 0; i < infix.size(); i++) {
            if (infix[i]->getClass() == "Number") {
                poliz.push_back(infix[i]);
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
        stack <int> evalue;
        for (int i = 0; i < poliz.size(); i++) {
            if (typeid(*(poliz[i])) == typeid(Number)) {
                evalue.push(((Number*)poliz[i])->getValue());
            } else if (typeid(*(poliz[i])) == typeid(Oper)) {
                        OPERATOR type = ((Oper*)poliz[i])->getType();
                        int a, b;
                        b = evalue.top();
                        evalue.pop();
                        a = evalue.top();
                        evalue.pop();
                        evalue.push(((Oper*)poliz[i])->getValue(a, b));
                    }
        }
        return evalue.top();
    }

int main() {
	std::string codeline;
	std::vector<Lexem *> infix;
	std::vector<Lexem *> postfix;
	int value;

	while (std::getline(std::cin, codeline)) {
		infix = parseLexem(codeline);
		postfix = buildPoliz(infix);
		value = evaluatePoliz(postfix);
		std::cout << value << std::endl;
	}
	return 0;
}
