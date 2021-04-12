#include "lexical.h"
#include "semantic.h"
#include "syntax.h"
#include <fstream>
void printVariables() {
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        cout << it->first << "___" << it->second->getValue() << endl;
    }
}
int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "No argument" << endl;
        return 0;
    }
    ifstream fin(argv[1]);
	std::string codeline;
    vector<vector<Lexem*>> infixlines, postfixlines;
    vector<Lexem*> toDelete;
    while (getline(fin, codeline)) {
        cout << codeline << endl;
        infixlines.push_back(parseLexem(codeline, toDelete));
    }
    for (int row = 0; row < (int)infixlines.size(); row++) {
        initLabels(infixlines[row], row);
    }
    initJumps(infixlines);
    for (const auto &infix: infixlines) {
        postfixlines.push_back(buildPoliz(infix, toDelete));
    }
    int row = 0;
    while (row >= 0 && row < (int)postfixlines.size()) {
        row = evaluatePoliz(postfixlines[row], row);
    }
    printVariables();
    for (const auto &infix: infixlines) {
        for (int i = 0; i < (int)infix.size(); i++) {
            if (infix[i] != nullptr && infix[i]->getClass() != VARIABLE && infix[i]->getClass() != POINTER) {
                delete infix[i];
            }
        }
    }
    for (auto it = variables.begin(); it != variables.end(); ++it) {
            delete it->second;
    }
    for (int i = 0; i < (int)toDelete.size(); i++) {
        delete toDelete[i];
    }
    return 0;
}
