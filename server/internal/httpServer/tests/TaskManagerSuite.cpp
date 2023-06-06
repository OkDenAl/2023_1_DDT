#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ITaskService.h"
#include "TaskManager.h"

class TaskServiceMock : public ITaskService {
 public:
    TaskServiceMock() = default;
    ~TaskServiceMock() = default;

    MOCK_METHOD(Task, createTask, (std::string desc), (override));
    MOCK_METHOD(Task, getTask, (size_t id), (override));
    MOCK_METHOD(std::vector<Task>, getAllTasks, (), (override));
    MOCK_METHOD(void, deleteTask, (size_t id), (override));
};

class TaskManagerSuite : public ::testing::Test {
 protected:
    void SetUp() override { manager.setService(taskService); }

    std::shared_ptr<TaskServiceMock> taskService = std::make_shared<TaskServiceMock>();
    TaskManager manager;
};

TEST_F(TaskManagerSuite, CreateTaskTest) {
    Request req;
    Header h1, h2;
    h1.name = "description";
    h1.value = "a";
    req.headers = {h1};
    EXPECT_CALL(*taskService, createTask("a"));
    manager.createTask(req);
}

TEST_F(TaskManagerSuite, GetAllTaskTest) {
    Request req;
    EXPECT_CALL(*taskService, getAllTasks);
    manager.getAllTasks(req);
}
