#pragma once
// Интерфейс для работы с файлами

#include <file_keeper/file.h>

#include <memory>
#include <filesystem>

class Figure;

class FileKeeper
{
public:
    using Ptr = std::shared_ptr<FileKeeper>;
    FileKeeper() = default;
    ~FileKeeper() = default;

    File::Ptr Create(std::string& name);
    void Save(File::Ptr& file, std::filesystem::path& path);
    File::Ptr Open(std::filesystem::path& path);

    bool IsFileOpen() const;
    std::vector<std::string> ReadFile() const;
    void AddToFile(std::unique_ptr<Figure>& fig);

private:
    File::Ptr curFile_;
};