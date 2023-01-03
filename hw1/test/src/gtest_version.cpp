#include <hw1/lib/lib.h>

#include <gtest/gtest.h>

using namespace std;

TEST(Lib, IsVersionValid) {
  ASSERT_GT(version(), 1);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
