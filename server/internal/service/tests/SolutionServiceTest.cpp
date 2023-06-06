#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <istream>
#include <sstream>

#include "SolutionService.h"

class Exception : public std::exception {
    std::string _msg;

 public:
    explicit Exception(const std::string& msg) : _msg(msg) {}
    const char* what() const noexcept override { return _msg.c_str(); }
};

class SolutionRepositoryMock : public ISolutionRepository {
 public:
    ~SolutionRepositoryMock() override = default;
    MOCK_METHOD(std::optional<Solution>, getSolutionById, (size_t id), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsBySenderId, (size_t sender_id), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsByTaskId, (size_t task_id), (override));
    MOCK_METHOD(size_t, storeSolution, (Solution solution), (override));
    MOCK_METHOD(void, updateSolution, (Solution solution), (override));
    MOCK_METHOD(void, deleteSolutionById, (size_t id), (override));
    MOCK_METHOD(void, deleteSolution, (Solution solution), (override));
    MOCK_METHOD(std::optional<Solution>, getOriginalSolution, (size_t id), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsByTaskIdAndSenderId, (size_t user_id, size_t task_id), (override));
    MOCK_METHOD(std::vector<Solution>, getSolutionsByTaskIdAndLanguage, (size_t, std::string), (override));
};

class TaskRepositoryMock : public ITaskRepository {
 public:
    ~TaskRepositoryMock() override = default;
    MOCK_METHOD(std::optional<Task>, getTaskById, (size_t id), (override));
    MOCK_METHOD(void, updateTask, (const Task& task), (override));
    MOCK_METHOD(size_t, storeTask, (Task task), (override));
    MOCK_METHOD(void, deleteTask, (Task task), (override));
    MOCK_METHOD(void, deleteTaskById, (size_t id), (override));
    MOCK_METHOD(std::vector<Task>, getAllTasks, (), (override));
};

struct SolutionServiceTest : public testing::Test {
    SolutionService* ss;
    SolutionRepositoryMock* solutionMockPtr;
    TaskRepositoryMock* taskMockPtr;

    void SetUp() {
        auto sMock = std::make_unique<SolutionRepositoryMock>();
        solutionMockPtr = sMock.get();
        auto tMock = std::make_unique<TaskRepositoryMock>();
        taskMockPtr = tMock.get();
        ss = new SolutionService(std::move(sMock), std::move(tMock));
    }
    void TearDown() { delete ss; }
};

ACTION(NoSolutionException) { throw Exception("no solution with this id in db"); }

TEST_F(SolutionServiceTest, deleteSolution) {
    EXPECT_CALL(*solutionMockPtr, deleteSolutionById(1)).Times(1);
    ss->deleteSolutionById(1);
}

TEST_F(SolutionServiceTest, deleteSolutionException) {
    EXPECT_CALL(*solutionMockPtr, deleteSolutionById(-1)).Times(1).WillRepeatedly(NoSolutionException());
    EXPECT_THROW(ss->deleteSolutionById(-1), std::exception);
}

TEST_F(SolutionServiceTest, getMetrics) {
    EXPECT_CALL(*solutionMockPtr, getSolutionById(1))
        .Times(1)
        .WillOnce(::testing::Return(Solution(1, "", 1, "", 1, "", "tokens", "astTree", 1, "cpp")));
    std::pair<std::string, std::string> metrics = ss->getMetrics(1);
    EXPECT_EQ(metrics.first, "tokens");
    EXPECT_EQ(metrics.second, "astTree");
}

TEST_F(SolutionServiceTest, getMetricsException) {
    EXPECT_CALL(*solutionMockPtr, getSolutionById(-1)).Times(1).WillRepeatedly(NoSolutionException());
    EXPECT_THROW(ss->getMetrics(-1), std::exception);
}

TEST_F(SolutionServiceTest, createSolutionPlagiat) {
    EXPECT_CALL(*solutionMockPtr, storeSolution(Solution(0, "", 2, "source", 1, "", "", "", 1, "cpp")))
        .Times(1)
        .WillRepeatedly(::testing::Return(1));

    std::vector<Solution> solutions;
    solutions.push_back(
        Solution(0, "", 1, "int main(){return 0;}", 1, "", "45 132 85 86 89 59 1 128 90 -1", "", -1, "cpp"));
    EXPECT_CALL(*solutionMockPtr, getSolutionsByTaskIdAndLanguage(1, "cpp"))
        .Times(1)
        .WillOnce(::testing::Return(solutions));

    EXPECT_CALL(*taskMockPtr, getTaskById(1)).Times(1).WillOnce(::testing::Return(Task(1, "desription", 0.5f, "name")));

    EXPECT_CALL(*solutionMockPtr, getSolutionById(0))
        .Times(1)
        .WillOnce(::testing::Return(std::make_optional(
            Solution(0, "", 1, "int main(){return 0;}", 1, "", "45 132 85 86 89 59 1 128 90 -1", "", -1, "cpp"))));

    auto sol = ss->createSolution(2, 1, "main.cpp", "size_t main(){return 1;}");
    EXPECT_EQ(sol.first.getId(), 1);
    // EXPECT_EQ(sol.second.original, "int main(){return 0;}");
    EXPECT_EQ(
        sol.first.getResult(),
        "\nНе, ну вы не палитесь. Плагиат.\nРезультаты метрик: 0.72\n\tАнализ текста: 0.54\n\tАнализ токенов: 0.89\n");
}

TEST_F(SolutionServiceTest, createSolutionNonPlagiat) {
    EXPECT_CALL(*solutionMockPtr, storeSolution(Solution(0, "", 2, "source", 1, "", "", "", 1, "cpp")))
        .Times(1)
        .WillRepeatedly(::testing::Return(1));

    std::vector<Solution> solutions;
    solutions.push_back(
        Solution(0, "", 1, "int main(){return 0;}", 1, "", "45 132 85 86 89 59 1 128 90 -1", "", -1, "cpp"));
    EXPECT_CALL(*solutionMockPtr, getSolutionsByTaskIdAndLanguage(1, "cpp"))
        .Times(1)
        .WillOnce(::testing::Return(solutions));

    EXPECT_CALL(*taskMockPtr, getTaskById(1)).Times(1).WillOnce(::testing::Return(Task(1, "desription", 0.5f, "name")));

    Solution sol = ss->createSolution(1, 1, "main.cpp", "int main(){return 0;}").first;
    EXPECT_EQ(sol.getResult(),
              "\nКрасивое решение. А главное уникальное !\nРезультаты метрик: 0.00\n\tАнализ текста: 0.00\n\tАнализ "
              "токенов: 0.00");
}
