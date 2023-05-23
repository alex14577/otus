#pragma once

#include <vector>
#include <memory>
#include <ctime>

class Sender;

class Bulk
{
public:
     virtual ~Bulk() = default;

     virtual std::vector<std::string_view> GetData() const = 0;
     virtual std::time_t GetTimeFirstCmd() const = 0;
     virtual void Attach(const std::shared_ptr<Sender>& sender) = 0;
};
