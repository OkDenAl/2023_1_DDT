#pragma once

#include <memory>

#include "ITaskRepository.hpp"
#include "ITaskService.h"

class TaskService : public ITaskService {
 private:
    std::unique_ptr<ITaskRepository> taskRepo;

 public:
    explicit TaskService(std::unique_ptr<ITaskRepository> taskRepo);
    TaskService();
    Task createTask(const std::string& desc, const std::string& name = "Default name", float treshold = 0.5f) override;
    Task getTask(size_t id) override;
    std::vector<Task> getAllTasks() override;
    void deleteTask(size_t id) override;
};
