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

pkg_check_modules(ASIO "asio" REQUIRED)
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
        src/Mime.cpp
        src/Thingamajig/Parser/Parser.h
        src/Thingamajig/Parser/Parser.cpp
        src/Thingamajig/Token.h
        src/Thingamajig/Parser/BasicToken.h
        src/Thingamajig/Parser/TokenTree.h
        src/Thingamajig/Parser/TokenTree.cpp
        src/Thingamajig/Tokens/Variable.cpp
        src/Thingamajig/Tokens/Variable.h
        src/Thingamajig/Tokens/Text.cpp
        src/Thingamajig/Tokens/Text.h
        src/Thingamajig/Block.h
        src/Thingamajig/Tokens/If.cpp
        src/Thingamajig/Tokens/If.h
        src/Thingamajig/Tokens/For.cpp
        src/Thingamajig/Tokens/For.h
        src/Thingamajig/Tokens/Root.cpp
        src/Thingamajig/Tokens/Root.h
        src/Thingamajig/Parser/TokenMergeRules.h
        src/Thingamajig/Parser/TokenMergeRules.cpp
        src/Thingamajig/Block.cpp
        src/Thingamajig/Token.cpp
        src/Thingamajig/Property.h
        src/Thingamajig/Properties/Object.h
        src/Thingamajig/Properties/Object.cpp
        src/Thingamajig/Properties/Number.h
        src/Thingamajig/Properties/Number.cpp
        src/Thingamajig/Properties/Text.h
        src/Thingamajig/Properties/Text.cxx
        src/Thingamajig/Properties/Array.cxx
        src/Thingamajig/Properties/Array.h
        src/Thingamajig/Scope.cxx
        src/Thingamajig/Scope.h
)

include_directories(cpp-webwork ${ASIO_INCLUDE_DIRS} ${MAGIC_INCLUDE_DIRS})
target_link_libraries(cpp-webwork ${ASIO_LIBRARIES} ${MAGIC_LIBRARIES})
message(${CMAKE_BUILD_TYPE})