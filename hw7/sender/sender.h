#pragma once

/// @file sender.h
/// @brief Интерфейс отправителя команд

class Sender
{
public:
    virtual ~Sender() = default;
    virtual void Update() = 0;
};