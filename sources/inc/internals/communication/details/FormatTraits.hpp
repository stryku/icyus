#pragma once

#include <type_traits>

namespace Icyus
{
    namespace Communication
    {
        namespace detail
        {
            namespace TransferHeader
            {
                namespace Formats
                {
                    struct Xml {};
                }

                template <typename T>
                constexpr bool isXmlFormat = std::is_same<T, Formats::Xml>::value;
            }
        }
    }
}