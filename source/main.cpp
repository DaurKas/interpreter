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
	//std::vector<Lexem *> infix;
	//std::vector<Lexem *> postfix;
    vector<vector<Lexem*>> infixlines, postfixlines;
    while (getline(cin, codeline)) {
        infixlines.push_back(parseLexem(codeline));
    }
    for (int row = 0; row < (int)infixlines.size(); row++) {
        initLabels(infixlines[row], row);
    }
    initJumps(infixlines);
    for (const auto &infix: infixlines) {
        postfixlines.push_back(buildPoliz(infix));
    }
    int row = 0;
    while (row >= 0 && row < (int)postfixlines.size()) {
        row = evaluatePoliz(postfixlines[row], row);
    }
    printVariables();
    for (const auto &infix: infixlines) {
        for (int i = 0; i < (int)infix.size(); i++) {
            //cout << "DELETE " << infix[i]->getClass() << endl;
            if (infix[i] != nullptr) {
                delete infix[i];
            }
        }
    }
    /*for (const auto &postfix: postfixlines) {
        for (int i = 0; i < (int)postfix.size(); i++) {
            delete postfix[i];
        }
    }*/
    return 0;
}
