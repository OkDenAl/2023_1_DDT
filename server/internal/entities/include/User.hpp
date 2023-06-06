#ifndef SOURCEDOUT_USER_HPP

#include <iostream>
#include <utility>

#define SOURCEDOUT_USER_HPP

class User {
 private:
    size_t id;
    std::string login;
    std::string password;
    std::string username;

 public:
    User(size_t id_, std::string login_, std::string password_, std::string username_) noexcept;

    User(std::string login_, std::string password_, std::string username_) noexcept;

    User() noexcept;

    [[nodiscard]] const std::string &getLogin() const noexcept;

    void setLogin(const std::string &login) noexcept;

    [[nodiscard]] const std::string &getPassword() const noexcept;

    void setPassword(const std::string &password) noexcept;

    [[nodiscard]] const std::string &getUsername() const noexcept;

    void setUsername(const std::string &username) noexcept;

    [[nodiscard]] size_t getId() const noexcept;

    friend std::ostream &operator<<(std::ostream &os, const User &user) noexcept;

    void setId(size_t id) noexcept;

    bool operator==(const User &rhs) const noexcept;

    bool operator!=(const User &rhs) const noexcept;
};

#endif  // SOURCEDOUT_USER_HPP
