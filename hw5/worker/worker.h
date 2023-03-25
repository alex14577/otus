#pragma once

// Описание интерфейса воркера (контроллера).

#include <string>
#include <memory>

class CommandFactory;
class Reciever;
class FileKeeper;
class Viewer;

class Worker
{
public:
    Worker(std::unique_ptr<Reciever>& rec,
        std::unique_ptr<CommandFactory>& cmds,
        std::shared_ptr<FileKeeper>& fileKeeper,
        std::unique_ptr<Viewer>& viewer
        );
        
    ~Worker() = default;

    void Run();

private:
    std::unique_ptr<Reciever> receiver_;
    std::shared_ptr<FileKeeper> fileKeeper_;
    std::unique_ptr<CommandFactory> cmds_;
    std::unique_ptr<Viewer> viewer_;
};

