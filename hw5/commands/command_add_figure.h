#pragma once 

// Интерфейс комманд.

#include <commands/command.h>
#include <file_keeper/file_keeper.h>

#include <string>
#include <memory>
#include <map>
#include <functional>

class Point;
class Circle;
class Line;

class AddFigure : public Command
{
public:
    AddFigure(FileKeeper::Ptr fileKeeper);
    virtual ~AddFigure() = default;

    void Execute(std::vector<std::string>& args) override final;
    
private:
    enum // Номера аргументов.
    {
        FigureName = 0,
    };
    FileKeeper::Ptr fileKeeper_;
};
