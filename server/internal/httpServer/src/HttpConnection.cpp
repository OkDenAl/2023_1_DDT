#include "HttpConnection.h"

#include <boost/bind.hpp>

#include "Utils.h"

HttpConnection::HttpConnection(tcp::socket&& socket_, std::shared_ptr<std::string const> const& doc_root_)
    : stream(std::move(socket_)), doc_root(doc_root_) {
    router = std::make_shared<Router>(*doc_root_);
}

void HttpConnection::run() {
    net::dispatch(stream.get_executor(), beast::bind_front_handler(&HttpConnection::read, shared_from_this()));
}

void HttpConnection::read() {
    request = {};
    stream.expires_after(std::chrono::seconds(30));
    http::async_read(stream, buffer, request,
                     beast::bind_front_handler(&HttpConnection::handleRead, shared_from_this()));
}

void HttpConnection::handleRead(beast::error_code e, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (e == http::error::end_of_stream) return close();

    if (e) return fail(e, "read");

    sendResponse(router->handleRequest(std::move(request)));
}

void HttpConnection::sendResponse(http::message_generator&& msg) {
    bool keep_alive = msg.keep_alive();

    beast::async_write(stream, std::move(msg),
                       beast::bind_front_handler(&HttpConnection::handleWrite, shared_from_this(), keep_alive));
}

void HttpConnection::handleWrite(bool keep_alive, beast::error_code e, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (e) return fail(e, "write");

    if (!keep_alive) {
        return close();
    }

    read();
}

void HttpConnection::close() {
    beast::error_code e;
    stream.socket().shutdown(tcp::socket::shutdown_send, e);
}
