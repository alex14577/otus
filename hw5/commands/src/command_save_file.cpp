#include <commands/command_save_file.h>

#include <figures/circle.h>
#include <figures/point.h>
#include <figures/line.h>

#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;

Save::Save(FileKeeper::Ptr fileKeeper)
    : fileKeeper_(fileKeeper)
{
    
}

void Save::Execute(vector<string>& args)
{
    try
    {
        if(fileKeeper_->IsFileOpen())
        {
            auto data{fileKeeper_->ReadFile()};
            string fileName = args[Path];
            ofstream ostrm(fileName, std::ios::out);
            for(const auto& d : data)
            {
                ostrm << d << endl;
            }
            ostrm.flush();
        }
        else
        {
            throw runtime_error("No opened file");
        }
    }
    catch(const exception& )
    {
        throw runtime_error("Unable to make this figure");
    }
}