#ifndef APP_HTTPCLIENT_HTTPCLIENT_IHTTPCLIENT_H_
#define APP_HTTPCLIENT_HTTPCLIENT_IHTTPCLIENT_H_

#include <utility>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class IHttpClient {
public:
    virtual http::response<http::dynamic_body> makeGetRequest(std::string_view target, std::string_view body) = 0;
    virtual http::response<http::dynamic_body> makePostRequest(std::string_view target, std::string_view body) = 0;

protected:
    virtual http::response<http::dynamic_body> makeRequest(std::string_view target,
                                                   http::verb method,
                                                   std::string_view body) = 0;
};


#endif  // APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_
