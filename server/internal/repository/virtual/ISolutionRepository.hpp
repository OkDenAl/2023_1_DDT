#ifndef SOURCEDOUT_ISOLUTIONREPOSITORY_HPP
#define SOURCEDOUT_ISOLUTIONREPOSITORY_HPP

#include <iostream>
#include <optional>
#include <vector>

#include "Solution.hpp"

class ISolutionRepository {
 public:
    virtual ~ISolutionRepository() = default;

    virtual std::optional<Solution> getSolutionById(size_t id) = 0;

    virtual std::vector<Solution> getSolutionsBySenderId(size_t sender_id) = 0;

    virtual std::vector<Solution> getSolutionsByTaskId(size_t task_id) = 0;

    virtual std::vector<Solution> getSolutionsByTaskIdAndSenderId(size_t, size_t) = 0;

    virtual std::vector<Solution> getSolutionsByTaskIdAndLanguage(size_t, std::string) = 0;

    virtual size_t storeSolution(Solution solution) = 0;

    virtual void updateSolution(Solution solution) = 0;

    virtual void deleteSolutionById(size_t id) = 0;

    virtual void deleteSolution(Solution solution) = 0;

    virtual std::optional<Solution> getOriginalSolution(size_t id) = 0;
};

#endif  // SOURCEDOUT_ISOLUTIONREPOSITORY_HPP
