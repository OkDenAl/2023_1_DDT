#include "../include/User.hpp"

#include <iostream>

User::User(size_t id_, std::string login_, std::string password_, std::string username_) noexcept
    : id(id_), login(std::move(login_)), password(std::move(password_)), username(std::move(username_)) {}

User::User(std::string login_, std::string password_, std::string username_) noexcept
    : id(0), login(std::move(login_)), password(std::move(password_)), username(std::move(username_)) {}

User::User() noexcept : id(0) {}

const std::string &User::getLogin() const noexcept { return login; }

void User::setId(size_t id_) noexcept { id = id_; }

void User::setLogin(const std::string &login_) noexcept { User::login = login_; }

const std::string &User::getPassword() const noexcept { return password; }

void User::setPassword(const std::string &password_) noexcept { User::password = password_; }

const std::string &User::getUsername() const noexcept { return username; }

void User::setUsername(const std::string &username_) noexcept { User::username = username_; }

size_t User::getId() const noexcept { return id; }

std::ostream &operator<<(std::ostream &os, const User &user) noexcept {
    os << "id: " << user.id << " login: " << user.login << " password: " << user.password
       << " username: " << user.username;
    return os;
}

bool User::operator==(const User &rhs) const noexcept { return id == rhs.id; }

bool User::operator!=(const User &rhs) const noexcept { return !(rhs == *this); }
