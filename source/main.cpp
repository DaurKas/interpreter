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
    vector<vector<Lexem*>> infixlines, postfixlines;
    while (getline(cin, codeline)) {
        cout << "TEST! " << endl;
        infixlines.push_back(parseLexem(codeline));
    }
    cout << "STAGE 2 BEGAN!" << endl;
    for (int row = 0; row < (int)infixlines.size(); ++row) {
        initLabels(infixlines[row], row);
    }
    cout << "STAGE 3 BEGAN" << endl;
    for (const auto &infix: infixlines) {
        postfixlines.push_back(buildPoliz(infix));
    }
    cout << "STAGE 4 BEGAN" << endl;
    int row = 0;
    while (row >= 0 && row < (int)postfixlines.size()) {
        cout << "MAIN ROW : " << row << endl;
        row = evaluatePoliz(postfixlines[row], row);
    }
    return 0;
	/* while (std::getline(std::cin, codeline)) {
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
    */
}
