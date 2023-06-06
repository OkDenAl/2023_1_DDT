#pragma once

#include <boost/beast.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;

void fail(beast::error_code ec, char const* what);

http::response<http::string_body> getBadRequest(const http::request<http::string_body>& request,
                                                beast::string_view why);

http::response<http::string_body> getInternalServerError(const http::request<http::string_body>& request,
                                                         beast::string_view why);