//
// Created by march on 16.05.2023.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

#include "TokenMetricLib.h"

class LevDistTokenMetricTest : public ::testing::Test {
 protected:
    std::unique_ptr<LevDistTokenMetric> levDistTokenMetric;
    void SetUp() { levDistTokenMetric = std::make_unique<LevDistTokenMetric>(); }
    void TearDown() {}
};

class WShinglingTokenMetricTest : public ::testing::Test {
 protected:
    std::unique_ptr<WShinglingTokenMetric> wShinglingTokenMetric;
    void SetUp() { wShinglingTokenMetric = std::make_unique<WShinglingTokenMetric>(); }
    void TearDown() {}
};

TEST_F(LevDistTokenMetricTest, check_eq_progs) {
    std::vector<int> tokens1 = {1, 2, 3};

    levDistTokenMetric->setData(tokens1, tokens1);

    EXPECT_EQ(levDistTokenMetric->getMetric(), 1);
}

TEST_F(LevDistTokenMetricTest, check_absolutely_not_eq_progs) {
    std::vector<int> tokens1 = {1, 2, 3};
    std::vector<int> tokens2 = {3, 4, 5, 6};

    levDistTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(levDistTokenMetric->getMetric() < 0.5, true);
}

TEST_F(LevDistTokenMetricTest, test_with_empty_prog) {
    std::vector<int> tokens1 = {1, 2, 3};
    std::vector<int> tokens2 = {};

    levDistTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(levDistTokenMetric->getMetric(), 0);
}

TEST_F(WShinglingTokenMetricTest, check_eq_progs) {
    std::vector<int> tokens1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> tokens2 = {1, 2, 3, 4, 5, 6};

    wShinglingTokenMetric->setData(tokens1, tokens1);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 1);
}

TEST_F(WShinglingTokenMetricTest, check_absolutely_not_eq_progs) {
    std::vector<int> tokens1 = {1, 2, 3};
    std::vector<int> tokens2 = {4, 5, 6};

    wShinglingTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 0);
}

TEST_F(WShinglingTokenMetricTest, test_with_empty_prog) {
    std::vector<int> tokens1 = {1, 2, 3};
    std::vector<int> tokens2 = {};

    wShinglingTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 0);
}

TEST_F(WShinglingTokenMetricTest, test_with_empty_progs) {
    std::vector<int> tokens1 = {};
    std::vector<int> tokens2 = {};

    wShinglingTokenMetric->setData(tokens1, tokens2);

    EXPECT_EQ(wShinglingTokenMetric->getMetric(), 0);
}

TEST_F(WShinglingTokenMetricTest, test_with_small_size) {
    std::vector<int> tokens1 = {1};
    std::vector<int> tokens2 = {2, 3};

    wShinglingTokenMetric->setData(tokens1, tokens2);

    double res = wShinglingTokenMetric->getMetric();
    EXPECT_EQ(res, 0);
}

TEST_F(WShinglingTokenMetricTest, test_with_big_size) {
    std::vector<int> tokens = {9,   45,  132, 85,  86,  89,  78,  45,  132, 128, 45,  132, 101, 1,
                               128, 132, 127, 132, 103, 103, 132, 128, 84,  85,  132, 115, 1,   86,
                               89,  43,  85,  132, 97,  1,   86,  132, 120, 128, 132, 113, 1,   128,
                               90,  132, 127, 132, 102, 102, 132, 128, 59,  1,   128, 90,  -1};

    wShinglingTokenMetric->setData(tokens, tokens);

    double res = wShinglingTokenMetric->getMetric();
    EXPECT_EQ(res, 1);
}
