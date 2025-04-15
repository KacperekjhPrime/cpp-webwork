#ifndef HTTPEXCEPTION_H
#define HTTPEXCEPTION_H
#include <exception>
#include "StatusCodes.h"

namespace webwork {
    class HTTPException : public std::exception {
    public:
        StatusCode statusCode;

        HTTPException(StatusCode statusCode) : statusCode(statusCode) {}
    };
} // webwork

#endif //HTTPEXCEPTION_H
