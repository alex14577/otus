#pragma once

// Интерфейс отображения на экран.

#include <viewer/viewer.h>
#include <file_keeper/file_keeper.h>

#include <string>

class ConsoleDisp : public Viewer
{
public:
    ConsoleDisp(FileKeeper::Ptr& fileKeeper);
    ~ConsoleDisp() = default;

    void ShowError(const std::string& err) override final;
    void Update() override final;

private:
    FileKeeper::Ptr fileKeeper_;    
};