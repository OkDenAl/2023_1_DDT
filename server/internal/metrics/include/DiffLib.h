//
// Created by march on 22.05.2023.
//

#ifndef SOURCEDOUT_DIFFLIB_H
#define SOURCEDOUT_DIFFLIB_H

#include <algorithm>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class FoundSame {
 public:
    void setData(std::vector<std::pair<std::string, std::pair<int, int> > > _tokens1,
                 std::vector<std::pair<std::string, std::pair<int, int> > > _tokens2);
    [[maybe_unused]] std::pair<std::string, std::string> getTexts();

 private:
    struct Elem2 {
        std::string op;
        std::pair<std::string, std::pair<int, int> > token1;
        std::pair<std::string, std::pair<int, int> > token2;
    };

    std::vector<std::pair<std::string, std::pair<int, int> > > str_int_tokens1;
    std::vector<std::pair<std::string, std::pair<int, int> > > str_int_tokens2;
    std::vector<Elem2> res_alignment;

    std::pair<std::string, std::string> tokens2text();
    std::pair<std::string, std::string> tokens2html();
    static void outOps(std::vector<std::string> ops, std::string& str);
};

#endif  // SOURCEDOUT_DIFFLIB_H
