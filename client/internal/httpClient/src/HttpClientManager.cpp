#include "HttpClientManager.h"

#include <memory>
#include <string>
#include <vector>

#include "HttpClient.h"

HttpClientManager::HttpClientManager(std::string_view host_, std::string_view port_)
    : host(host_),
      port(port_),
      client(std::make_shared<HttpClient>(host_, port_)),
      serializer(std::make_shared<Serializer>()) {}

std::pair<unsigned, User> HttpClientManager::loginUser(const std::string &login, const std::string &password) {
    std::string body = serializer->serialLoginData(login, password);
    http::response<http::dynamic_body> res = client->makeGetRequest("/user/login", body);
    unsigned status = res.result_int();
    std::string res_body;
    for (auto seq : res.body().data()) {
        auto *cbuf = boost::asio::buffer_cast<const char *>(seq);
        res_body.append(cbuf, boost::asio::buffer_size(seq));
    }
    User user{0, "", "", ""};
    if (status == 200) user = serializer->deserialUserData(res_body);
    return {status, user};
}

std::pair<unsigned, User> HttpClientManager::registerUser(const std::string &login, const std::string &username,
                                                          const std::string &password) {
    std::string body = serializer->serialRegisterData(login, username, password);
    http::response<http::dynamic_body> res = client->makeGetRequest("/user/register", body);
    unsigned status = res.result_int();
    std::string res_body;
    for (auto seq : res.body().data()) {
        auto *cbuf = boost::asio::buffer_cast<const char *>(seq);
        res_body.append(cbuf, boost::asio::buffer_size(seq));
    }
    User user;
    if (status == 200) {
        user = serializer->deserialUserData(res_body);
    }
    return {status, user};
}

std::pair<Solution, Solution::Codes> HttpClientManager::submitSolution(const int &user_id, const int &task_id,
                                                                       const std::string &filename,
                                                                       const std::string &path_to_sound) {
    std::string body = serializer->serialSolutionData(user_id, task_id, filename, path_to_sound);
    http::response<http::dynamic_body> res = client->makeGetRequest("/solution/submit", body);
    std::cout << res << std::endl;
    // unsigned status = res.result_int();
    std::string res_body;
    for (auto seq : res.body().data()) {
        auto *cbuf = boost::asio::buffer_cast<const char *>(seq);
        res_body.append(cbuf, boost::asio::buffer_size(seq));
    }
    Solution sol;
    Solution::Codes codes;
    std::tie(sol, codes) = serializer->deserialNewSolutionData(res_body);
    return {sol, codes};
}

unsigned int HttpClientManager::getAllSolutionsForTask(const int &user_id, const int &task_id) { return 0; }

void HttpClientManager::setHttpClient(std::shared_ptr<IHttpClient> client_) { client = client_; }

std::vector<Task> HttpClientManager::getAllTasks() {
    http::response<http::dynamic_body> res = client->makeGetRequest("/task/all", "");
    std::string res_body;
    for (auto seq : res.body().data()) {
        auto *cbuf = boost::asio::buffer_cast<const char *>(seq);
        res_body.append(cbuf, boost::asio::buffer_size(seq));
    }
    std::vector<Task> tasks = serializer->deserialAllTasks(res_body);
    return tasks;
}

unsigned int HttpClientManager::createTask(const std::string &name, const std::string &desc, const double &threshold) {
    std::string body = serializer->serialNewTaskData(name, desc, threshold);
    http::response<http::dynamic_body> res = client->makeGetRequest("/task/create", body);
    unsigned int result = res.result_int();
    return result;
}
