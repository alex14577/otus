#include <async/async.h>
#include <bulk/bulk_impl.h>
#include <parser/parser.h>
#include <manager/manager.h>
#include <async/src/queue.h>
#include <sender/file_sender.h>
#include <sender/stdout_sender.h>

#define DEBUG_LOG
#include <log/log.h>

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <array>
#include <queue>
#include <string>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <filesystem>
#include <atomic>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

using logging::LogDbg;

namespace 
{
std::vector<std::string> Split(const std::string& str, char d) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, d)) {
        result.push_back(item);
    }

    return result;
}

Manager::Event LineTypeToEvent(LineType lineType)
{
    switch (lineType)
    {
    case (LineType::Cmd):
        {
            return Manager::Event::CmdAdded;
        }
    case (LineType::StartBlock):
        {
            return Manager::Event::StartBlockReceived;
        }        
    case (LineType::EndBlock):
        {
            return Manager::Event::EndBlockReceived;
        }
    case (LineType::Eof):
        {
            return Manager::Event::EofReceived;
        }
    default:
        {
            return Manager::Event::None;
        }
    }
}

class Async
{
public:
     Async() =default;
     ~Async() = default;

     using BulkPtr = shared_ptr<BulkImpl>;
     using ManagerPtr = shared_ptr<Manager>;

     [[nodiscard]] static shared_ptr<Async> GetPtr()
     {
          if(!ptr_)
          {
               lock_guard<mutex> lock(m_);
               if(!ptr_)
               {
                    ptr_ = make_shared<Async>();
                    ptr_->Start();
               }
          }
          return ptr_;
     }

     unique_ptr<pair<BulkPtr, ManagerPtr>> CreateBulk(Target target, size_t blkSize)
     {
          ManagerPtr mgr = make_shared<Manager>(blkSize);
          switch (target)
          {
          case (Target::File):
          {
               auto b = make_shared<BulkImpl>();
               auto fileSender = make_shared<FileSender>(b, path_);
               b->Attach(fileSender);
               return make_unique<pair<BulkPtr, ManagerPtr>>(make_pair(b, mgr) );
          }
          case (Target::Log):
          {
               auto b = make_shared<BulkImpl>();
               b->Attach(make_shared<StdOutSender>(b));
               return make_unique<pair<BulkPtr, ManagerPtr>>(make_pair(b, mgr) );
          }
          case (Target::All):
          {
               auto b = make_shared<BulkImpl>();
               b->Attach(make_shared<FileSender>(b, path_));
               b->Attach(make_shared<StdOutSender>(b));
               return make_unique<pair<BulkPtr, ManagerPtr>>(make_pair(b, mgr) );
          }
          default:
               return {};
          }
     }

     void Run(Target target);
     void Start();

     static bool HasStarted()
     {
          return started_;
     }

     size_t GetUniqueId() 
     {
          return uniqueId_++;
     }

     void Receive(async::Handle handle, const char* data, std::size_t size);
     size_t Connect(size_t bulkSize)
     {
          auto blkAndMgrLog = CreateBulk(Target::Log, bulkSize);
          auto blkAndMgrFile = CreateBulk(Target::File, bulkSize);
          auto& mLog = bulksAndMgrs_[Target::Log];
          auto& mFile = bulksAndMgrs_[Target::File];
          auto id = GetUniqueId();

          std::lock_guard<mutex> lc(m_);
          mLog.emplace(id, move(blkAndMgrLog));
          mFile.emplace(id, move(blkAndMgrFile));
          return id;
     }

     void Disconnect(async::Handle h)
     {
          auto handle = reinterpret_cast<size_t>(h);
          {
               bool mustStop = true;
               {
                    unique_lock<mutex> lc(m_);
                    creatorCv_.wait(lc, [this, handle]()
                         {
                              return q_.EmptyById(handle);   
                         });
                    for(auto& [_, blkAndMgr] : bulksAndMgrs_)
                    {
                         auto it = blkAndMgr.find(handle);
                         if(it != blkAndMgr.end())
                         {
                              blkAndMgr.erase(it);
                         }
                         if(!blkAndMgr.empty())
                         {
                              mustStop = false;
                         }
                    }
                    stop_ = mustStop;
               }
               qCv_.notify_all();
               
               if(mustStop)
               {
                    for(auto& thr : threads_)
                    {
                         if(thr.joinable())
                         {
                              thr.join();
                         }
                    }
                    ptr_.reset();
               }
          }
     }

