#pragma once

#include <vector>
#include <memory>
#include <string>
#include "User.h"
#include "Task.h"
#include "Solution.h"

class Serializer {
public:
    std::string serialLoginData(std::string_view login, std::string_view password);
    std::string serialRegisterData(std::string_view login, std::string_view username, std::string_view password);
    std::string serialSolutionData(const int& user_id, const int& task_id, const std::string& filename,
                                   const std::string& path_to_file);
    std::string serialNewTaskData(std::string_view name, std::string_view desc, double threshold);

    User deserialUserData(std::string_view body);
    Solution deserialSolutionData(std::string_view body);
    std::pair<Solution, Solution::Codes> deserialNewSolutionData(std::string_view body);
    std::vector<Task> deserialAllTasks(std::string_view body);
};

