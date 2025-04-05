cmake_minimum_required(VERSION 3.28.3)
project(cpp-webwork)

set(CMAKE_CXX_STANDARD 23)

find_package(cppzmq REQUIRED)

add_executable(cpp-webwork src/main.cpp
        src/Route.h
        src/Response.h
        src/Request.h
        src/Server/Server.h
        src/Server/ServerConfig.h
        src/Server/Server.cpp
        src/Request.h
        src/Logging.h
        src/Logging.cxx)

target_link_libraries(cpp-webwork cppzmq)
