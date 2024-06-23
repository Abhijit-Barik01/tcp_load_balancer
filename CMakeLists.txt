cmake_minimum_required(VERSION 3.10)
project(tcp_load_balancer)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(tcp_load_balancer
    src/Client.cpp
    src/Server.cpp
    src/LoadBalancer.cpp
    src/main.cpp
)
