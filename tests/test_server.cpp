#include <gtest/gtest.h>
#include "protocol.hpp"

TEST(ProtocolTest, ProcessMessage) {
EXPECT_EQ(process_message("hello"), "HELLO");
EXPECT_EQ(process_message("Test123"), "TEST123");
EXPECT_EQ(process_message(""), "");
}