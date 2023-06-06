#ifndef SOURCEDOUT_TASKREPOSITORY_HPP
#define SOURCEDOUT_TASKREPOSITORY_HPP

#include <boost/format.hpp>
#include <fstream>
#include <optional>

#include "ITaskRepository.hpp"
#include "dbManager.hpp"
#include "pqxx/pqxx"

using namespace pqxx;

class TaskRepository : public ITaskRepository {
 public:
    TaskRepository();

    std::optional<Task> getTaskById(size_t id) override;

    std::vector<Task> getAllTasks() override;

    void updateTask(const Task &task) override;

    size_t storeTask(Task task) override;

    void deleteTask(Task task) override;

    void deleteTaskById(size_t task_id) override;

 private:
    static Task makeTask(const result::const_iterator &c);

    std::shared_ptr<dbManager> manager;
};

#endif  // SOURCEDOUT_TASKREPOSITORY_HPP
