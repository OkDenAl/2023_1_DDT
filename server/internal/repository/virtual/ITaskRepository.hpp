#ifndef SOURCEDOUT_ITASKREPOSITORY_HPP
#define SOURCEDOUT_ITASKREPOSITORY_HPP

#include <iostream>
#include <optional>
#include <vector>

#include "Task.hpp"

class ITaskRepository {
 public:
    virtual ~ITaskRepository() = default;

    virtual std::optional<Task> getTaskById(size_t id) = 0;

    virtual std::vector<Task> getAllTasks() = 0;

    virtual void updateTask(const Task& task) = 0;

    virtual size_t storeTask(Task task) = 0;

    virtual void deleteTask(Task task) = 0;

    virtual void deleteTaskById(size_t task_id) = 0;
};

#endif  // SOURCEDOUT_ITASKREPOSITORY_HPP
