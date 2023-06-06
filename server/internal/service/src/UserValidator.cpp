#include "UserValidator.h"

#include <iostream>
#include <regex>

bool UserValidator::validate(const User& user) {
    if (validateLogin(user.getLogin()) && validatePassword(user.getPassword()) &&
        validateUsername(user.getUsername())) {
        return true;
    }
    return false;
}

bool UserValidator::validateLogin(const std::string& login) {
    if (login.length() < 3 || login.length() > 30) {
        return false;
    }
    const std::regex pattern("(\\w+)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(login, pattern);
}

bool UserValidator::validatePassword(const std::string& password) {
    if (password.length() < 8 || password.length() > 30) {
        return false;
    }
    return true;
}

bool UserValidator::validateUsername(const std::string& username) {
    if (username.length() < 3 || username.length() > 20) {
        return false;
    }
    return true;
}
