#include <my_container/my_container.h>

#include <gtest/gtest.h>

class MyContainer : public ::testing::Test
{
protected:
	void SetUp()
	{
	}
	void TearDown()
	{

	}
};


using namespace std;
using namespace my_container;

TEST_F(MyContainer, ConstructorFirstLast)
{
    Container<int> src;
    
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);    
    
    Container dst(src.begin(), src.end());

    EXPECT_EQ(src, dst);

}
