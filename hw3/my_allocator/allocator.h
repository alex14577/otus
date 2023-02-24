#include <exception>
#include <type_traits>
#include <malloc.h>
#include <memory>
#include <algorithm>
#include <bitset>

#include <vector>

#include <iostream>

namespace my_alloc
{
template <typename T, size_t N>
class MyAlloc
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer    = const T*;
    using reference        = T&;
    MyAlloc() = default;

    MyAlloc(const MyAlloc& other)
    {
        pool_ = other.pool_;
        isBusy_ = other.isBusy_;
    }
    template <typename U>
    MyAlloc(MyAlloc<U, N>&& other)
    {
        pool_.swap(other.pool_);
        isBusy_.swap(other.isBusy_);
    }
    ~MyAlloc() = default;

    constexpr bool operator ==(MyAlloc& other)
    {
        return pool_ == other.pool_;
    }

    template<typename T1>
	struct rebind
	{ typedef MyAlloc<T1, N> other; };

    T* allocate(unsigned long n)
    {        
        if(!pool_) // Зашли 1-ый раз
        {
            Init();
        }

        auto it = FindPlace(n);
        if( it != N) 
        {
            Fill(it, n, true);
            return &pool_.get()[it];
        }
        throw std::bad_alloc();
    }
    void deallocate(T* p, unsigned long n)
    {
        if(p && (n > 0))
        {
            auto first = p - pool_.get();
            Fill(first, n, false);
        }
    }

private:
    std::shared_ptr<T[]> pool_{nullptr};
    std::shared_ptr<std::bitset<N>> isBusy_;

    void Init()
    {
        pool_.reset(new value_type[N]);
        if(!pool_)
        {
            throw std::bad_alloc();
        }
        isBusy_.reset(new std::bitset<N>(0));
    }

    void Fill(int first, int n, bool val)
    {
        auto& isBusy = (*isBusy_.get());
        for(auto i = first; i < first + n; ++i)
        {
            isBusy[i] = val;
        }
    }
    int FindPlace(int num)
    {
        decltype(N) it{0};
        auto& isBusy = (*isBusy_.get());
        while(it < N)
        {
            int spaceWidth{0};
            auto begin = it;
            while(spaceWidth < num && isBusy[it] == false && it < N)
            {
                spaceWidth++;
                it++;
            }
            if(spaceWidth == num)
            {
                return begin;
            }
            it++;
        }
        return N;
    }
};


}

