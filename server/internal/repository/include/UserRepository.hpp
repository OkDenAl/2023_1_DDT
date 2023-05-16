#ifndef SOURCEDOUT_USERREPOSITORY_HPP
#define SOURCEDOUT_USERREPOSITORY_HPP

#include <iostream>
#include "IUserRepository.hpp"
#include "dbManager.hpp"
#include <pqxx/pqxx>
#include <boost/format.hpp>
#include <fstream>
#include <optional>

using namespace pqxx;


class UserRepository : public IUserRepository {
public:
    explicit UserRepository();

    std::optional<User> getUserById(size_t id) override;

    std::optional<User> getUserByLogin(std::string login) override;

    size_t makeUser(User user) override;

    void deleteUser(User user) override;

    void deleteByUserId(size_t user_id) override;

    std::vector<User> getAllUsers() override;

    void update(User user) override;


private:
    static User makeUser(const result::const_iterator &c);

    std::shared_ptr<dbManager> manager;
};

#endif //SOURCEDOUT_USERREPOSITORY_HPP
