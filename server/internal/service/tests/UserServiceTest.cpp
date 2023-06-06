#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ServiceExceptions.h"
#include "UserService.h"

class Exception : public std::exception {
    std::string _msg;

 public:
    explicit Exception(const std::string& msg) : _msg(msg) {}
    const char* what() const noexcept override { return _msg.c_str(); }
};

class UserRepositoryMock : public IUserRepository {
 public:
    ~UserRepositoryMock() override = default;
    MOCK_METHOD(std::optional<User>, getUserById, (size_t id), (override));
    MOCK_METHOD(std::optional<User>, getUserByLogin, (std::string login), (override));
    MOCK_METHOD(size_t, makeUser, (User user), (override));
    MOCK_METHOD(void, deleteUser, (User user), (override));
    MOCK_METHOD(void, deleteByUserId, (size_t id), (override));
    MOCK_METHOD(std::vector<User>, getAllUsers, (), (override));
    MOCK_METHOD(void, update, (User user), (override));
};

struct UserServiceTest : public testing::Test {
    UserService* us;
    UserRepositoryMock* mock_ptr;

    void SetUp() {
        auto mock = std::make_unique<UserRepositoryMock>();
        mock_ptr = mock.get();
        us = new UserService(std::move(mock));
    }
    void TearDown() { delete us; }
};

ACTION(NoUserException) { throw Exception("no user with this id in db"); }

TEST_F(UserServiceTest, deleteUser) {
    EXPECT_CALL(*mock_ptr, deleteByUserId(1)).Times(1);
    us->deleteUser(1);
}

TEST_F(UserServiceTest, deleteUserWithInvalidId) {
    EXPECT_CALL(*mock_ptr, deleteByUserId(1)).Times(1).WillRepeatedly(NoUserException());
    EXPECT_THROW(us->deleteUser(1), std::exception);
}

TEST_F(UserServiceTest, loginOk) {
    EXPECT_CALL(*mock_ptr, getUserByLogin("login"))
        .Times(1)
        .WillOnce(::testing::Return(User(1, "login", "password", "username")));
    User u = us->login("login", "password");
    EXPECT_EQ(u.getLogin(), "login");
    EXPECT_EQ(u.getId(), 1);
    EXPECT_EQ(u.getPassword(), "password");
    EXPECT_EQ(u.getUsername(), "username");
}

TEST_F(UserServiceTest, loginInvalidLogin) {
    EXPECT_CALL(*mock_ptr, getUserByLogin("loginnn")).Times(1).WillOnce(NoUserException());
    EXPECT_THROW(us->login("loginnn", "password"), std::exception);
}

TEST_F(UserServiceTest, loginInvalidPass) {
    EXPECT_CALL(*mock_ptr, getUserByLogin("login"))
        .Times(1)
        .WillOnce(::testing::Return(User(1, "login", "password", "username")));
    EXPECT_THROW(us->login("login", "password1"), std::exception);
}

TEST_F(UserServiceTest, makeUserOk) {
    EXPECT_CALL(*mock_ptr, makeUser(User("login@gmail.com", "password", "username")))
        .Times(1)
        .WillOnce(::testing::Return(1));
    User u = us->createUser("login@gmail.com", "username", "password");
    EXPECT_EQ(u.getLogin(), "login@gmail.com");
    EXPECT_EQ(u.getId(), 1);
    EXPECT_EQ(u.getPassword(), "password");
    EXPECT_EQ(u.getUsername(), "username");
}

TEST_F(UserServiceTest, makeUserInvalidData) {
    EXPECT_CALL(*mock_ptr, makeUser(User("login", "password", "username"))).Times(0);
    EXPECT_THROW(us->createUser("", "", ""), ValidateException);
}
