#pragma once

#include <string>

namespace Icyus
{
    namespace utils
    {
        template <typename T>
        constexpr long double operator"" KB(T val)
        {
            return val * 1024;
        }
        
        template <typename T>
        constexpr long double operator"" MB(T val)
        {
            return val * 1KB;
        }

        template <typename T>
        constexpr long double operator"" GB(T val)
        {
            return val * 1MB;
        }

        template <typename T>
        constexpr long double operator"" TB(T val)
        {
            return val * 1GB;
        }

        template <typename Size>
        std::string formatSize(Size size)
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