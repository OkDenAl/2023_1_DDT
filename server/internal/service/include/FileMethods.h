#pragma once

#include <string>
#include <utility>

inline const std::string CPP_EXTENSION = "cpp";
inline const std::string PYTHON_EXTENSION = "py";
inline const std::string UNKNOWN_EXTENSION = "";

class FileMethods {
 public:
    static std::pair<std::string, bool> checkFileExtension(const std::string& filename);
};