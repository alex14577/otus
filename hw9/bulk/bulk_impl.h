#pragma once

#include <manager/manager.h>
#include <bulk/bulk.h>
#include <types/types.h>

#include <string>
#include <ctime>

class BulkImpl final : public Bulk
{
public:
     ~BulkImpl() = default;
     void AddCmd(const std::string& cmd);
     void Execute();

     std::vector<std::string_view> GetData() const override;
     std::time_t GetTimeFirstCmd() const override;
     void Attach(const std::shared_ptr<Sender>& sender) override;

private:
     void NotifyAll();

private:
     std::vector<std::string> cmds_;
     std::vector<std::shared_ptr<Sender>> senders_;
     std::time_t frstCmdTime_ = 0;
};
