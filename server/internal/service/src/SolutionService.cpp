#include "SolutionService.h"

#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <thread>

#include "DiffLib.h"
#include "FileMethods.h"
#include "MyCppAntlr.h"
#include "PythonAntlr.h"
#include "ServiceExceptions.h"
#include "ServiceUtils.h"
#include "SolutionRepository.hpp"
#include "TaskRepository.hpp"

const std::string PLAGIAT_VERDICT = "Не, ну вы не палитесь. Плагиат.";
const std::string NOT_PLAGIAT_VERDICT = "Красивое решение. А главное уникальное !";

SolutionService::SolutionService(std::unique_ptr<ISolutionRepository> solutionRepo,
                                 std::unique_ptr<ITaskRepository> taskRepo)
    : solutionRepo(std::move(solutionRepo)), taskRepo(std::move(taskRepo)) {}

SolutionService::SolutionService() {
    solutionRepo = std::make_unique<SolutionRepository>();
    taskRepo = std::make_unique<TaskRepository>();
}

void SolutionService::setAntlrWrapper(const std::string& fileExtension, const std::string& filedata) {
    std::istringstream in(filedata);
    if (fileExtension == CPP_EXTENSION) {
        antlr = std::make_unique<MyCppAntlr>(in);
    } else if (fileExtension == PYTHON_EXTENSION) {
        antlr = std::make_unique<PythonAntlr>(in);
    }
}

std::pair<std::string, std::string> SolutionService::setResultVerdict(float textBasedRes, float tokenBasedRes,
                                                                      float treshold = 0.5f) {
    float meanRes = (tokenBasedRes + textBasedRes) / 2;
    if (meanRes < treshold) {
        return std::make_pair(
            (boost::format("\n%s\nРезультаты метрик: %.2f\n\tАнализ текста: %.2f\n\tАнализ токенов: %.2f") %
             NOT_PLAGIAT_VERDICT % meanRes % textBasedRes % tokenBasedRes)
                .str(),
            NOT_PLAGIAT_VERDICT);
    }
    return std::make_pair(
        (boost::format("\n%s\nРезультаты метрик: %.2f\n\tАнализ текста: %.2f\n\tАнализ токенов: %.2f\n") %
         PLAGIAT_VERDICT % meanRes % textBasedRes % tokenBasedRes)
            .str(),
        PLAGIAT_VERDICT);
}

std::pair<float, size_t> SolutionService::getMaxTextResMetric(std::vector<Solution>& solutions,
                                                              const std::string& filedata, size_t userId,
                                                              float treshold) {
    std::pair<float, size_t> maxMatch = std::make_pair(0.0, 0);
    for (auto sol : solutions) {
        if (sol.getSenderId() == userId) {
            continue;
        }
        textMetric = std::make_unique<LevDistTextMetric>();
        textMetric->setData(filedata, sol.getSource());
        float textBasedRes = float(textMetric->getMetric());

        textMetric = std::make_unique<JaccardTextMetric>();
        textMetric->setData(filedata, sol.getSource());
        textBasedRes = (textBasedRes + float(textMetric->getMetric())) / 2;

        if (maxMatch.first < textBasedRes) {
            maxMatch.first = textBasedRes;
            maxMatch.second = sol.getId();
        }

        if (textBasedRes > treshold) {
            break;
        }
    }
    return maxMatch;
}

std::pair<float, size_t> SolutionService::getMaxTokenResMetric(std::vector<Solution>& solutions,
                                                               std::vector<int>& tokens, size_t userId,
                                                               float treshold) {
    std::pair<float, size_t> maxMatch = std::make_pair(0.0, 0);
    for (auto sol : solutions) {
        if (sol.getSenderId() == userId) {
            continue;
        }
        tokenMetric = std::make_unique<LevDistTokenMetric>();
        tokenMetric->setData(tokens, Utils::convertStringIntoIntArray(sol.getTokens()));
        float tokenBasedRes = float(tokenMetric->getMetric());

        auto sol_tokens = Utils::convertStringIntoIntArray(sol.getTokens());

        tokenMetric = std::make_unique<WShinglingTokenMetric>();
        tokenMetric->setData(tokens, Utils::convertStringIntoIntArray(sol.getTokens()));
        tokenBasedRes = (tokenBasedRes + float(tokenMetric->getMetric())) / 2;

        if (maxMatch.first < tokenBasedRes) {
            maxMatch.first = tokenBasedRes;
            maxMatch.second = sol.getId();
        }

        if (tokenBasedRes > treshold) {
            break;
        }
    }
    return maxMatch;
}

