#include "server.hpp"
#include "protocol.hpp"
#include <iostream>

Server::Server(unsigned short port)
        : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    start_accept();
}

void Server::run() {
    io_context_.run();
}

void Server::start_accept() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& error) {
        if (!error) {
            handle_connection(socket);
        }
        start_accept();
    });
}

void Server::handle_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    auto buffer = std::make_shared<std::array<char, 1024>>();
    socket->async_read_some(
            boost::asio::buffer(*buffer),
            [this, socket, buffer](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    std::string message(buffer->data(), bytes_transferred);
                    std::string response = process_message(message);
                    boost::asio::async_write(
                            *socket,
                            boost::asio::buffer(response),
                            [](const boost::system::error_code&, std::size_t) {});
                }
            });
}