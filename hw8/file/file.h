#pragma once

#include <crc/crc.h>

#include <stddef.h>
#include <string>
#include <filesystem>
#include <memory>

class File
{
public:
    File() = default;
    File(File&&) = default;
    File(size_t chunkSize, std::unique_ptr<crc_alg::Crc>&& crc);

    bool Open(const std::filesystem::path& f);

    /// @brief Получить crc от следующего куска файла.
    /// @return pair<bool, size_t, где:
    /// bool - true, если кусок последний, иначе - непоследний.
    /// size_t - crc от куска.
    std::pair<bool, size_t> GetChunk() const;

    struct FileCloser
    {
        void operator()(std::FILE* f);
    };
    
    std::filesystem::path GetPath() const;

private:
    std::unique_ptr<std::FILE, FileCloser>  f_;
    size_t chunkSize_;
    std::unique_ptr<crc_alg::Crc> crc_;
    std::filesystem::path path_;
};