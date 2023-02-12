#include <memory>
#include <iostream>

namespace my_container
{
    template <typename T, typename AllocT = std::allocator<T>>
    class Container
    {
    public:
        using iterator = T*;
        using size_type = size_t;
        using allocator_type = AllocT;

        Container() = default;

        Container(Container& other)
        {
#ifdef DEBUG
            std::cout << "Container Copy Ctr" << std::endl;
#endif
            storage_ = alloc_.allocate(other.size());
            if(!other.empty())
            {
                std::copy(other.begin(), other.end(), storage_);
            }
        }
        Container(Container&& other)
        {
#ifdef DEBUG
            std::cout << "Container Move Ctr" << std::endl;
#endif
            if(!other.empty())
            {
                storage_.swap(other);
                capacity_ = other.capacity_;
                size_ = other.size_;
                other.size_= 0;
                other.capacity_= 0;
            }

            std::copy(other.begin(), other.end(), storage_);
        }
        Container(const iterator first, const  iterator last)
        {
#ifdef DEBUG
            std::cout << "Range Copy Ctr" << std::endl;
#endif
            const size_type num = std::distance(first, last);
            storage_.reset(alloc_.allocate(num));

            iterator it = first;
            size_type cnt{0};
            while(it != last)
            {
                alloc_.construct(&storage_[cnt++], it);
            }
            size_ = num;
            capacity_ = num;
        }
        ~Container()
        {
#ifdef DEBUG
            std::cout << "Dtr" << std::endl;
#endif
            iterator it = storage_;
            iterator end = &storage_[size_];
            while(it != end)
            {
                alloc_.destroy(it);
                ++it;
            }
            alloc_.deallocate(storage_, size_);
        }        

        iterator begin() { return storage_; }
        iterator end() {return empty() ? nullptr : &storage_[size_];}

        void push_back(T el)
        {
            if(size_ == capacity_)
            {
                size_type newCapacity = size_ == 0? 1 : size_ * mlt_;
                iterator p = alloc_.allocate(newCapacity);
                capacity_ = newCapacity;
                
                iterator dst{p};
                iterator src{storage_};
                iterator end{&storage_[size_]};
                while(src != end)
                {
                    alloc_.construct(dst, *src);
                    alloc_.destroy(src);
                    ++src;
                    ++dst;
                }
                if(size_)
                {
                    alloc_.deallocate(storage_, size_);
                }
                storage_ = p;
            }
            alloc_.construct(&storage_[size_], el);
            ++size_;

        }

        T& operator [] (size_type n)
        {
            return storage_[n];
        }
        
        bool empty(){ return size_ == 0; }
        size_type size(){ return size_; }

        
    private:
        T* storage_{nullptr};
        size_type size_{0};
        size_type capacity_{0};
        allocator_type alloc_;
        static constexpr size_type mlt_ = 2;
    };
}
