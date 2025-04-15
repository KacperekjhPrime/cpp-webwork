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
        src/Parser/Expression/Expression.cpp
        src/Parser/Expression/Expression.h
        src/Parser/Expression/Token.h
        src/Parser/Expression/Tokens/Operators/NumericBinaryOperator.h
        src/Helper.h
        src/Parser/Expression/Tokens/Operators/BinaryOperators.h
        src/Parser/Expression/Tokens/Operators/BinaryOperators.cxx
        src/Parser/Expression/Tokens/Variable.cxx
        src/Parser/Expression/Tokens/Variable.h
        src/Parser/Expression/Tokens/Parenthesis.cxx
        src/Parser/Expression/Tokens/Number.cxx
        src/Parser/Expression/Tokens/Number.h
        src/Parser/Thingamajig/Tokens/Expression.cxx
        src/Parser/Thingamajig/Tokens/Expression.h
        src/Parser/Thingamajig/Tokens/BlockBase.cpp
        src/Parser/Thingamajig/Tokens/BlockBase.h
        src/Parser/Expression/Tokens/Interfaces/IBinaryOperator.h
        src/Parser/Expression/Tokens/Interfaces/IUnaryOperator.h
        src/Parser/Expression/Tokens/Interfaces/IEvaluable.h
        src/Parser/Expression/Tokens/Operators/SubtractionOperator.cpp
        src/Parser/Expression/Tokens/Operators/SubtractionOperator.h
        src/Parser/Expression/Tokens/Operators/BoolBinaryOperator.h
        src/Parser/Expression/Tokens/Operators/LogicNegationOperator.cxx
        src/Parser/Expression/Tokens/Operators/LogicNegationOperator.h
        src/Parser/Expression/Tokens/Boolean.cxx
        src/Parser/Expression/Tokens/Boolean.h
        src/Parser/Expression/Tokens/Function.cxx
        src/Parser/Expression/Tokens/Function.h
        src/Parser/Expression/Tokens/Comma.h
        src/Parser/Expression/Tokens/Comma.cxx
        src/Mime.cpp
        src/Server/Server.h
        src/Server/Server.cpp
        src/StatusCodes.h
        src/URL.cpp
        src/URL.h
        src/Helper.cpp
        src/Helper.h
        src/Response.cpp
        src/HTTPException.h
        src/Properties/Scope.cxx
        src/Properties/Scope.h
        src/Properties/Interfaces/IBoolean.cxx
        src/Properties/Interfaces/INumber.cxx
        src/Properties/Interfaces/IString.cxx
        src/Properties/Array.cxx
        src/Properties/Boolean.cxx
        src/Properties/Function.cxx
        src/Properties/Number.cpp
        src/Properties/Object.cpp
        src/Properties/String.cxx
        src/Parser/Thingamajig/Tokens/Component.h
        src/Parser/Thingamajig/Tokens/Component.cxx
)

include_directories(cpp-webwork ${ASIO_INCLUDE_DIRS} ${MAGIC_INCLUDE_DIRS})
target_link_libraries(cpp-webwork ${ASIO_LIBRARIES} ${MAGIC_LIBRARIES})
message(${CMAKE_BUILD_TYPE})