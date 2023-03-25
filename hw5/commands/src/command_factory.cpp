#include<commands/command_factory.h>

using namespace std;

Command::Ptr CommandFactory::Create(Command::Id& id)
{
    if(cmds_.contains(id))
    {
        return cmds_[id];
    }
    return nullptr;
}
