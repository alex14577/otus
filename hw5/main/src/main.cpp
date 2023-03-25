#include <worker/worker.h>
#include <receiver/console_receiver.h>
#include <commands/command_factory.h>
#include <file_keeper/file_keeper.h>
#include <viewer/console.h>

#include <commands/command_create_file.h>
#include <commands/command_add_figure.h>
#include <commands/command_save_file.h>

#include <memory>

using namespace std;

unique_ptr<CommandFactory> CreateCommandFactory(shared_ptr<FileKeeper>& fileKeeper)
{
    unique_ptr<CommandFactory> cmdFactory = make_unique<CommandFactory>();

    cmdFactory->AddCmd<CreateFile>  ("create",  fileKeeper);
    cmdFactory->AddCmd<AddFigure>   ("add",     fileKeeper);
    cmdFactory->AddCmd<Save>        ("save",    fileKeeper);

    return cmdFactory;
}

int main()
{
    unique_ptr<Reciever> receiver = make_unique<ConsoleReceiver>();
    FileKeeper::Ptr fileKeeper = make_unique<FileKeeper>();

    auto cmdFact = CreateCommandFactory(fileKeeper);
    unique_ptr<Viewer> viewer = make_unique<ConsoleDisp>(fileKeeper);
    
    Worker w(receiver, cmdFact, fileKeeper, viewer);
    w.Run();
}