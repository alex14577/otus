#include <commands/command_create_file.h>

#include <iostream>

using namespace std;

CreateFile::CreateFile(FileKeeper::Ptr fileKeeper)
    : FileKeeper_(fileKeeper)
{
    
}

void CreateFile::Execute(vector<string>& args)
{
    FileKeeper_->Create(args[fileName]);
}