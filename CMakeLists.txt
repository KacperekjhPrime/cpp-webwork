cmake_minimum_required(VERSION 3.28.3)
project(cpp-webwork)

set(CMAKE_CXX_STANDARD 23)

if (${CMAKE_BUILD_TYPE} STREQUAL "Windows")
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_C_COMPILER   x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
endif ()

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
set(CMAKE_CXX_FLAGS "-Wall -g")

pkg_check_modules(CPPZMQ "cppzmq" REQUIRED)
pkg_check_modules(MAGIC "libmagic" REQUIRED)

add_executable(cpp-webwork src/main.cpp
        src/Route.h
        src/Response.h
        src/Request.h
        src/Logging.h
        src/Logging.cxx
        src/Loading/Loader.h
        src/Loading/Loader.cpp
        src/Loading/Module.h
        src/Mime.h
        src/Mime.cpp)

include_directories(cpp-webwork ${CPPZMQ_INCLUDE_DIRS} ${MAGIC_INCLUDE_DIRS})
target_link_libraries(cpp-webwork ${CPPZMQ_LIBRARIES} ${MAGIC_LIBRARIES})
message(${CMAKE_BUILD_TYPE})