cmake_minimum_required(VERSION 3.30.5)
project(cpp-webwork)

set(CMAKE_CXX_STANDARD 23)

find_package(cppzmq REQUIRED)

add_executable(cpp-webwork src/main.cpp
        src/Route.h
        src/Response.cxx
        src/Response.h
        src/Request.cxx
        src/Request.h
        src/Request.cxx
        src/Request.h)

target_link_libraries(cpp-webwork cppzmq)
