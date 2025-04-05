#ifndef LOGGING_H
#define LOGGING_H
#include <format>
#include <string_view>

namespace webwork {
    enum class LogLevel {
        Info,
        Warning,
        Error
    };

    void Log(LogLevel level, std::string_view message);

    template <class ...T>
    void Log(LogLevel level, std::format_string<T...> message, T ...args) {
        Log(level, std::format(message, std::forward<T...>(args)...));
    }
}

#endif