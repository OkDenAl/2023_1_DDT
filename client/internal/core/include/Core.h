#pragma once

#include <string>
#include <vector>

#include "Task.h"
#include "Solution.h"

class Core {
public:
    static unsigned signUp(const std::string &login, const std::string &username, const std::string &pass);

    static unsigned login(const std::string &login, const std::string &pass);

    static std::vector<Task> getAllTasks();

    static std::pair<Solution, Solution::Codes> submitSolution(const int& task_id, const std::string& filename, const std::string& path_to_file);

    static unsigned int createTask(const std::string& name, const std::string &desc,
                                   const double& threshold);

    static void logout();

private:
    static std::size_t user_id;
};
