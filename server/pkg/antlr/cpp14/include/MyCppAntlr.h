#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include "CPP14Lexer.h"
#include "CPP14Parser.h"
#include "IAntlrWrapper.h"

class MyCppAntlr : public IAntlrWrapper {
 private:
    std::unique_ptr<antlrcpptest::CPP14Lexer> lexer_ptr;
    std::unique_ptr<antlrcpptest::CPP14Parser> parser_ptr;
    std::unique_ptr<antlr4::ANTLRInputStream> input_ptr;
    std::unique_ptr<antlr4::CommonTokenStream> tokenStream_ptr;

 public:
    MyCppAntlr(std::istream &in);
    ~MyCppAntlr() override = default;
    std::vector<antlr4::Token *> getTokens() override;
    std::vector<int> getTokensTypes() override;
    std::vector<std::string> getTokensNames() override;
    std::vector<std::pair<std::string, int>> getTokensNamesWithPosition() override;
    std::vector<std::pair<std::string, std::pair<int, int>>> getTokensNamesWithFullPosition() override;
    std::pair<std::string, std::string> getTokensAndTree() override;
    std::string getTokensString() override;
    std::string getTreeString() override;
};
