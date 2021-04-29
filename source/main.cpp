#include "lexical.h"
#include "semantic.h"
#include "syntax.h"
#include <fstream>
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
    initFunctions(infixlines);
    for (int row = 0; row < (int)infixlines.size(); row++) {
        initLabels(infixlines[row], row);
    }
    initJumps(infixlines);
    buildFunctions(infixlines);
    Function *main = functions["main"];
    Number *arg = new Number(0);
    main->pushNewArg(arg);
    Number *res = main->getValue();
    cout << res->getValue();
    delete arg;
    freeAll(infixlines);
    return 0;
}
