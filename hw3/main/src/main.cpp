#include <my_allocator/allocator.h>
#include <my_container/my_container.h>

#include <iostream>
#include <map>
#include <vector>

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
void AddValRef(Container<int, AllocT>& m, int val)
{
    m.push_back(val);
}

template <typename AllocT = std::allocator<int>>
Container<int, AllocT> AddVal(Container<int, AllocT> m, int val)
{
    m.push_back(val);
    return m;
}

template <typename AllocT = std::allocator<int>>
void Print(Container<int, AllocT>& m)
{
    for(auto& it : m)
    {
        cout << it << " ";
    }
    std::cout << std::endl;
}

template<typename AllocT = std::allocator<int>>
void TestContainer()
{
    Container<int, AllocT> m;

    for(int i = 0; i < ElNum / 2; ++i)
    {
        m = AddVal(m, i);
    }
    for(int i = ElNum / 2; i < ElNum; ++i)
    {
        AddValRef(m, i);
    }
    Print(m);
}

void TestStdVec()
{
    using Vec = std::vector<int, MyAlloc<int, ElNum * 5 + 1>>;

    auto addVal = +[](Vec v, int i) ->  Vec
    {
        v.push_back(i);
        return v;
    };

    auto print = +[](Vec& v)
    {
        for(auto n : v)
        {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    };

    Vec v;  
    for(int i = 0; i < ElNum; i++)
    {
        v = addVal(v, i);
    }
    print(v);
}

int main()
{
    try
    {
        TestMap();
        TestMap<MyAlloc<stdPair, ElNum>>();
        TestContainer();
        TestContainer<MyAlloc<int, ElNum * 2 + 1>>();
        TestStdVec();
    }
    catch(const std::bad_alloc& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
