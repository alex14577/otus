#include <gtest/gtest.h>
#include <matrix/matrix.h>

TEST(MatrixTest, EmptyMatrix) 
{
  Matrix<int, -1> matrix;
  ASSERT_EQ(matrix.size(), 0);
  ASSERT_EQ(matrix[0][0], -1);
  ASSERT_EQ(matrix.size(), 0);
}

TEST(MatrixTest, SingleElement) 
{
  Matrix<int, -1> matrix;
  matrix[100][100] = 314;
  ASSERT_EQ(matrix[100][100], 314);
  ASSERT_EQ(matrix.size(), 1);
}

TEST(MatrixTest, Iteration) 
{
  Matrix<int, -1> matrix;
  matrix[100][100] = 314;
  matrix[200][200] = 42;

  int count = 0;
  for(auto c: matrix)
  {
    int x, y, v;
    std::tie(x, y, v) = c;
    if ((x == 100 && y == 100 && v == 314) || (x == 200 && y == 200 && v == 42))
      count++;
  }

  ASSERT_EQ(count, 2);
}

TEST(MatrixTest, AddAndDelete) 
{
  Matrix<int, -1> matrix;
  matrix[100][100] = 314;
  ASSERT_EQ(matrix[100][100], 314);
  ASSERT_EQ(matrix.size(), 1);
  matrix[100][100] = -1;
  ASSERT_EQ(matrix.size(), 0);

}