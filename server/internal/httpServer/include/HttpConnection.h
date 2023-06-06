#ifndef SOURCEDOUT_HTTPSERVER_HTTPCONNECTION_H
#define SOURCEDOUT_HTTPSERVER_HTTPCONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/noncopyable.hpp>

#include "Router.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HttpConnection : public std::enable_shared_from_this<HttpConnection> {
 public:
    explicit HttpConnection(tcp::socket&& socket_, std::shared_ptr<std::string const> const& doc_root_);
    void run();
    void read();
    void handleRead(beast::error_code e, std::size_t bytes_transferred);
    void sendResponse(http::message_generator&& msg);
    void handleWrite(bool keep_alive, beast::error_code e, std::size_t bytes_transferred);
    void close();

 private:
    beast::tcp_stream stream;
    beast::flat_buffer buffer;
    std::shared_ptr<std::string const> doc_root;
    http::request<http::string_body> request;
    std::shared_ptr<Router> router;
};

#endif  // SOURCEDOUT_HTTPSERVER_HTTPCONNECTION_H
