#include "Router.h"

#include <iostream>
#include <string>

#include "Utils.h"

Router::Router(std::string_view doc_root_)
    : solutionManager(std::make_shared<SolutionManager>()),
      userManager(std::make_shared<UserManager>()),
      taskManager(std::make_shared<TaskManager>()),
      doc_root(doc_root_) {}

http::message_generator Router::handleRequest(http::request<http::string_body> &&req) {
    if (req.method() != http::verb::get && req.method() != http::verb::post)
        return getBadRequest(req, "Unknown HTTP-method");

    if (req.target().empty() || req.target()[0] != '/' || req.target().find("..") != beast::string_view::npos) {
        return getBadRequest(req, "Illegal request-target");
    }

    if (req.target() == "/solution/submit") {
        return solutionManager->createSolution(std::move(req));
    } else if (req.target() == "/solution/all") {
        return solutionManager->getAllSolutions(std::move(req));
    } else if (req.target() == "/user/register") {
        return userManager->registerUser(std::move(req));
    } else if (req.target() == "/user/login") {
        return userManager->loginUser(std::move(req));
    } else if (req.target() == "/task/create") {
        return taskManager->createTask(std::move(req));
    } else if (req.target() == "/task/all") {
        return taskManager->getAllTasks(std::move(req));
    }

    return getBadRequest(req, "Unknown request-target");
}
