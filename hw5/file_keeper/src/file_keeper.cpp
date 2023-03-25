#include <file_keeper/file_keeper.h>
#include <exception>

using namespace std;

shared_ptr<File> FileKeeper::Create(string& name)
{
    if(!curFile_)
    {
        curFile_ = make_shared<File>(name);
    }
    else
    {
        throw runtime_error("File is already open");
    }
    return curFile_;
}

void FileKeeper::Save([[maybe_unused]] File::Ptr& file, [[maybe_unused]]  std::filesystem::path& path)
{
    throw runtime_error("Operation is unavailable");
}

File::Ptr FileKeeper::Open([[maybe_unused]]  std::filesystem::path& path)
{
    throw runtime_error("Operation is unavailable");
}

bool FileKeeper::IsFileOpen() const
{
    return curFile_.get() != nullptr;
}

vector<string> FileKeeper::ReadFile() const
{
    return curFile_->GetData();
}

void FileKeeper::AddToFile(unique_ptr<Figure>& fig)
{
    curFile_->Push(fig);
}