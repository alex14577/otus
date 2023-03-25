#pragma once 

// Интерфейс комманд.

#include <string>
#include <vector>
#include <memory>

class Command
{
public:
    using Id = std::string;
    using Ptr = std::shared_ptr<Command>;
    Command() = default;
    virtual ~Command() = default;

    virtual void Execute(std::vector<std::string>& args) = 0;
};
