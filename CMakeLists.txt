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
        src/Parser/BasicToken.h
        src/Parser/Block.h
        src/Parser/Chunk.cpp
        src/Parser/Chunk.h
        src/Parser/Parser.cpp
        src/Parser/TokenTypeConstants.h
        src/Parser/Tree.h
        src/Parser/Thingamajig/Property.h
        src/Parser/Thingamajig/Scope.cxx
        src/Parser/Thingamajig/Scope.h
        src/Parser/Thingamajig/Thingamajig.cpp
        src/Parser/Thingamajig/Thingamajig.h
        src/Parser/Thingamajig/Token.cpp
        src/Parser/Thingamajig/Token.h
        src/Parser/Thingamajig/Tokens/For.cpp
        src/Parser/Thingamajig/Tokens/For.h
        src/Parser/Thingamajig/Tokens/If.cpp
        src/Parser/Thingamajig/Tokens/If.h
        src/Parser/Thingamajig/Tokens/Root.cpp
        src/Parser/Thingamajig/Tokens/Root.h
        src/Parser/Thingamajig/Tokens/Text.cpp
        src/Parser/Thingamajig/Tokens/Text.h
        src/Parser/Thingamajig/Tokens/Variable.cpp
        src/Parser/Thingamajig/Tokens/Variable.h
        src/Parser/Thingamajig/Properties/Array.cxx
        src/Parser/Thingamajig/Properties/Array.h
        src/Parser/Thingamajig/Properties/Boolean.cxx
        src/Parser/Thingamajig/Properties/Boolean.h
        src/Parser/Thingamajig/Properties/Number.cpp
        src/Parser/Thingamajig/Properties/Number.h
        src/Parser/Thingamajig/Properties/Object.cpp
        src/Parser/Thingamajig/Properties/Object.h
        src/Parser/Thingamajig/Properties/String.cxx
        src/Parser/Thingamajig/Properties/String.h
        src/Parser/Thingamajig/Properties/Interfaces/IBoolean.h
        src/Parser/Expression/Expression.cpp
        src/Parser/Expression/Expression.h
)

include_directories(cpp-webwork ${ASIO_INCLUDE_DIRS} ${MAGIC_INCLUDE_DIRS})
target_link_libraries(cpp-webwork ${ASIO_LIBRARIES} ${MAGIC_LIBRARIES})
message(${CMAKE_BUILD_TYPE})