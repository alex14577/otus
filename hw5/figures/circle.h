#pragma once

// Класс, реализубщий фигуру Круг

#include <figures/figure.h>
#include <figures/point.h>

#include <string>

class Circle : public Figure
{
public:
    Circle(Point p, uint64_t r);

    virtual std::string GetData() const override final;

private:
    std::string name_{"circle"};
    Point pos_;
    uint64_t radius_;
};