#include <manager/manager.h>

#include <stdexcept>

using namespace std;

Manager::Manager(size_t argsNum)
    : cmdsNumToExecute_(argsNum)
    {}

Manager::State Manager::HandleCmdReceived()
{
    switch(mode_)
    {
        case(Mode::ArgsNum):
        {
            cmdsReceived_++;
            if(cmdsReceived_ == cmdsNumToExecute_)
            {
                cmdsReceived_ = 0;
                return State::NeedExecute;
            }
            return State::No;
        }
        case(Mode::Blocks):
        {
            return State::No;
        }
        default:
        {
            return State::No;
        }
    }
}

Manager::State Manager::HandleEvent(Event ev)
{
    switch (ev)
    {
    case (Event::CmdAdded):
        {
            return HandleCmdReceived();
        }
    case (Event::StartBlockReceived):
        {
            return HandleAddBlockDeep();            
        }
    case (Event::EndBlockReceived):
        {
            return HandleDeductBlockDeep();
        }
    case (Event::EofReceived):
        {
            return HandleEofReceived();
        }
    default:
        return State::No;
    }
}

void Manager::ChangeMode(Mode mode)
{
    switch (mode)
    {
    case (Mode::ArgsNum):
        {
            mode_ = Mode::ArgsNum;
            cmdsReceived_ = 0;
            break;
        }
    case (Mode::Blocks):
        {
            mode_ = Mode::Blocks;
            blockDeep_ = 0;
            break;
        }
    default:
        {
            throw runtime_error("Invalid mode");
        }
    }
}

Manager::State Manager::HandleAddBlockDeep()
{
    switch(mode_)
    {
        case(Mode::Blocks):
        {
            blockDeep_++;
            return State::No;
        }
        case(Mode::ArgsNum):
        {
            ChangeMode(Mode::Blocks);
            blockDeep_++;
            return State::NeedExecute;
        }
        default:
        {
            return State::No;
        }
    }
}

Manager::State Manager::HandleDeductBlockDeep()
{
    if(mode_ == Mode::Blocks)
    {
        if(blockDeep_ > 0)
        {
            blockDeep_--;
            if(!blockDeep_)
            {
                ChangeMode(Mode::ArgsNum);
                return State::NeedExecute;
            }
        }
    }
    return State::No;
}

Manager::State Manager::HandleEofReceived()
{
    switch (mode_)
    {
        case(Mode::Blocks):
        {
            return State::NeedExit;
        }
        case(Mode::ArgsNum):
        {
            return State::NeedExitAndExecute;    
        }
    }
    return State::No;
}