     pair<BulkPtr, ManagerPtr> GetBulkAndMgr(Target target, size_t id)
     {
          auto& m = bulksAndMgrs_[target];
          const auto& blkAndMgr = m.find(id);
          if(blkAndMgr != m.end())
          {
               return {blkAndMgr->second->first, blkAndMgr->second->second};
          }
          return {};
     }

private:
     static bool started_;
     static shared_ptr<Async> ptr_;
     static mutex m_;

     condition_variable qCv_;
     condition_variable creatorCv_;
     Queue q_;

     array<thread, 3> threads_;

     unordered_map<Target, unordered_map<size_t, unique_ptr<pair<BulkPtr, ManagerPtr>>>> bulksAndMgrs_;

     bool stop_ = false;

     fs::path path_ = fs::path("/home/alex/prj/otus/otus/hw9/blk");

     atomic<size_t> uniqueId_ = 0;

     unordered_map<decltype(this_thread::get_id()), size_t> threadId_; // Для отладки
     
};

shared_ptr<Async> Async::ptr_ = nullptr;
mutex Async::m_;
bool Async::started_ = false;

void Async::Receive(async::Handle handle, const char* data, std::size_t size)
{
     size_t h = reinterpret_cast<size_t>(handle);
     {
          lock_guard<mutex> lc(m_);
          q_.Push(data, size, Target::All, h);
     }
     qCv_.notify_all();
}

void Async::Run(Target target)
{
     static atomic<size_t> threadNum = 0; // Для отладки
     threadId_[this_thread::get_id()] = threadNum++;
     while(1)
     {    
          LogDbg() << threadId_[this_thread::get_id()] << ": Waiting data";

          unique_lock<mutex> lc(m_);
          qCv_.wait(lc, [this]()
               { 
                    return !q_.Empty() || stop_;
               });
          if(stop_)
          {
               return;
          }
          auto [id, data] = q_.Pop(target);
          auto [blk, mgr] = GetBulkAndMgr(target, id);
          lc.unlock();

          LogDbg() << to_string(threadId_[this_thread::get_id()]) << ": Received data";

          auto cmds = Split(data, '\n');

          for(const auto& cmd : cmds)
          {
               auto lineType = ParseLine(cmd);
               if(lineType == LineType::Cmd)
               {
                    blk->AddCmd(cmd);
               }
               
               switch(mgr->HandleEvent(LineTypeToEvent(lineType)))
               {
                    case (Manager::State::NeedExitAndExecute):
                    {
                         blk->Execute();
                         break;
                    }
                    case (Manager::State::NeedExecute):
                    {
                         LogDbg() << threadId_[this_thread::get_id()] << ": Cmd Exucute";
                         blk->Execute();
                         break;
                    }
                    case (Manager::State::NeedExit):
                    {
                         return;
                    }
                    default:
                         {}
               } 
          }
          creatorCv_.notify_one();
     }
}

void Async::Start()
{
     threads_[0] = move(thread(&Async::Run, this, Target::Log));
     bulksAndMgrs_[Target::Log] = move(unordered_map<size_t, unique_ptr<pair<BulkPtr, ManagerPtr>>>());
     threads_[1] = move(thread(&Async::Run, this, Target::File));
     bulksAndMgrs_[Target::File] = move(unordered_map<size_t, unique_ptr<pair<BulkPtr, ManagerPtr>>>());
     threads_[2] = move(thread(&Async::Run, this, Target::File));

     started_ = true;
}

}

namespace async {

Handle Connect(size_t bulk) 
{
     (void)(bulk);

     auto p = Async::GetPtr();

     auto handle = p->Connect(bulk);

     return (Handle)handle;
}

void Receive(Handle handle, const char* data, std::size_t size) 
{
     if(Async::HasStarted())
     {
          Async::GetPtr()->Receive(handle, data, size);
     }
     else
     {
          throw runtime_error("Async not started");
     }
}

void Disconnect(Handle handle) 
{
     if(Async::HasStarted())
     {
          Async::GetPtr()->Disconnect(handle);
     }
     else
     {
          throw runtime_error("Async not started");
     }
}

}
