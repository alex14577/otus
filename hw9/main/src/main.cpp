#include <async/async.h>

#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <filesystem>

using namespace std;
using namespace async;
namespace fs = std::filesystem;

string GetCmds(const string& path)
{
     ifstream f(path);
     stringstream ss;
     if(f.is_open())
     {
          ss << f.rdbuf();
     }
     return ss.str();
}

void PrepareOut()
{
     fs::remove_all("/home/alex/prj/otus/otus/hw9/blk/");
     fs::create_directory("/home/alex/prj/otus/otus/hw9/blk");
}

int main()
{
     PrepareOut();
     auto cmds1 = GetCmds("/home/alex/prj/otus/otus/hw9/test_cmd1");
     auto cmds2 = GetCmds("/home/alex/prj/otus/otus/hw9/test_cmd2");
     auto cmds3 = GetCmds("/home/alex/prj/otus/otus/hw9/test_cmd3");

     vector<async::Handle> handles;
     for(size_t i = 100; i > 0; i--)
     {
          auto h1 = Connect(4);
          auto h = Connect(3);
          handles.push_back(h);
          handles.push_back(h1);
          Receive(h, cmds1.data(), cmds1.size());
          Receive(h1, cmds1.data(), cmds1.size());
          Receive(h, cmds2.data(), cmds2.size());
          Receive(h1, cmds2.data(), cmds2.size());
          Receive(h, cmds3.data(), cmds3.size());
          Receive(h1, cmds3.data(), cmds3.size());
          Receive(h, cmds1.data(), cmds1.size());
          Receive(h1, cmds1.data(), cmds1.size());
          Receive(h, cmds2.data(), cmds2.size());
          Receive(h1, cmds2.data(), cmds2.size());
          Receive(h, cmds3.data(), cmds3.size());
          Receive(h1, cmds3.data(), cmds3.size());
     }
     for(const auto h : handles)
     {
          Disconnect(h);
     }
}

