#pragma once

#include <memory>
#include <utility>

#include "IAntlrWrapper.h"
#include "ISolutionRepository.hpp"
#include "ISolutionService.h"
#include "ITaskRepository.hpp"
#include "TextMetricsLib.h"
#include "TokenMetricLib.h"

class SolutionService : public ISolutionService {
 private:
    std::unique_ptr<ISolutionRepository> solutionRepo;
    std::unique_ptr<ITaskRepository> taskRepo;
    std::unique_ptr<IAntlrWrapper> antlr;
    std::unique_ptr<ITextMetric> textMetric;
    std::unique_ptr<ITokenMetric> tokenMetric;
    void setAntlrWrapper(const std::string& fileExtension, const std::string& filedata);
    std::pair<std::string, std::string> setResultVerdict(float textBasedRes, float tokenBasedRes, float treshold);
    std::pair<float, size_t> getMaxTextResMetric(std::vector<Solution>& solutions, const std::string& filedata,
                                                 size_t userId, float treshold);

    std::pair<float, size_t> getMaxTokenResMetric(std::vector<Solution>& solutions, std::vector<int>& tokens,
                                                  size_t userId, float treshold);

 public:
    explicit SolutionService(std::unique_ptr<ISolutionRepository> solutionRepo,
                             std::unique_ptr<ITaskRepository> taskRepo);
    SolutionService();
    std::pair<Solution, Solution::Codes> createSolution(size_t userId, size_t taskId, const std::string& filename,
                                                        const std::string& filedata) override;
    void deleteSolutionById(size_t solId) override;
    std::vector<Solution> getSolutionsByUserAndTaskId(size_t user_id, size_t task_id) override;
    std::pair<std::string, std::string> getMetrics(size_t solId) override;
};
