#pragma once 

// Интерфейс для получения команд.
#include <string>

class Reciever
{
public:
    Reciever() = default;
    virtual ~Reciever() = default;

    // Получить порцию данных.
    virtual std::string GetData() = 0;
};