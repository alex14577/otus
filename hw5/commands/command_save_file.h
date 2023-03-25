#pragma once 

// Команда сохранить в файл.

#include <commands/command.h>
#include <file_keeper/file_keeper.h>

#include <string>
#include <memory>
#include <map>
#include <functional>

class Point;
class Circle;
class Line;

class Save : public Command
{
public:
    Save(FileKeeper::Ptr fileKeeper);
    virtual ~Save() = default;

    void Execute(std::vector<std::string>& args) override final;
    
private:
    enum // Номера аргументов.
    {
        Path = 0,
    };
    FileKeeper::Ptr fileKeeper_;
};
