#ifndef SOURCEDOUT_IUSERREPOSITORY_HPP
#define SOURCEDOUT_IUSERREPOSITORY_HPP

#include <optional>
#include <vector>

#include "User.hpp"

class IUserRepository {
 public:
    virtual ~IUserRepository() = default;

    virtual std::optional<User> getUserById(size_t id) = 0;

    virtual std::optional<User> getUserByLogin(std::string login) = 0;

    virtual size_t makeUser(User user) = 0;

    virtual void deleteUser(User user) = 0;

    virtual void update(User user) = 0;

    virtual void deleteByUserId(size_t user_id) = 0;

    virtual std::vector<User> getAllUsers() = 0;
};

#endif  // SOURCEDOUT_IUSERREPOSITORY_HPP
