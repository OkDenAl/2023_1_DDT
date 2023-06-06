#include "TaskService.h"

#include "TaskRepository.hpp"

TaskService::TaskService(std::unique_ptr<ITaskRepository> taskRepo) : taskRepo(std::move(taskRepo)) {}

TaskService::TaskService() { taskRepo = std::make_unique<TaskRepository>(); }

Task TaskService::createTask(const std::string& desc, const std::string& name, float treshold) {
    try {
        Task task = Task(desc, treshold, name);
        size_t id = taskRepo->storeTask(task);
        task.setId(id);
        return task;
    } catch (...) {
        throw;
    }
}

std::vector<Task> TaskService::getAllTasks() {
    try {
        return taskRepo->getAllTasks();
    } catch (...) {
        throw;
    }
}

Task TaskService::getTask(size_t id) {
    try {
        return taskRepo->getTaskById(id).value();
    } catch (...) {
        throw;
    }
}

void TaskService::deleteTask(size_t id) {
    try {
        taskRepo->deleteTaskById(id);
    } catch (...) {
        throw;
    }
}
