#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ISolutionManager.h"
#include "ITaskManager.h"
#include "IUserManager.h"
#include "Router.h"

class SolutionManagerMock : public ISolutionManager {
 public:
    SolutionManagerMock() = default;
    MOCK_METHOD(Response, getAllSolutions, (const Request& req), (override));
    MOCK_METHOD(Response, createSolution, (const Request& req), (override));
    MOCK_METHOD(Response, getMetrics, (const Request& req), (override));
};

class TaskManagerMock : public ITaskManager {
 public:
    TaskManagerMock() = default;
    MOCK_METHOD(Response, createTask, (const Request& req), (override));
    MOCK_METHOD(Response, getAllTasks, (const Request& req), (override));
};

class UserManagerMock : public IUserManager {
 public:
    UserManagerMock() = default;
    MOCK_METHOD(Response, loginUser, (const Request& req), (override));
    MOCK_METHOD(Response, registerUser, (const Request& req), (override));
};

class RouterSuite : public ::testing::Test {
 protected:
    void SetUp() override {
        router.setSolutionManager(solutionManager);
        router.setUserManager(userManager);
        router.setTaskManager(taskManager);
    }

    std::shared_ptr<UserManagerMock> userManager = std::make_shared<UserManagerMock>();
    std::shared_ptr<TaskManagerMock> taskManager = std::make_shared<TaskManagerMock>();
    std::shared_ptr<SolutionManagerMock> solutionManager = std::make_shared<SolutionManagerMock>();
    Router router;
};

TEST_F(RouterSuite, RegisterUserTest) {
    Request req;
    req.method = "POST";
    req.uri = "/user/register";
    Response res;
    EXPECT_CALL(*userManager, registerUser);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, LoginUserTest) {
    Request req;
    req.method = "GET";
    req.uri = "/user/login";
    Response res;
    EXPECT_CALL(*userManager, loginUser);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, GetAllTasksTest) {
    Request req;
    req.method = "GET";
    req.uri = "/task/all";
    Response res;
    EXPECT_CALL(*taskManager, getAllTasks);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, CreateTaskTest) {
    Request req;
    req.method = "POST";
    req.uri = "/task/create";
    Response res;
    EXPECT_CALL(*taskManager, createTask);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, GetSolutionMetricsTest) {
    Request req;
    req.method = "GET";
    req.uri = "/solution/metrics";
    Response res;
    EXPECT_CALL(*solutionManager, getMetrics);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, CreateSolutionTest) {
    Request req;
    req.method = "POST";
    req.uri = "/solution/create";
    Response res;
    EXPECT_CALL(*solutionManager, createSolution);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, GetAllSolutionsTest) {
    Request req;
    req.method = "GET";
    req.uri = "/solution/all";
    Response res;
    EXPECT_CALL(*solutionManager, getAllSolutions);
    router.handleRequest(req, res);
}

TEST_F(RouterSuite, BadMethodTest) {
    Request req;
    req.method = "";
    req.uri = "/solution/all";
    Response res;
    router.handleRequest(req, res);
    EXPECT_EQ(res.status, 500);
}

TEST_F(RouterSuite, BadUriTest) {
    Request req;
    req.method = "GET";
    req.uri = "";
    Response res;
    router.handleRequest(req, res);
    EXPECT_EQ(res.status, 500);
}
