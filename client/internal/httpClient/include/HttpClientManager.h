#ifndef APP_HTTPCLIENT_HTTPCLIENTMANAGER_HTTPCLIENTMANAGER_H_
#define APP_HTTPCLIENT_HTTPCLIENTMANAGER_HTTPCLIENTMANAGER_H_

#include <string>
#include <vector>
#include <utility>

#include "IHttpClient.h"
#include "User.h"
#include "Solution.h"
#include "Task.h"
#include "Metric.h"
#include "Serializer.h"

class HttpClientManager {
public:
    HttpClientManager(std::string_view host_, std::string_view port_);

    std::pair<unsigned, User> loginUser(const std::string &login, const std::string &password);
    std::pair<unsigned, User> registerUser(const std::string &login, const std::string &username,
                                           const std::string &password);
    std::pair<Solution, Solution::Codes> submitSolution(const int& user_id, const int &task_id, const std::string& filename,
                            const std::string &path_to_solution);
    unsigned int getAllSolutionsForTask(const int& user_id, const int& task_id);
    std::vector<Task> getAllTasks();
    unsigned int createTask(const std::string& name, const std::string &desc,
                            const double& threshold);
    void setHttpClient(std::shared_ptr<IHttpClient> client_);
private:
    std::string host;
    std::string port;
    std::shared_ptr<IHttpClient> client;
    std::shared_ptr<Serializer> serializer;
};


#endif  // APP_HTTPCLIENT_HTTPCLIENTMANAGER_HTTPCLIENTMANAGER_H_
