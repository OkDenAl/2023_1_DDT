#pragma once

#include <utility>
#include <vector>

#include "Solution.hpp"

class ISolutionService {
 public:
    virtual ~ISolutionService() = default;
    virtual std::pair<Solution, Solution::Codes> createSolution(size_t userId, size_t taskId,
                                                                const std::string& filename,
                                                                const std::string& filedata) = 0;
    virtual void deleteSolutionById(size_t solId) = 0;
    virtual std::vector<Solution> getSolutionsByUserAndTaskId(size_t user_id, size_t task_id) = 0;
    virtual std::pair<std::string, std::string> getMetrics(size_t solId) = 0;
};
