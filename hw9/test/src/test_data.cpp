#include <async/src/queue.h>
#include <types/types.h>

#include <gtest/gtest.h>

#include <string>

using namespace std;

TEST(TestData, DataTargetRemain1)
{
     Data data("123", Target::All, 1);
     EXPECT_EQ(data.GetTargetRemain(), Target::All);

     data.ResetTarget(Target::File);
     EXPECT_EQ(data.GetTargetRemain(), Target::Log);     
}

TEST(TestData, DataTargetRemain2)
{
     Data data("123", Target::All, 1);
     EXPECT_EQ(data.GetTargetRemain(), Target::All);

     data.ResetTarget(Target::Log);
     EXPECT_EQ(data.GetTargetRemain(), Target::File);     
}

TEST(TestData, DataTargetRemain3)
{
     Data data("123", Target::All, 1);
     EXPECT_EQ(data.GetTargetRemain(), Target::All);

     data.ResetTarget(Target::Log);
     EXPECT_EQ(data.GetTargetRemain(), Target::File);
     data.ResetTarget(Target::File);
     EXPECT_EQ(data.GetTargetRemain(), Target::NoTarget);
}

TEST(TestData, DataGetId)
{
     for(size_t i = 0; i < 1000; i++)
     {
          Data data("123", Target::All, i);
          EXPECT_EQ(data.GetId(), i);
     }
}

TEST(TestData, DataString)
{
     for(size_t i = 0; i < 1000; i++)
     {
          string str = to_string(i * 123);
          Data data(str, Target::All, i);
          EXPECT_EQ(data.String(), str);
     }
}
