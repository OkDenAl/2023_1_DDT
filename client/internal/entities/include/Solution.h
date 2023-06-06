#pragma once

#include <iostream>
#include <string>
#include <utility>

struct Solution {
    size_t id;
    std::string source;
    std::string result;
    struct Codes {
        std::string original;
        std::string current;
    };
};