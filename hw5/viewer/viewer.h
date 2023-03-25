#pragma once

// Интерфейс отображения на экран.

#include <file_keeper/file_keeper.h>

#include <string>

class Viewer
{
public:
    Viewer() = default;
    virtual ~Viewer() = default;

    virtual void ShowError(const std::string& err) = 0;
    virtual void Update() = 0;
};