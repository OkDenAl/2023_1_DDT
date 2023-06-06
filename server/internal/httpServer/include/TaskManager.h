#pragma once

#include <memory>
#include <string>

#include "ITaskManager.h"
#include "Serializer.h"
#include "TaskService.h"

class TaskManager : public ITaskManager {
 public:
    TaskManager();
    http::message_generator createTask(http::request<http::string_body>&& req) override;
    http::message_generator getAllTasks(http::request<http::string_body>&& req) override;
    void setService(std::shared_ptr<ITaskService> service);

 private:
    std::shared_ptr<ITaskService> taskService;
    std::shared_ptr<Serializer> serializer;
};
