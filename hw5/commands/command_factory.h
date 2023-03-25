#pragma once 

// Класс, отвечающий за обработчику команд.

#include <commands/command.h>

#include <map>
#include <functional>

class CommandFactory
{
public:
    CommandFactory() = default;
    ~CommandFactory() = default;
    
    template<typename T, typename ...Args>
    void AddCmd(Command::Id id, Args... args)
    {
        cmds_[id] = make_shared<T>(args...);
    }

    Command::Ptr Create(Command::Id& id);

private:
    std::map<Command::Id, Command::Ptr> cmds_;
};