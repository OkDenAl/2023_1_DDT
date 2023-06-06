#include "HttpServer.h"

#include <boost/bind.hpp>
#include <vector>

#include "Utils.h"

HttpServer::HttpServer(net::io_context& io_context_, tcp::endpoint endpoint_,
                       std::shared_ptr<std::string const> const& doc_root_)
    : io_context(io_context_), acceptor(net::make_strand(io_context_)), doc_root(doc_root_) {
    beast::error_code ec;
    acceptor.open(endpoint_.protocol(), ec);
    if (ec) {
        fail(ec, "open");
        return;
    }

    acceptor.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
        fail(ec, "set_option");
        return;
    }

    acceptor.bind(endpoint_, ec);
    if (ec) {
        fail(ec, "bind");
        return;
    }

    acceptor.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
        fail(ec, "listen");
        return;
    }
}

void HttpServer::run() { startAccept(); }

void HttpServer::startAccept() {
    acceptor.async_accept(net::make_strand(io_context),
                          beast::bind_front_handler(&HttpServer::handleAccept, shared_from_this()));
}

void HttpServer::handleAccept(beast::error_code ec, tcp::socket socket) {
    if (ec) {
        fail(ec, "accept");
        return;
    } else {
        std::make_shared<HttpConnection>(std::move(socket), doc_root)->run();
    }

    startAccept();
}
