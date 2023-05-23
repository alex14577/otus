#pragma once

/// @file sender.h
/// @brief Интерфейс отправителя команд

#include <types/types.h>

class Sender
{
public:
    virtual ~Sender() = default;
    virtual void Update() = 0;
    virtual Target GetTarget() const noexcept= 0;
};