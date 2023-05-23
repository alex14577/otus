#include <async/src/queue.h>
#include <types/types.h>

#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace std;

TEST(TestQueue, QueueSimple)
{
     string str = "123";
     size_t id = 1;
     Queue q;
     EXPECT_TRUE(q.Empty());

     q.Push(str.data(), str.size(), Target::All, id);
     EXPECT_FALSE(q.Empty());
     EXPECT_TRUE(q.EmptyById(id + 1));
     EXPECT_FALSE(q.EmptyById(id));
     
     q.Pop(Target::File);
     EXPECT_FALSE(q.EmptyById(id));
     
     auto res = q.Pop(Target::File);
     EXPECT_TRUE(res.second.empty());

     res = q.Pop(Target::Log);
     EXPECT_FALSE(res.second.empty());
     EXPECT_TRUE(q.Empty());
     EXPECT_TRUE(q.EmptyById(id));
     
}

TEST(TestQueue, QueueSimple1)
{
     Queue q;
     EXPECT_TRUE(q.Empty());
     string str = "123";

     q.Push(str.data(), str.size(), Target::All, 1);
     q.Push(str.data(), str.size(), Target::All, 2);
     q.Push(str.data(), str.size(), Target::All, 3);

     auto [id1, str1] = q.Pop(Target::File);
     EXPECT_FALSE(str1.empty());
     EXPECT_EQ(id1, 1);

     auto [id2, str2] = q.Pop(Target::File);
     EXPECT_FALSE(str2.empty());
     EXPECT_EQ(id2, 2);



}