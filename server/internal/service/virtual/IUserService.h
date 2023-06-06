#pragma once

#include <vector>

#include "User.hpp"

class IUserService {
 public:
    virtual ~IUserService() = default;
    virtual User createUser(const std::string& login, const std::string& username, const std::string& password) = 0;
    virtual User login(const std::string& login, const std::string& password) = 0;
    virtual void deleteUser(size_t id) = 0;
};
