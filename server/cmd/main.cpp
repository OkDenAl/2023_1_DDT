#include <boost/asio.hpp>
#include <iostream>

#include "HttpServer.h"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    // Check command line arguments.
    //    if (argc != 5)
    //    {
    //        std::cerr <<
    //                  "Usage: http-server-async <address> <port> <doc_root> <threads>\n" <<
    //                  "Example:\n" <<
    //                  "    http-server-async 0.0.0.0 8080 . 1\n";
    //        return EXIT_FAILURE;
    //    }
    std::cout << "SERVER RUN12" << std::endl;
    auto const address = net::ip::make_address("0.0.0.0");
    auto const port = static_cast<unsigned short>(std::atoi("8080"));
    auto const doc_root = std::make_shared<std::string>(".");
    auto const threads = std::max<int>(1, std::atoi("1"));

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    // Create and launch a listening port
    std::make_shared<HttpServer>(ioc, tcp::endpoint{address, port}, doc_root)->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for (auto i = threads - 1; i > 0; --i) v.emplace_back([&ioc] { ioc.run(); });
    ioc.run();

    return EXIT_SUCCESS;
}
