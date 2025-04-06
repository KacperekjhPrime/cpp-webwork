#include "Mime.h"

#include <magic.h>
#include <format>

namespace webwork {
    struct Magic {
        magic_t magic;

        Magic() : magic(magic_open(MAGIC_MIME_TYPE)) {
            magic_load(magic, nullptr);
        }

        ~Magic() {
            magic_close(magic);
        }
    };

    const Magic magic = {};

    std::string_view GetFileMime(const std::filesystem::path &path) {
        if (!is_regular_file(path)) {
            throw std::runtime_error(std::format("{} does not exist or is not a file", path.string()));
        }
        const auto *mime = magic_file(magic.magic, path.generic_string().c_str());
        if (!mime) {
            throw std::runtime_error(std::format("Failed to get MIME type of {}: {}", path.string(), magic_error(magic.magic)));
        }
        return mime;
    }
}
