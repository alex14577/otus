#pragma once 

// Интерфейс комманд.

#include <commands/command.h>
#include <file_keeper/file_keeper.h>

#include <string>
#include <memory>

class CreateFile : public Command
{
public:
    CreateFile(FileKeeper::Ptr fileKeeper);
    virtual ~CreateFile() = default;

    void Execute(std::vector<std::string>& args) override final;
    
    // Номера аргументов в команде.
    enum
    {
        fileName = 0,
    };

private:
    FileKeeper::Ptr FileKeeper_;
};
