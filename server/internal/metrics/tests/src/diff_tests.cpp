//
// Created by march on 01.06.2023.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "DiffLib.h"

class FoundSameTest : public ::testing::Test {
 protected:
    std::unique_ptr<FoundSame> foundSame;
    void SetUp() { foundSame = std::make_unique<FoundSame>(); }
    void TearDown() {}
};

TEST_F(FoundSameTest, check_eq_progs) {
    foundSame->setData({{"a", {1, 0}}, {"a", {2, 0}}, {"a", {3, 0}}}, {{"a", {1, 0}}, {"a", {2, 0}}, {"a", {3, 0}}});

    std::pair<std::string, std::string> res = foundSame->getTexts();
    std::pair<std::string, std::string> exp_res = {
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span></div>\n"
        "</html>",
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span></div>\n"
        "</html>"};
    EXPECT_EQ(res, exp_res);
}

TEST_F(FoundSameTest, check_progs_with_replace) {
    foundSame->setData({{"a", {1, 0}}, {"a", {2, 0}}, {"a", {3, 0}}}, {{"a", {1, 0}}, {"b", {2, 0}}, {"a", {3, 0}}});

    std::pair<std::string, std::string> res = foundSame->getTexts();
    std::pair<std::string, std::string> exp_res = {
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #FFD700\">a </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span></div>\n"
        "</html>",
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #FFD700\">b </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span></div>\n"
        "</html>"};
    EXPECT_EQ(res, exp_res);
}

TEST_F(FoundSameTest, check_progs_with_delete) {
    foundSame->setData({{"a", {1, 0}}, {"d", {2, 0}}, {"a", {3, 0}}}, {{"a", {1, 0}}, {"a", {3, 0}}});

    std::pair<std::string, std::string> res = foundSame->getTexts();
    std::pair<std::string, std::string> exp_res = {
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div><span style=\"background-color: #96CC9F\">a </span><br>\n"
        "<span></span><span style=\"background-color: #CD5C5C\">d </span><br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span></div>\n"
        "</html>",
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<div><span style=\"background-color: #96CC9F\">a </span><span style=\"background-color: "
        "#CD5C5C\"></span><br>\n"
        "<br>\n"
        "<span></span><span style=\"background-color: #96CC9F\">a </span></div>\n"
        "</html>"};
    EXPECT_EQ(res, exp_res);
}
