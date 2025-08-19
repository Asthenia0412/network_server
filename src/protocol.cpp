#include "protocol.hpp"
#include <algorithm>

std::string process_message(const std::string& message) {
    std::string response = message;
    std::transform(response.begin(), response.end(), response.begin(), ::toupper);
    return response;
}