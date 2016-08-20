#pragma once

#include <string>

namespace Icyus
{
    namespace utils
    {
        constexpr uintmax_t operator"" KB(uintmax_t val)
        {
            return val * 1024;
        }
        
        constexpr uintmax_t operator"" MB(uintmax_t val)
        {
            return val * 1024KB;
        }

        constexpr uintmax_t operator"" GB(uintmax_t val)
        {
            return val * 1024MB;
        }

        constexpr uintmax_t operator"" TB(uintmax_t val)
        {
            return val * 1024GB;
        }

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