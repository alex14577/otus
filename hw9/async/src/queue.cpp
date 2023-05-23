#include <async/src/queue.h>

using namespace std;

Data::Data(const std::string_view& data, Target target, size_t id)
     : data_(data),
       uniqueId_(id),
       target_(target)
{}

string Data::String()
{
     return data_;
}

const string Data::String()  const
{
     return data_;
}
size_t Data::GetId() const
{
     return uniqueId_;
}

Target Data::GetTargetRemain() const
{
     return static_cast<Target>(target_);
}

void Data::ResetTarget(Target target)
{
     target_ = static_cast<Target>(static_cast<uint8_t>(target_) & ~static_cast<uint8_t>(target));
}

void Queue::Push(const char* data, size_t size, Target target, size_t id)
{
     q_.emplace_back(Data({data,size}, target, id));
}

std::pair<size_t, string> Queue::Pop(Target target)
{
     for(auto it = q_.begin(); it != q_.end(); ++it)
     {
          if(static_cast<uint8_t>(it->GetTargetRemain()) & static_cast<uint8_t>(target))
          {
               it->ResetTarget(target);
               if(static_cast<uint8_t>(it->GetTargetRemain()) == 0)
               {
                    auto ret{move(*it)};
                    q_.erase(it);
                    return {ret.GetId(), move(ret.String())};
               }
               return  {it->GetId(), it->String()};
          }
     }
     return {};
}

bool Queue::Empty() const
{
    return q_.empty();
}

#include <iostream>
#include <atomic>

// atomic<size_t> cnt = 0;

bool Queue::EmptyById(size_t id) const
{
     // cout << cnt++ << endl;
     // size_t cntInt = 0;
     for(const auto& data : q_)
     {
          // cntInt++;
          if(data.GetId() == id)
          {
               // cout << "\"" << cntInt << "\" ";
               return false;
          }
     }
     return true;
}