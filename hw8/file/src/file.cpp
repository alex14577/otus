#include <file/file.h>

#include <fstream>
#include <vector>

using namespace std;

namespace fs = std::filesystem;

File::File(size_t chunkSize, std::unique_ptr<crc_alg::Crc>&& crc)
    : f_(nullptr), chunkSize_(chunkSize),
      crc_(move(crc))
{}

bool File::Open(const fs::path& f)
{
     f_ = std::unique_ptr<std::FILE, FileCloser>(fopen(f.c_str(), "rb"));
     if(f_)
     {
          path_ = f;
          return true;
     }
     return false;
}

pair<bool, size_t> File::GetChunk() const
{
     if(f_)
     {
          bool lastChunk = false;
          vector<uint8_t> data(chunkSize_);
          size_t readSz = 0; 
          readSz = fread(data.data(), 1, chunkSize_, f_.get());
          if(readSz < chunkSize_)
          {
               lastChunk = true;
               fill(&data[readSz], &data[chunkSize_], '\0');
          }
          return {lastChunk, crc_->GetCrc(data)};
     }
     return {true, 0};
}

fs::path File::GetPath() const
{
     return path_;
}

void File::FileCloser::operator()(std::FILE* f)
{
     fclose(f);
}
