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
     pathOut_ = fs::is_directory(path) ? path : fs::current_path();
}

void FileSender::Update()
{
     auto time = bulk_->GetTimeFirstCmd();
     array<char, 25> timeCh{0};
     auto [ptr, ec] = to_chars(timeCh.begin(), timeCh.end(), static_cast<int>(time));
     (void)(ptr);
     string filename;
     filename = pathOut_.string() + fs::path::preferred_separator +
         "bulk" + timeCh.data() + ".log";

     struct Closer
     {
          void operator()(ofstream& f)
          {
               f.close();
          }
     };

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