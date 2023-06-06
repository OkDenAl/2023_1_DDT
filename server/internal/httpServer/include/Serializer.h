#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_SERIALIZER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_SERIALIZER_H_

#include <string>
#include <utility>
#include <vector>

#include "Solution.hpp"
#include "Task.hpp"
#include "User.hpp"

class Serializer {
 public:
    std::tuple<std::size_t, std::size_t, std::string, std::string> deserialNewSolutionData(const std::string& val);
    std::tuple<std::size_t, std::size_t> deserialTaskData(const std::string& val);
    std::tuple<std::string, std::string, double> deserialNewTaskData(const std::string& val);
    size_t deserialSolutionData(const std::string& val);
    std::tuple<std::string, std::string> deserialUserData(const std::string& val);
    std::tuple<std::string, std::string, std::string> deserialNewUserData(const std::string& val);

    std::string serialSolutions(const std::vector<Solution>& solutions);
    std::string serialAllTasks(const std::vector<Task>& tasks);
    std::string serialUserData(const User& user);
    std::string serialSolution(const Solution& sol);
    std::string serialNewSolution(const Solution& sol, const Solution::Codes& codes);
    std::string serialTask(const Task& task);
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_SERIALIZER_H_
