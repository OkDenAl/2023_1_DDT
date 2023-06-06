#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_ISolutionMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_ISolutionMANAGER_H_

#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = boost::beast::http;

class ISolutionManager {
 public:
    virtual http::message_generator getAllSolutions(http::request<http::string_body>&& req) = 0;
    virtual http::message_generator createSolution(http::request<http::string_body>&& req) = 0;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_ISolutionMANAGER_H_
