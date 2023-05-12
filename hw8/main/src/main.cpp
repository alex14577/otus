#include <crc/crc.h>
#include <file/file.h>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <regex>
#include <map>

using namespace std;
namespace fs = std::filesystem;

constexpr string_view argDir = "--dir";
constexpr string_view argDirExclude = "--direxclude";
constexpr string_view argDirDeep = "--dirDeep";
constexpr string_view argFileMinSize = "--fminsz";
constexpr string_view argFileNameMask = "--fmask";
constexpr string_view argBlockSize = "--bsz";
constexpr string_view argHashAlg = "--hashalg";

struct Args
{
     string_view dir;
     string_view dirEx;
     string_view dirDeep;
     string_view fileMinSize;
     string_view mask;
     string_view blockSz;
     string_view hashAlg;
};

string_view GetArgByName(size_t argc, const char** argv, const string_view& argName)
{
     for(size_t i = 1; i < argc - 1; ++i)
     {
          string_view argNameCur = argv[i];
          if(argNameCur == argName && !string_view(argv[i + 1]).starts_with("--"))
          {
               return string_view(argv[i + 1]);
          }
     }
     return {};
}

vector<fs::path> FindFiles(const fs::path& path, const Args& args)
{
     if(!fs::exists(path))
     {
          cout << "Wrong Path!!!" << endl;
          return {};
     }

     regex regMask;
     if(!args.mask.empty())
     {
          regMask = regex(args.mask.data(),  std::regex_constants::ECMAScript | std::regex_constants::icase);
     }

     vector<fs::path> res;
     for(const auto& itPath : fs::directory_iterator(path))
     {
          if(
               fs::is_regular_file(itPath) && 
               (args.mask.empty() || regex_match(itPath.path().filename().c_str(), regMask)) &&
               static_cast<int>(itPath.file_size()) >= atoi(args.fileMinSize.data())
          )
          {
               res.push_back(itPath);
          }
          else if (fs::is_directory(itPath) && args.dirDeep == "1" && itPath != fs::path(args.dirEx))
          {
               for(const auto& file : FindFiles(itPath, args))
               {    
                    res.emplace_back(move(file));
               }
          }
     }
     return res;
}

crc_alg::CrcAlg ConvertCrcAlg(const string_view& str)
{
     if(str == "crc32")
     {
          return crc_alg::CrcAlg::Crc32;
     }
     else if(str == "md5")
     {
          return crc_alg::CrcAlg::Md5;
     }
     else
     {
          return crc_alg::CrcAlg::Undefined;
     }
}

vector<unique_ptr<File>> FindDuplicates(vector<unique_ptr<File>>&& files)
{    
     map<size_t, vector<unique_ptr<File>>> m;
     map<size_t, vector<unique_ptr<File>>> vLastChunk;
     for(size_t i = 0; i < files.size(); ++i)
     {
          auto [lastChunk, crc] = files[i]->GetChunk();
          if(lastChunk)
          {
               vLastChunk[crc].push_back(move(files[i]));
          }
          else
          {
               m[crc].push_back(move(files[i]));
          }
     }
     auto erase = [](const auto& v)
          { 
               return v.second.size() <= 1;
          }; 
     erase_if(vLastChunk, erase);
     erase_if(m, erase);

     vector<unique_ptr<File>> res;   
     for(auto& [_, fGroup] : vLastChunk)
     {
          res.reserve(res.size() + fGroup.size());
          move(fGroup.begin(), fGroup.end(), back_inserter(res));
     }
  
     for(auto&& [_, fGr] : m)
     {
          auto t = FindDuplicates(move(fGr));
          res.reserve(res.size() + t.size());
          move(t.begin(), t.end(), back_inserter(res));
     }
     
     return res;
}

int main(int argc, const char** argv)
{
     Args args
     {
          GetArgByName(argc, argv, argDir),
          GetArgByName(argc, argv, argDirExclude),
          GetArgByName(argc, argv, argDirDeep),
          GetArgByName(argc, argv, argFileMinSize),
          GetArgByName(argc, argv, argFileNameMask),
          GetArgByName(argc, argv, argBlockSize),
          GetArgByName(argc, argv, argHashAlg)
     };

     // Найдёи все файлы, удоволетворяющие входным аргументам
     auto paths = FindFiles(fs::path(args.dir), args);

     vector<unique_ptr<File>> files;
     files.reserve(paths.size());
     crc_alg::CrcAlg alg = ConvertCrcAlg(args.hashAlg);
     size_t chunkSz = atoi(args.blockSz.data());
     for(const auto& filePath : paths)
     {    
          unique_ptr<crc_alg::Crc> crc;
          if(alg == crc_alg::CrcAlg::Crc32)
          {
               crc = make_unique<crc_alg::Crc32Calculator>();
          }
          else
          {
               crc = make_unique<crc_alg::CrcMd5Calculator>();
          }
          unique_ptr<File> f( new File(chunkSz, move(crc)) );
          if( !f->Open(filePath))
          {
               cout << "Can't open file: " << filePath << endl;
               return -1;
          }
          files.push_back( move(f) );
     }

     auto v = FindDuplicates(move(files));

     for(const auto& f : v)
     {
          cout << f->GetPath() << endl;
     }

}

