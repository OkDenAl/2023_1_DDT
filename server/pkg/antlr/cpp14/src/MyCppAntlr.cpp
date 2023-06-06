#include "MyCppAntlr.h"

#include <iostream>

MyCppAntlr::MyCppAntlr(std::istream& in) {
    input_ptr = std::make_unique<antlr4::ANTLRInputStream>(in);
    lexer_ptr = std::make_unique<antlrcpptest::CPP14Lexer>(&(*input_ptr));
    tokenStream_ptr = std::make_unique<antlr4::CommonTokenStream>(&(*lexer_ptr));
    parser_ptr = std::make_unique<antlrcpptest::CPP14Parser>(&(*tokenStream_ptr));
}

std::vector<antlr4::Token*> MyCppAntlr::getTokens() {
    tokenStream_ptr->fill();
    std::vector<antlr4::Token*> ans(tokenStream_ptr->size());

    int i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        ans[i] = token;
        i++;
    }

    return ans;
}

std::vector<std::pair<std::string, int>> MyCppAntlr::getTokensNamesWithPosition() {
    tokenStream_ptr->fill();
    std::vector<std::pair<std::string, int>> ans(tokenStream_ptr->size());

    int i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        auto type = token->getText();
        int line = token->getLine();
        ans[i] = std::make_pair(type, line);
        i++;
    }

    return ans;
}

std::vector<std::pair<std::string, std::pair<int, int>>> MyCppAntlr::getTokensNamesWithFullPosition() {
    tokenStream_ptr->fill();
    std::vector<std::pair<std::string, std::pair<int, int>>> ans(tokenStream_ptr->size());

    size_t i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        auto type = token->getText();
        int line = static_cast<int>(token->getLine());
        int pos = static_cast<int>(token->getCharPositionInLine());
        ans[i] = std::make_pair(type, std::make_pair(line, pos));
        i++;
    }

    return ans;
}

std::vector<int> MyCppAntlr::getTokensTypes() {
    tokenStream_ptr->fill();
    std::vector<int> ans(tokenStream_ptr->size());

    int i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        if (token->getText() == "<EOF>") {
            ans[i] = -1;
        } else {
            ans[i] = token->getType();
        }
        i++;
    }

    return ans;
}

std::vector<std::string> MyCppAntlr::getTokensNames() {
    tokenStream_ptr->fill();
    std::vector<std::string> ans(tokenStream_ptr->size());

    int i = 0;
    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        ans[i] = token->getText();
        i++;
    }

    return ans;
}

std::string MyCppAntlr::getTokensString() {
    tokenStream_ptr->fill();
    std::string res;

    for (antlr4::Token* token : tokenStream_ptr->getTokens()) {
        res += token->toString() + " ";
    }

    return res;
}

std::string MyCppAntlr::getTreeString() {
    auto tree = parser_ptr->translationUnit();
    return tree->toStringTree(&(*parser_ptr));
}

std::pair<std::string, std::string> MyCppAntlr::getTokensAndTree() {
    std::string tokens = getTokensString();
    std::string astTree = getTreeString();
    return std::make_pair(tokens, astTree);
}
