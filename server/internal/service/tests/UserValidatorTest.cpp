#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "UserValidator.h"

TEST(UserValidatorTest, validateOK) {
    EXPECT_TRUE(UserValidator::validate(User("login@gmail.com", "password", "username")));
}

TEST(UserValidatorTest, invalidLogin) { EXPECT_FALSE(UserValidator::validate(User("", "password", "username"))); }

TEST(UserValidatorTest, invalidPassword) { EXPECT_FALSE(UserValidator::validate(User("login", "", "username"))); }

TEST(UserValidatorTest, invalidUsername) { EXPECT_FALSE(UserValidator::validate(User("login", "password", ""))); }

TEST(UserValidatorTest, invalidUserFields) { EXPECT_FALSE(UserValidator::validate(User("", "", ""))); }
