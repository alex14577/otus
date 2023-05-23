#pragma once

#include <string>
#include <iostream>
#include <mutex>

namespace logging
{

class LogDbg
{
public:
     LogDbg() = default;

     template<typename T>
     LogDbg& operator<<([[maybe_unused]] const T& str)
     {
#ifdef DEBUG_LOG
          std::lock_guard<std::mutex> lc(m_);
          std::cout << str;
#endif
          return *this;
     }

     ~LogDbg()
     {
#ifdef DEBUG_LOG
          std::lock_guard<std::mutex> lc(m_);
          std::cout << std::endl;
#endif
     }
private:
     std::mutex m_;
};

}
