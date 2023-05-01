#pragma once

#include <manager/manager.h>

#include <string>
#include <queue>
#include <memory>

class Bulk
{
public:
    void AddCmd(const std::string& cmd);
    void Execute(std::ostream& out);

private:
    std::queue<std::string> cmds_;    
};