std::pair<Solution, Solution::Codes> SolutionService::createSolution(size_t userId, size_t taskId,
                                                                     const std::string& filename,
                                                                     const std::string& filedata) {
    try {
        std::pair<std::string, bool> fileExtension = FileMethods::checkFileExtension(filename);
        if (!fileExtension.second) {
            throw FileExtensionException("unknown file extension");
        }

        setAntlrWrapper(fileExtension.first, filedata);
        std::vector<int> tokensTypes = antlr->getTokensTypes();
        auto curTokensNamesWithFullPosition = antlr->getTokensNamesWithFullPosition();
        std::string astTree = antlr->getTreeString();

        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        float treshold = taskRepo->getTaskById(taskId).value().getTreshhold();

        std::vector<Solution> solutions = solutionRepo->getSolutionsByTaskIdAndLanguage(taskId, fileExtension.first);

        std::pair<float, size_t> textBasedRes;
        std::pair<float, size_t> tokenBasedRes;

        std::thread t1([&textBasedRes, this, &solutions, &filedata, &userId, &treshold]() {
            textBasedRes = getMaxTextResMetric(solutions, filedata, userId, treshold);
        });
        std::thread t2([&tokenBasedRes, this, &solutions, &tokensTypes, &userId, &treshold]() {
            tokenBasedRes = getMaxTokenResMetric(solutions, tokensTypes, userId, treshold);
        });
        t1.join();
        t2.join();

        std::pair<std::string, std::string> result =
            setResultVerdict(textBasedRes.first, tokenBasedRes.first, treshold);

        size_t plagiatSolId = 0;
        Solution::Codes codes;
        if (result.second == PLAGIAT_VERDICT) {
            if (textBasedRes.first > tokenBasedRes.first) {
                plagiatSolId = textBasedRes.second;
            } else {
                plagiatSolId = tokenBasedRes.second;
            }
            Solution originalSol = solutionRepo->getSolutionById(plagiatSolId).value();
            setAntlrWrapper(originalSol.getLanguage(), originalSol.getSource());
            auto originalTokensNamesWithFullPosition = antlr->getTokensNamesWithFullPosition();
            FoundSame foundSame;
            foundSame.setData(originalTokensNamesWithFullPosition, curTokensNamesWithFullPosition);
            std::pair<std::string, std::string> res = foundSame.getTexts();
            codes = Solution::Codes(res.first, res.second);
        }

        Solution sol =
            Solution(std::ctime(&now), userId, filedata, taskId, result.first,
                     Utils::convertIntArrayIntoString(tokensTypes), astTree, plagiatSolId, fileExtension.first);

        size_t id = solutionRepo->storeSolution(sol);
        sol.setId(id);
        return std::make_pair(sol, codes);
    } catch (...) {
        throw;
    }
}

void SolutionService::deleteSolutionById(size_t solId) {
    try {
        solutionRepo->deleteSolutionById(solId);
    } catch (...) {
        throw;
    }
}

std::pair<std::string, std::string> SolutionService::getMetrics(size_t solId) {
    try {
        Solution sol = solutionRepo->getSolutionById(solId).value();
        std::string tokens = sol.getTokens();
        std::string astTree = sol.getAstTree();
        return std::make_pair(tokens, astTree);
    } catch (...) {
        throw;
    }
}

std::vector<Solution> SolutionService::getSolutionsByUserAndTaskId(size_t user_id, size_t task_id) {
    try {
        return solutionRepo->getSolutionsByTaskIdAndSenderId(task_id, user_id);
    } catch (...) {
        throw;
    }
}
