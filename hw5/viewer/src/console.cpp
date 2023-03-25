#include <viewer/console.h>
#include <iostream>

using namespace std;

ConsoleDisp::ConsoleDisp(FileKeeper::Ptr& fileKeeper)
    : fileKeeper_(fileKeeper)
{}

void ConsoleDisp::ShowError(const std::string& err)
{
    cout << err << endl;
}

void ConsoleDisp::Update()
{
    if(fileKeeper_->IsFileOpen())
    {
        auto data { fileKeeper_->ReadFile() };
        for(const auto& d : data)
        {
            cout << d << " ";
            cout << endl;
        }
        cout << endl;
    }
}