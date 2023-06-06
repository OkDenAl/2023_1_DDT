#include "ServiceUtils.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

std::string Utils::convertIntArrayIntoString(std::vector<int>& arr) {
    std::string str;
    for (size_t i = 0; i < arr.size(); i++) {
        str += std::to_string(arr[i]) + " ";
    }
    return str;
}

std::vector<int> Utils::convertStringIntoIntArray(const std::string& str) {
    std::stringstream ss(str);
    std::vector<int> v;

    std::copy(std::istream_iterator<int>(ss), {}, back_inserter(v));
    return v;
}
