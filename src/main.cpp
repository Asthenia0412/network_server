#include "server.hpp"
#include <iostream>

int main() {
    try {
        Server server(8080); // 启动服务器，监听 8080 端口
        std::cout << "Server running on port 8080...\n";
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}