#include "lexical.h"
#include "semantic.h"
#include "syntax.h"
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
