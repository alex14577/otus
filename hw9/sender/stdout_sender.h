/// @file file_sender.h.
/// @brief Реализация интерфейса писателя в файл.

#pragma once

#include <sender/sender.h>

#include <memory>

class Bulk;

class StdOutSender final : public Sender
{
public:
    StdOutSender(const std::shared_ptr<Bulk>& bulk);
    ~StdOutSender() = default;

    void Update() override;
    Target GetTarget() const noexcept;

private:
    std::shared_ptr<Bulk> bulk_;
    Target target_ = Target::Log;
};
