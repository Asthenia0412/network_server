cmake_minimum_required(VERSION 3.10)
project(NetworkServer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
        src/main.cpp
        src/server.cpp
        src/protocol.cpp
)

add_executable(server ${SOURCES})

find_package(Boost 1.71 REQUIRED COMPONENTS system asio)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(server PRIVATE ${Boost_LIBRARIES})
endif()

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
        tests/test_server.cpp
        src/server.cpp
        src/protocol.cpp
)

add_executable(test_server ${TEST_SOURCES})
target_link_libraries(test_server PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${Boost_LIBRARIES})

add_test(NAME ServerTest COMMAND test_server)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-instr-generate")
endif()

add_custom_target(coverage
        COMMAND ${CMAKE_BINARY_DIR}/bin/test_server
        COMMAND llvm-profdata merge -sparse default.profraw -o coverage.profdata
        COMMAND llvm-cov export ${CMAKE_BINARY_DIR}/bin/test_server -instr-profile=coverage.profdata -format=json > coverage.json
        DEPENDS test_server
)