//
// Created by march on 04.05.2023.
//

#ifndef SOURCEDOUT_TOKENMETRICLIB_H
#define SOURCEDOUT_TOKENMETRICLIB_H

#include <boost/tokenizer.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class ITokenMetric {
 public:
    virtual ~ITokenMetric() = default;
    virtual void setData(std::vector<int> tokens1, std::vector<int> tokens2) = 0;
    virtual double getMetric() = 0;
};

class PrepareDataTokenMetric : public ITokenMetric {
 public:
    void setData(std::vector<int> _tokens1, std::vector<int> _tokens2) override;

 protected:
    std::vector<int> tokens1;
    std::vector<int> tokens2;
};

class LevDistTokenMetric : public PrepareDataTokenMetric {
 public:
    double getMetric() override;
};

class WShinglingTokenMetric : public PrepareDataTokenMetric {
 public:
    double getMetric() override;
};

#endif  // SOURCEDOUT_TOKENMETRICLIB_H
