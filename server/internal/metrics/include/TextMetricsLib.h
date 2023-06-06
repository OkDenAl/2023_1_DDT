//
// Created by march on 02.05.2023.
//

#ifndef SOURCEDOUT_DECLARATION_H
#define SOURCEDOUT_DECLARATION_H

#include <boost/tokenizer.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class ITextMetric {
 public:
    virtual ~ITextMetric() = default;
    virtual void setData(std::string text1, std::string text2) = 0;
    virtual double getMetric() = 0;
};

class PrepareDataTextMetric : public ITextMetric {
 public:
    void setData(std::string text1, std::string text2) override;

 protected:
    std::vector<std::string> tokens1;
    std::vector<std::string> tokens2;

 private:
    static std::string deleteComments(const std::string& text);
    static std::vector<std::string> tbmTokenizer(const std::string& text);
};

class LevDistTextMetric : public PrepareDataTextMetric {
 public:
    double getMetric() override;
};

class JaccardTextMetric : public PrepareDataTextMetric {
 public:
    double getMetric() override;
};

#endif  // SOURCEDOUT_DECLARATION_H
