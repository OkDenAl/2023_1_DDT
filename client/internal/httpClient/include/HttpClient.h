#ifndef APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_
#define APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_

#include <utility>
#include <memory>
#include <string>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "IHttpClient.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class HttpClient : public IHttpClient {
public:
    HttpClient(std::string_view host_, std::string_view port_);
    http::response<http::dynamic_body> makeGetRequest(std::string_view target, std::string_view body) override;
    http::response<http::dynamic_body> makePostRequest(std::string_view target, std::string_view body) override;

private:
    http::response<http::dynamic_body> makeRequest(std::string_view target,
                                                   http::verb method,
                                                   std::string_view body) override;

    net::io_context io_context{};
    tcp::resolver resolver;
    beast::tcp_stream stream;
    std::string host;
    std::string port;
    std::mutex mutex;
};


#endif  // APP_HTTPCLIENT_HTTPCLIENT_HTTPCLIENT_H_
