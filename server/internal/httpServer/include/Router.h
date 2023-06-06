#ifndef SOURCEDOUT_HTTPSERVER_ROUTER_UTILS_H
#define SOURCEDOUT_HTTPSERVER_ROUTER_UTILS_H

#include <boost/beast.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

#include "SolutionManager.h"
#include "TaskManager.h"
#include "UserManager.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

class Router : public std::enable_shared_from_this<Router> {
 public:
    explicit Router(std::string_view doc_root_);

    http::message_generator handleRequest(http::request<http::string_body>&& req);

    void setSolutionManager(std::shared_ptr<ISolutionManager> mng) { solutionManager = mng; }
    void setUserManager(std::shared_ptr<IUserManager> mng) { userManager = mng; }
    void setTaskManager(std::shared_ptr<ITaskManager> mng) { taskManager = mng; }

 private:
    std::shared_ptr<ISolutionManager> solutionManager;
    std::shared_ptr<IUserManager> userManager;
    std::shared_ptr<ITaskManager> taskManager;
    std::string doc_root;
};

#endif  // SOURCEDOUT_HTTPSERVER_ROUTER_UTILS_H
