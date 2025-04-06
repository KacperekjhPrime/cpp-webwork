#ifndef MIME_H
#define MIME_H

#include <string_view>
#include <filesystem>

namespace webwork {
    std::string_view GetFileMime(const std::filesystem::path &path);
}

#endif //MIME_H
