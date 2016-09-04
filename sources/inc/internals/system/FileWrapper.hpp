#pragma once

#include <fstream>
#include <experimental/filesystem>

namespace Icyus
{
    namespace System
    {
        class FileWrapper
        {
        public:
            FileWrapper(const std::experimental::filesystem::path &path) :
                file{ path },
                path{ path }
            {}

            FileWrapper(FileWrapper&&) = default;
            FileWrapper& operator=(FileWrapper&&) = default;

            auto size() const
            {
                return std::experimental::filesystem::file_size(path);
            }

            auto read(void *dest, std::streamsize size)
            {
                return file.readsome(static_cast<char*>(dest), size);
            }

            void write(const void *src, std::streamsize size)
            {
                file.write(static_cast<const char*>(src), size);
            }

            auto lastReadCount() const
            {
                return file.gcount();
            }

            auto name() const
            {
                return path.c_str();
            }

        private:
            std::fstream file;
            std::experimental::filesystem::path path;
        };
    }
}