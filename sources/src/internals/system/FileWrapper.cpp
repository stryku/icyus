#include "internals/system/FileWrapper.hpp"

namespace Icyus
{
    namespace System
    {
        FileWrapper::FileWrapper(const std::experimental::filesystem::path &path) :
            file{ path },
            path{ path }
        {}

        uintmax_t FileWrapper::size() const
        {
            return std::experimental::filesystem::file_size(path);
        }

        std::streamsize FileWrapper::read(void *dest, std::streamsize size)
        {
            return file.readsome(static_cast<char*>(dest), size);
        }

        void FileWrapper::write(const void *src, std::streamsize size)
        {
            file.write(static_cast<const char*>(src), size);
        }

        std::streamsize FileWrapper::lastReadCount() const
        {
            return file.gcount();
        }

        std::string FileWrapper::name() const
        {
            return path.string();
        }
    }
}