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
     matrix[300][300] = 321;
     matrix[564][521] = 432;

     int count = 0;
     for(auto c: matrix)
     {
     int x, y, v;
     std::tie(x, y, v) = c;
     if ( (x == 100 && y == 100 && v == 314) || 
          (x == 200 && y == 200 && v == 42 ) ||
          (x == 300 && y == 300 && v == 321) ||
          (x == 564 && y == 521 && v == 432)
          )
          count++;
     }

     ASSERT_EQ(count, 4);
     ASSERT_EQ(matrix.size(), 4);
}

TEST(MatrixTest, AddAndDelete) 
{
     constexpr int defVal = -1;
     Matrix<int, defVal> matrix;
     matrix[100][100] = 314;
     matrix[200][200] = 42;
     matrix[300][300] = 321;
     matrix[564][521] = 432;

     ASSERT_EQ(matrix[100][100], 314);
     ASSERT_EQ(matrix[200][200], 42);
     ASSERT_EQ(matrix[300][300], 321);
     ASSERT_EQ(matrix[564][521], 432);

     ASSERT_EQ(matrix.size(), 4);

     matrix[300][300] = defVal;
     ASSERT_EQ(matrix[300][300], defVal);
     ASSERT_EQ(matrix.size(), 3);

     matrix[564][521] = defVal;
     ASSERT_EQ(matrix[564][521], defVal);
     ASSERT_EQ(matrix.size(), 2);

     matrix[100][100] = defVal;
     ASSERT_EQ(matrix[100][100], defVal);
     ASSERT_EQ(matrix.size(), 1);

     matrix[200][200] = defVal;
     ASSERT_EQ(matrix[200][200], defVal);
     ASSERT_EQ(matrix.size(), 0);
}