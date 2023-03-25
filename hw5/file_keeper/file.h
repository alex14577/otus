#pragma once

// Интерфейс файла.

#include <figures/figure.h>

#include <vector>
#include <string>
#include <memory>

class File
{
public:
    using Ptr = std::shared_ptr<File>;

    File() = delete;
    File(std::string name);
    ~File() = default;

    void Push(std::unique_ptr<Figure>& fig);
    std::string GetName() const;
    std::vector<std::string> GetData();

private:
    std::string name_;
    std::vector<std::unique_ptr<Figure>> data_;
};