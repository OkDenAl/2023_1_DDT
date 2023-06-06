#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_ITaskMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_ITaskMANAGER_H_

#include <boost/beast.hpp>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = boost::beast::http;

class ITaskManager {
 public:
    virtual http::message_generator createTask(http::request<http::string_body>&& req) = 0;
    virtual http::message_generator getAllTasks(http::request<http::string_body>&& req) = 0;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_ITaskMANAGER_H_
