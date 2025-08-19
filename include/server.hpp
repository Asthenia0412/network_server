#pragma once
#include <boost/asio.hpp>
#include <string>

class Server {
public:
    Server(unsigned short port);
    void run();

private:
    void start_accept();
    void handle_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};