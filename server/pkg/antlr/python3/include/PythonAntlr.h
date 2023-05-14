#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "IAntlrWrapper.h"
#include "antlr4-runtime.h"

class PythonAntlr:public IAntlrWrapper {
 private:
  std::unique_ptr<antlrcpptest::Python3Lexer> lexer_ptr;
  std::unique_ptr<antlrcpptest::Python3Parser> parser_ptr;
  std::unique_ptr<antlr4::ANTLRInputStream> input_ptr;
  std::unique_ptr<antlr4::CommonTokenStream> tokenStream_ptr;

 public:
  PythonAntlr(std::ifstream &in);
  ~PythonAntlr() override = default;
  std::vector<std::string> getTokensArray() override;
  std::pair<std::string, std::string> getTokensAndTree() override;
  std::string getTokensString() override;
  std::string getTreeString() override;
};