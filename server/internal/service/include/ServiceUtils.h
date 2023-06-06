#pragma once

#include <string>
#include <vector>

class Utils {
 public:
    static std::string convertIntArrayIntoString(std::vector<int>& arr);
    static std::vector<int> convertStringIntoIntArray(const std::string& str);
};
