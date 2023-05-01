#include <bulk/bulk.h>

#include <stdexcept>

using namespace std;

void Bulk::AddCmd(const string& cmd)
{
    cmds_.emplace(cmd);
}

void Bulk::Execute(std::ostream& out)
{
    if(!cmds_.empty())
    {
        out << "bulk:";
        while(cmds_.size())
        {
            out << " " << cmds_.front();
            cmds_.pop();
        }
        out << endl;
    }

}