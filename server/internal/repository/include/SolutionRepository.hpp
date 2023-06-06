#ifndef SOURCEDOUT_SOLUTIONREPOSITORY_HPP
#define SOURCEDOUT_SOLUTIONREPOSITORY_HPP

#include <boost/format.hpp>
#include <fstream>
#include <iostream>
#include <optional>
#include <pqxx/pqxx>

#include "ISolutionRepository.hpp"
#include "dbManager.hpp"

using namespace pqxx;

class SolutionRepository : public ISolutionRepository {
 public:
    SolutionRepository();

    std::optional<Solution> getSolutionById(size_t id) override;

    std::vector<Solution> getSolutionsBySenderId(size_t sender_id) override;

    std::vector<Solution> getSolutionsByTaskId(size_t task_id) override;

    std::vector<Solution> getSolutionsByTaskIdAndSenderId(size_t, size_t) override;

    std::vector<Solution> getSolutionsByTaskIdAndLanguage(size_t task_id, std::string lang) override;

    size_t storeSolution(Solution solution) override;

    void updateSolution(Solution solution) override;

    void deleteSolutionById(size_t id) override;

    void deleteSolution(Solution solution) override;

    std::optional<Solution> getOriginalSolution(size_t id) override;

 private:
    static Solution makeSolution(const result::const_iterator &c);

    std::shared_ptr<dbManager> manager;
};

#endif
