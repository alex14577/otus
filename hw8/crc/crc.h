/// @file crc.h
/// @brief Интерфейс для работы с контрольными суммами

#pragma once

#include <unistd.h>
#include <vector>
#include <stddef.h>
#include <cstdint>

namespace crc_alg
{

enum CrcAlg
{
    Undefined,
    Crc32,
    Md5
};

class Crc
{
public:
    virtual ~Crc() = default;
    virtual size_t GetCrc(const std::vector<uint8_t>& data) = 0;
};

class Crc32Calculator final : public Crc
{
public:
    Crc32Calculator() = default;
    ~Crc32Calculator() = default;
    size_t GetCrc(const std::vector<uint8_t>& data) override;
};

class CrcMd5Calculator final : public Crc
{
public:
    CrcMd5Calculator() = default;
    ~CrcMd5Calculator() = default;
    size_t GetCrc(const std::vector<uint8_t>& data) override;
};

} // namespace crc

