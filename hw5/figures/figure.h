#pragma once

// Интерфейс для работы с графическими промитивами.

#include <string>

class Figure
{
public:
    Figure() = default;
    virtual ~Figure() = default;

    //Получить представление фигуры.
    virtual std::string GetData() const = 0;
};