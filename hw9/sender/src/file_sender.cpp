#include <sender/file_sender.h>
#include <bulk/bulk.h>
#include <fstream>
#include <iomanip>
#include <charconv>

using namespace std;

namespace fs = std::filesystem;

FileSender::FileSender(const std::shared_ptr<Bulk>& bulk, const std::filesystem::path& path)
     : bulk_(bulk)
{
     if(fs::is_directory(path))
     {
          pathOut_ = path;
     }
     else
     {
          pathOut_ = fs::is_directory(path) ? path : fs::current_path();
     }
}

void FileSender::Update()
{
     auto time = bulk_->GetTimeFirstCmd();
     array<char, 25> timeCh{0};
     to_chars(timeCh.begin(), timeCh.end(), static_cast<int>(time));

     string filename;
     filename = pathOut_.string() + fs::path::preferred_separator +
         "bulk" + timeCh.data() + ".log";

     size_t tryNum = 1;
     while(fs::exists(filename))
     {
          array<char, 25> tryNumCh{0};
          to_chars(tryNumCh.begin(), tryNumCh.end(), static_cast<int>(tryNum++));
          filename = pathOut_.string() + fs::path::preferred_separator +
               "bulk" + timeCh.data() + '_' + tryNumCh.data() + ".log";
     }

     auto data = bulk_->GetData();

     ofstream out(filename);
     if(out.is_open())
     {
          out << "bulk: ";
          for(const auto& d : data)
          {
               out << d << " ";
          }
          out << endl;
     }
}

Target FileSender::GetTarget() const noexcept
{
     return target_;
}