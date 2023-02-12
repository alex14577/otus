#include <exception>
#include <type_traits>
#include <malloc.h>

#ifdef DEBUG
#include <iostream>
#endif

namespace my_alloc
{
template <typename T>
class MyAlloc
{
public:
    using value_type = T;
    MyAlloc() {}

    template <typename U>
    MyAlloc(const MyAlloc<U>& ) 
    {
#ifdef DEBUG
        std::cout << "copy crt " << typeid(U).name() << std::endl;
#endif
    }
    template <typename U>
    MyAlloc(const MyAlloc<U>&& ) 
    {
#ifdef DEBUG
        std::cout << "move crt " <<typeid(U).name() <<  std::endl;
#endif
    }

    template<typename T1>
	struct rebind
	{ typedef MyAlloc<T1> other; };

    T* allocate(unsigned long n)
    {
#ifdef DEBUG
        std::cout << "allocate" << " n = " << n << " size = " << sizeof(T) << std::endl;
#endif
        auto p = malloc(n * sizeof(T));
        if(!p)
        {
            throw std::bad_alloc();
        }
        return reinterpret_cast<T*>(p);
    }
    void deallocate(T* p, unsigned long n)
    {
        (void)(n);
#ifdef DEBUG
        std::cout << "deallcate" << " n = " << n << std::endl ;
#endif
        free(p);
    }
    
    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) 
    {
#ifdef DEBUG
        std::cout << "construct" << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p)
    {
#ifdef DEBUG
        std::cout << "destroy" << " " << std::endl;
#endif
        p->~T();
    }
};
}