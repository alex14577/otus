#include <worker/worker.h>
#include <receiver/receiver.h>
#include <file_keeper/file_keeper.h>
#include <commands/command_factory.h>
#include <viewer/viewer.h>

#include <string>
#include <iostream>

using namespace std;

Worker::Worker(std::unique_ptr<Reciever>& rec, 
    std::unique_ptr<CommandFactory>& cmds, 
    std::shared_ptr<FileKeeper>& fileKeeper,
    std::unique_ptr<Viewer>& viewer
    )
{
    receiver_.swap(rec);
    cmds_.swap(cmds);
    fileKeeper_.swap(fileKeeper);
    viewer_.swap(viewer);
}

namespace
{
vector<string> Split(const string &str)
{
    vector<string> res;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(' ');
    while(stop != string::npos)
    {
        res.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(' ', start);
    }

    res.emplace_back(str.substr(start));

    return res;
}
}

void Worker::Run()
{
    while (true)
    {
        auto data = receiver_->GetData();
        auto args = Split(data);

        auto cmd = cmds_->Create(args[0]);

        args.erase(args.begin());

        if(cmd)
        {
            try
            {
                cmd->Execute(args);
                viewer_->Update();
            }
            catch(const std::exception& e)
            {
                viewer_->ShowError(e.what());
            }
        }
        else
        {
            cout << "Нет такой команды" << endl;
        }
    }
}
