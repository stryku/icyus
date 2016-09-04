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
            FileWrapper(const std::experimental::filesystem::path &path);

            FileWrapper(FileWrapper&&) = default;
            FileWrapper& operator=(FileWrapper&&) = default;

            uintmax_t size() const;
            std::streamsize read(void *dest, std::streamsize size);
            void write(const void *src, std::streamsize size);
            std::streamsize lastReadCount() const;
            std::string name() const;

        private:
            std::fstream file;
            std::experimental::filesystem::path path;
        };
    }
}