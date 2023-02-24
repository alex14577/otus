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
        using const_iterator = const T*;

        Container() = default;

        Container(const Container& other)
        {
            Copy(other);
        }
        Container(Container&& other)
        {
            if(!other.empty())
            {
                std::swap(storage_, other.storage_);
                std::swap(alloc_, other.alloc_);
                std::swap(size_, other.size_);
                std::swap(capacity_, other.capacity_);
            }
        }
        Container(const iterator first, const  iterator last)
        {
            const size_type num = std::distance(first, last);
            storage_ = alloc_.allocate(num);

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
            ClearContainer();
        }        

        iterator begin() const { return storage_; }
        iterator end() const {return empty() ? nullptr : &storage_[size_];}
        const_iterator cbegin() const { return storage_; }
        const_iterator cend() const {return empty() ? nullptr : &storage_[size_];}

        void push_back(const T& el)
        {
            if(size_ == capacity_)
            {
                size_type newCapacity = size_ == 0 ? 1 : size_ * mlt_;
                iterator p = alloc_.allocate(newCapacity);
                capacity_ = newCapacity;
                
                std::copy(storage_, storage_ + size_, p);

                if(size_)
                {
                    alloc_.deallocate(storage_, size_);
                }
                storage_ = p;
            }

            storage_[size_] = el;
            ++size_;
        }

        T& operator [] (size_type n)
        {
            return storage_[n];
        }

        Container& operator =(const Container& other)
        {
            Copy(other);
            return *this;
        }

        bool empty() const { return size_ == 0; }
        size_type size() const { return size_; }

        
    private:
        T* storage_{nullptr};
        size_type size_{0};
        size_type capacity_{0};
        allocator_type alloc_;
        static constexpr size_type mlt_ = 2;

        void Copy(const Container& other)
        {
            ClearContainer();
            if(!other.empty())
            {
                storage_ = alloc_.allocate(other.size());   
                std::copy(other.cbegin(), other.cend(), storage_);
                size_ = other.size_;
                capacity_ = size_;
            }
        }

        void ClearContainer()
        {
            if(size_)
            {
                if constexpr(!std::is_scalar<T>::value)
                {
                    iterator it = storage_;
                    iterator end = &storage_[size_];
                    while(it != end)
                    {
                        it->~T();
                        ++it;
                    }
                }

                alloc_.deallocate(storage_, size_);
                size_ = 0;
                capacity_ = 0;
                storage_ = nullptr;
            }
        }
    };
}
