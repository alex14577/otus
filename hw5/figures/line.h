#pragma once

// Класс, реализубщий фигуру Квадрат

#include <figures/figure.h>
#include <figures/point.h>

#include <string>

class Line : public Figure
{
public:
    Line(Point start, Point end);

    virtual std::string GetData() const override final;

private:
    std::string name_{"line"};
    Point start_;
    Point end_;
};