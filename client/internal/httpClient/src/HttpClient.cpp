#include "httpClient.h"

#include <string>
#include <boost/system/error_code.hpp>

HttpClient::HttpClient(std::string_view host_, std::string_view port_) :
        host(host_),
        port(port_),
        resolver(io_context),
        stream(io_context) {}

http::response<http::dynamic_body> HttpClient::makeRequest(std::string_view target,
                                                           http::verb method,
                                                           std::string_view body) {
    tcp::resolver::results_type results;
    {
        std::lock_guard _{mutex};
        results = resolver.resolve(host, port);
    }
    stream.connect(results);
    http::request<http::string_body> req{http::verb::get, target, 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set(http::field::content_type, "text/plain");
    req.content_length(body.size());
    req.body() = body;

    http::write(stream, req);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(stream, buffer, res);

    return res;
}

http::response<http::dynamic_body> HttpClient::makeGetRequest(std::string_view target,
                                          std::string_view body) {
    return makeRequest(target, http::verb::get, body);
}

http::response<http::dynamic_body> HttpClient::makePostRequest(std::string_view target,
                                           std::string_view body) {
    return makeRequest(target, http::verb::post, body);
}
