#ifndef APP_HTTPSERVER_HTTPSERVER_MANAGERS_IUserMANAGER_H_
#define APP_HTTPSERVER_HTTPSERVER_MANAGERS_IUserMANAGER_H_

#include <boost/beast.hpp>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = boost::beast::http;

class IUserManager {
 public:
    virtual http::message_generator loginUser(http::request<http::string_body>&& req) = 0;
    virtual http::message_generator registerUser(http::request<http::string_body>&& req) = 0;
};

#endif  // APP_HTTPSERVER_HTTPSERVER_MANAGERS_IUserMANAGER_H_
