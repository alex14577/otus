#pragma once

/// @file data.h
/// @brief Вспомогательный класс сообщений.

#include <types/types.h>

#include <string>
#include <deque>
#include <mutex>

class Data
{
public:

public:
     Data() = default;
     Data(const Data&) = default;
     Data(Data&&) = default;
     Data(const std::string_view& data, Target target, size_t id);

     Data& operator=(const Data&) = default;

     Target GetTargetRemain() const;
     void ResetTarget(Target target);
     std::string String();
     const std::string String() const;
     size_t GetId() const;

private:
     std::string data_;
     size_t uniqueId_;
     Target target_;    
};

class Queue
{
public:
    Queue() = default;
    Queue(const Queue&) = default;
    
    void Push(const char* data, size_t size, Target target, size_t id);

    std::pair<size_t, std::string> Pop(Target target);

    bool Empty() const;

    bool EmptyById(size_t id) const;

private:
    std::deque<Data> q_;
};