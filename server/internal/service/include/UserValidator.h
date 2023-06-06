#pragma once

#include "User.hpp"

class UserValidator {
 private:
    static bool validateLogin(const std::string& login);
    static bool validatePassword(const std::string& password);
    static bool validateUsername(const std::string& username);

 public:
    static bool validate(const User& user);
};
