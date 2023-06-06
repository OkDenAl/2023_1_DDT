#pragma once

#include <utility>
#include <vector>

#include "antlr4-runtime.h"

class IAntlrWrapper {
 public:
    virtual ~IAntlrWrapper() = default;
    virtual std::vector<antlr4::Token*> getTokens() = 0;
    virtual std::vector<int> getTokensTypes() = 0;
    virtual std::vector<std::string> getTokensNames() = 0;
    virtual std::vector<std::pair<std::string, int>> getTokensNamesWithPosition() = 0;
    virtual std::vector<std::pair<std::string, std::pair<int, int>>> getTokensNamesWithFullPosition() = 0;
    virtual std::pair<std::string, std::string> getTokensAndTree() = 0;
    virtual std::string getTokensString() = 0;
    virtual std::string getTreeString() = 0;
};
