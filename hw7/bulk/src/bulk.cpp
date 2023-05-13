#include <bulk/bulk_impl.h>
#include <sender/sender.h>

#include <stdexcept>
#include <chrono>

using namespace std;

using sysclk = std::chrono::system_clock;

void BulkImpl::AddCmd(const string& cmd)
{
     if(cmds_.empty())
     {
          frstCmdTime_ = sysclk::to_time_t(sysclk::now());
     }
     cmds_.push_back(cmd);
}

void BulkImpl::Execute()
{
     if(!cmds_.empty())
     {
          NotifyAll();
          cmds_.clear();
     }
}

void BulkImpl::Attach(const std::shared_ptr<Sender>& sender)
{
     auto it = find(senders_.begin(), senders_.end(), sender);
     if(it == senders_.end())
     {
         senders_.push_back(sender);
     }
}

std::vector<std::string_view> BulkImpl::GetData() const
{
     vector<string_view> res;
     res.reserve(cmds_.size());
     res.insert(res.begin(), cmds_.begin(), cmds_.end());
     return res;
}

std::time_t BulkImpl::GetTimeFirstCmd() const 
{
     return frstCmdTime_;
}

void BulkImpl::NotifyAll()
{
     for(const auto& sender : senders_)
     {
          sender->Update();
     }
}