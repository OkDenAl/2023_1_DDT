#include "UserManager.h"

#include "ServiceExceptions.h"
#include "Utils.h"

UserManager::UserManager() : serializer(std::make_shared<Serializer>()), userService(std::make_shared<UserService>()) {}

void UserManager::setService(std::shared_ptr<IUserService> service) { userService = service; }

http::message_generator UserManager::loginUser(http::request<http::string_body> &&req) {
    std::string login, password;

    try {
        std::tie(login, password) = serializer->deserialUserData(req.body());
    } catch (...) {
        return getBadRequest(req, "Bad parameters");
    }

    User user;
    bool flag = true;

    try {
        user = userService->login(login, password);
    } catch (...) {
        flag = false;
    }

    if (flag) {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(user);
        std::cout << serializer->serialUserData(user) << std::endl;
        res.prepare_payload();
        return res;
    } else {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(user);
        res.prepare_payload();
        return res;
    }
}

http::message_generator UserManager::registerUser(http::request<http::string_body> &&req) {
    std::string login, password, username;

    try {
        std::tie(login, password, username) = serializer->deserialNewUserData(req.body());
    } catch (...) {
        return getBadRequest(req, "Bad parameters");
    }

    try {
        User user = userService->createUser(login, username, password);
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = serializer->serialUserData(user);
        res.prepare_payload();
        return res;
    } catch (const ValidateException &e) {
        http::response<http::string_body> res{http::status::forbidden, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = "Невалидные данные";
        res.prepare_payload();
        return res;
    } catch (...) {
        return getInternalServerError(req, "Something went wrong!");
    }
}
