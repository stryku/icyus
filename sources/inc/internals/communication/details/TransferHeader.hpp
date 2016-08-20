#pragma once

#include <string>

namespace Icyus
{
    namespace Communication
    {
        struct TransferHeader
        {
            using FileNameType = std::string;
            using FileSizeType = uintmax_t;

            FileNameType fileName;
            FileSizeType fileSize;
        };
    }
}