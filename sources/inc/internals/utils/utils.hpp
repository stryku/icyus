#pragma once

#include <internals/utils/TestClass.hpp>

#include <string>
#include <type_traits>

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

        std::string formatSize(uintmax_t size);
    }
}