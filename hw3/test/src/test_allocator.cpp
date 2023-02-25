#include <my_allocator/allocator.h>

#include <gtest/gtest.h>

#include <vector>
#include <cmath>

using namespace std;
using namespace my_alloc;

constexpr auto testSet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

using ValueType = int;
constexpr size_t valNum = 10;
using AllocT = MyAlloc<ValueType, testSet.size() * 10>;
using Vec = vector<ValueType, AllocT>;


class Alloc : public ::testing::Test
{
protected:
	void SetUp()
	{
		alloc = new AllocT;
	}
	void TearDown()
	{
		delete alloc;
	}
	AllocT* alloc;
};

TEST_F(Alloc, VectorPushBack)
{
    Vec v{*alloc};
    for(auto val : testSet)
    {
        v.push_back(val);
    }

    for(auto val : testSet)
    {
        ASSERT_EQ(v[val] , val);        
    }
}

TEST_F(Alloc, VectorCopyCtr)
{
    auto addVal = +[](Vec v, ValueType val) -> Vec
    {
        v.push_back(val);
        return v;
    };

    Vec v(*alloc);
    for(auto val : testSet)
    {
       v = addVal(v, val);
    }

    for(auto val : testSet)
    {
        ASSERT_EQ(v[val] , val);        
    }
    ASSERT_EQ(v.size() ,testSet.size());
}

TEST_F(Alloc, Map)
{
    constexpr size_t valNum = 10;
    using AllocMap = MyAlloc<std::pair<const ValueType, ValueType>, valNum>;
    map<ValueType, ValueType, less<ValueType>, AllocMap> m;

    m[0] = 1;
    for(unsigned long i = 1; i < valNum; ++i)
    {
        m[i] = m[i - 1] * (i + 1);
    }

    auto factorils = {1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

    auto it = factorils.begin();
    for(unsigned long i = 0; i < valNum; ++i)
    {
        ASSERT_EQ(m[i] , *it);
        ++it;
    }
}