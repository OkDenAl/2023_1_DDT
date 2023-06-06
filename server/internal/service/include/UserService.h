#pragma once
#include <memory>

#include "IUserRepository.hpp"
#include "IUserService.h"
#include "UserValidator.h"

class UserService : public IUserService {
 private:
    std::unique_ptr<IUserRepository> userRepo;

 public:
    explicit UserService(std::unique_ptr<IUserRepository> userRepo);
    UserService();
    User createUser(const std::string& login, const std::string& username, const std::string& password) override;
    User login(const std::string& login, const std::string& password) override;
    void deleteUser(size_t id) override;
};
