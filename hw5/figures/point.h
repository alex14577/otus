#pragma once

// Класс, реализубщий фигуру Точка

#include <figures/figure.h>

#include <stdint.h>
#include <string>

class Point : public Figure
{
public:
    using Type = uint64_t;

    Point(Type x, Type y)
    : x_(x),
      y_(y)
      {}

    std::string GetData() const override final;   

    Type GetX() const;
    Type GetY() const;

private:
    std::string name_{"point"};
    Type x_;
    Type y_;
};