#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IUserService.h"
#include "UserManager.h"

class UserServiceMock : public IUserService {
 public:
    UserServiceMock() = default;
    ~UserServiceMock() = default;
    MOCK_METHOD(User, createUser, (std::string login, std::string username, std::string password), (override));
    MOCK_METHOD(User, getUserById, (size_t id), (override));
    MOCK_METHOD(void, deleteUser, (size_t id), (override));
};

class UserManagerSuite : public ::testing::Test {
 protected:
    void SetUp() override { manager.setService(userService); }

    std::shared_ptr<UserServiceMock> userService = std::make_shared<UserServiceMock>();
    UserManager manager;
};

TEST_F(UserManagerSuite, LoginUserTest) {
    Request req;
    Header h1, h2;
    h1.name = "login";
    h1.value = 1;
    req.headers = {h1};
    EXPECT_CALL(*userService, getUserById(1));
    manager.loginUser(req);
}

TEST_F(UserManagerSuite, RgisterUserTest) {
    Request req;
    Header h1, h2, h3;
    h1.name = "login";
    h1.value = "1";
    h2.name = "username";
    h2.value = "2";
    h3.name = "password";
    h3.value = "3";
    req.headers = {h1, h2, h3};
    EXPECT_CALL(*userService, createUser("1", "2", "3"));
    manager.registerUser(req);
}
