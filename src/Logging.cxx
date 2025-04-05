#include "Logging.h"

#include <iostream>

namespace webwork {
    void Log(LogLevel level, std::string_view message) {
        std::string_view prefix;
        switch (level) {
            case LogLevel::Info:
                prefix = "\033[1m[INFO]";
                break;
            case LogLevel::Warning:
                prefix = "\033[93m[WARNING]";
                break;
            case LogLevel::Error:
                prefix = "\033[31m[ERROR]";
                break;
            default:
                prefix = "[UNKNOWN]";
                break;
        }

        std::cout << prefix << "\033[0m " << message << std::endl;
    }
}
