#pragma once

#include <string>

namespace Icyus
{
    namespace Communication
    {
        namespace detail
        {
            namespace TransferHeader
            {
                struct Header
                {
                    using FileNameType = std::string;
                    using FileSizeType = uintmax_t;

                    Header() = default;
                    Header(const FileNameType &fileName, const FileSizeType fileSize) :
                        fileName{ fileName },
                        fileSize{ fileSize }
                    {}

                    FileNameType fileName;
                    FileSizeType fileSize;
                };
            }
        }
    }
}