#include <file_keeper/file.h>

using namespace std;

File::File(string name)
    : name_(name)
{ }

void File::Push(std::unique_ptr<Figure>& fig)
{
    data_.push_back(move(fig));
}

std::vector<std::string> File::GetData()
{
    vector<string> data;
    for(const auto& fig : data_)
    {
        data.push_back(fig->GetData());
    }
    return data;
}

std::string File::GetName() const
{
    return name_;
}