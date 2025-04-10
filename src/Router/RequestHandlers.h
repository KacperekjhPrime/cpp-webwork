#ifndef REQUESTHANDLERS_H
#define REQUESTHANDLERS_H
#include "../Request.h"
#include "../Response.h"

namespace webwork::routes {
    Response FileHandler(Request &request);
    Response DirectoryHandler(Request &request);
    Response ApiHandler(Request &request);
} // webwork::routes

#endif //REQUESTHANDLERS_H
