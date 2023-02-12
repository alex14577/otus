#include <my_allocator/allocator.h>
#include <my_container/my_container.h>

#include <iostream>
#include <map>
#include <math.h>

using namespace my_alloc;
using namespace my_container;
using namespace std;

constexpr int ElNum = 10;

template<typename KeyT, typename ValT, typename AllocT>
class IMap
{
public:
    IMap(){};

    void Fill(const int n)
    {
        for(int i = 0, fact = 1; i < n; ++i)
        {
            fact *= i + 1;
            map_[i] = fact;
        }
    }

    IMap& Get()
    {
        return map_;
    }

    void Print()
    {
        for(auto [key, val] : map_)
        {
            cout << key << " " << val << endl;
        }
    }

private:
    map<KeyT, ValT, std::less<KeyT>, AllocT> map_;
};

using stdPair = pair<const int, int>;
template <typename Alloc = std::allocator<stdPair>>
void TestMap()
{
    
    IMap<int, int, Alloc> m;
    m.Fill(ElNum);
    m.Print();
}

template <typename AllocT = std::allocator<int>>
void TestContainer()
{
    Container<int, AllocT> m;

    for(size_t i = 0; i < 10; ++i)
    {
        m.push_back(i);
    }
    for(auto it : m)
    {
        cout << it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    TestMap();
    TestMap<MyAlloc<stdPair>>();
    TestContainer();
    TestContainer<MyAlloc<int>>();

    return 0;
}
