#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ISolutionService.h"
#include "SolutionManager.h"

class SolutionServiceMock : public ISolutionService {
 public:
    SolutionServiceMock() = default;
    MOCK_METHOD(Solution, createSolution, (size_t userId, size_t taskId, std::string source), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsByUserAndTaskId, (size_t userId, size_t taskId), (override));
    MOCK_METHOD((std::pair<std::string, std::string>), getMetrics, (size_t solId), (override));
    MOCK_METHOD(void, deleteSolutionById, (size_t solId), (override));
};

class SolutionManagerSuite : public ::testing::Test {
 protected:
    void SetUp() override { manager.setService(solutionService); }

    std::shared_ptr<SolutionServiceMock> solutionService = std::make_shared<SolutionServiceMock>();
    SolutionManager manager;
};

TEST_F(SolutionManagerSuite, GetSolutionByUserAndTaskTest) {
    Request req;
    Header h1, h2;
    h1.name = "user_id";
    h2.name = "task_id";
    h1.value = '1';
    h2.value = '2';
    req.headers = {h1, h2};
    EXPECT_CALL(*solutionService, getSolutionsByUserAndTaskId(1, 2));
    manager.getAllSolutions(req);
}

TEST_F(SolutionManagerSuite, GetMetricsTest) {
    Request req;
    Header h1;
    h1.name = "sol_id";
    h1.value = "1";
    req.headers = {h1};
    EXPECT_CALL(*solutionService, getMetrics(1));
    manager.getMetrics(req);
}

TEST_F(SolutionManagerSuite, CreateSolutionTest) {
    Request req;
    Header h1, h2, h3;
    h1.name = "user_id";
    h1.value = "1";
    h2.name = "task_id";
    h2.value = "2";
    h3.name = "source";
    h3.value = "int main() { return 0; }";
    req.headers = {h1, h2, h3};
    EXPECT_CALL(*solutionService, createSolution(1, 2, "int main() { return 0; }"));
    manager.createSolution(req);
}
