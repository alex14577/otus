/// @file file_sender.h.
/// @brief Реализация интерфейса писателя в файл.

#pragma once

#include <sender/sender.h>

#include <memory>
#include <filesystem>

class Bulk;

class FileSender final : public Sender
{

public:
    FileSender(const std::shared_ptr<Bulk>& bulk, const std::filesystem::path& path);
    ~FileSender() = default;

    void Update() override;

private:
    std::shared_ptr<Bulk> bulk_;
    std::filesystem::path pathOut_;
};