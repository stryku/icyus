#pragma once

#include <string>

namespace Icyus
{
    namespace Communication
    {
        namespace TransferHeader
        {
            struct Header
            {
                using FileNameType = std::string;
                using FileSizeType = uintmax_t;

                FileNameType fileName;
                FileSizeType fileSize;
            };
        }
    }
}