#include "FileMethods.h"

#include <cstdio>
#include <fstream>

std::pair<std::string, bool> FileMethods::checkFileExtension(const std::string& filename) {
    if (filename.substr(filename.find_last_of(".") + 1) == CPP_EXTENSION) {
        return std::make_pair(CPP_EXTENSION, true);
    }
    if (filename.substr(filename.find_last_of(".") + 1) == PYTHON_EXTENSION) {
        return std::make_pair(PYTHON_EXTENSION, true);
    }
    return std::make_pair(UNKNOWN_EXTENSION, false);
}
