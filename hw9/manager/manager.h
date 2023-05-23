#pragma once

#include <bulk/bulk.h>

#include <memory>
#include <stddef.h>

class Manager
{
public:
    Manager(size_t argsNum);

    enum class Mode
    {
        Blocks,
        ArgsNum,
    };

    enum Event
    {
        None,
        CmdAdded,
        StartBlockReceived,
        EndBlockReceived,
        EofReceived,
    };

    enum State
    {
        No,
        NeedExecute,
        NeedExit,
        NeedExitAndExecute
    };

    /// @brief Обработать событие. 
    /// @param ev Событие
    /// @return true, если пора исполнить команды
    State HandleEvent(Event ev);

private:
    // Используется то или иное в зависимости от режима.
    union
    {
        size_t cmdsReceived_ = 0;
        size_t blockDeep_;
    };

    State HandleAddBlockDeep();
    State HandleDeductBlockDeep();
    State HandleCmdReceived();
    State HandleEofReceived();
    void ChangeMode(Mode mode);
    
    Mode mode_{Mode::ArgsNum};
    size_t cmdsNumToExecute_{0};
};