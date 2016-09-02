#include <internals/utils/utils.hpp>

namespace Icyus
{
    namespace utils
    {
        std::string formatSize(uintmax_t size)
        {
            const char *suffix;

            if (size < 1KB)
                suffix = "B";
            else if (size < 1MB)
            {
                size /= 1KB;
                suffix = "KB";
            }
            else if (size < 1GB)
            {
                size /= 1MB;
                suffix = "MB";
            }
            else if (size < 1TB)
            {
                size /= 1GB;
                suffix = "GB";
            }
            else
            {
                size /= 1TB;
                suffix = "TB";
            }

            return std::to_string(size) + suffix;
        }
    }
}