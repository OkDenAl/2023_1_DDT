#include "Utils.h"

void fail(beast::error_code ec, const char* what) { std::cerr << what << ": " << ec.message() << "\n"; }

http::response<http::string_body> getBadRequest(const http::request<http::string_body>& request,
                                                beast::string_view why) {
    http::response<http::string_body> res{http::status::bad_request, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(request.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
}

http::response<http::string_body> getInternalServerError(const http::request<http::string_body>& request,
                                                         beast::string_view why) {
    http::response<http::string_body> res{http::status::internal_server_error, request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(request.keep_alive());
    res.body() = std::string(why);
    res.prepare_payload();
    return res;
}
