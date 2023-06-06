#ifndef SOURCEDOUT_HTTPSERVER_HTTPSERVER_H
#define SOURCEDOUT_HTTPSERVER_HTTPSERVER_H

#include <boost/asio.hpp>
#include <string>
#include <vector>

#include "HttpConnection.h"
#include "Router.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HttpServer : public std::enable_shared_from_this<HttpServer> {
 public:
    HttpServer(net::io_context& io_context_, tcp::endpoint endpoint_,
               std::shared_ptr<std::string const> const& doc_root_);
    void run();

 private:
    void startAccept();
    void handleAccept(beast::error_code ec, tcp::socket socket);

    net::io_context& io_context;
    tcp::acceptor acceptor;
    std::shared_ptr<std::string const> doc_root;
};

#endif  // SOURCEDOUT_HTTPSERVER_HTTPSERVER_H
