#include <gtest/gtest.h>

#include "../matrix_oop.h"

TEST(TestConstructor, Default) {
  Matrix temp;
  EXPECT_EQ(temp.getRows(), 1);
  EXPECT_EQ(temp.getCols(), 1);
}

TEST(TestConstructor, TwoArguments) {
  Matrix temp(2, 2);
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_EQ(temp.getCols(), 2);
}

TEST(TestConstructor, CopyConstructor) {
  Matrix temp(2, 2);
  temp(1, 1) = 4.0;
  Matrix copy(temp);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 2);
  EXPECT_DOUBLE_EQ(copy(1, 1), temp(1, 1));
}

TEST(TestConstructor, MoveConstructor) {
  Matrix temp(2, 2);
  temp(1, 1) = 4.0;
  Matrix moved(std::move(temp));
  EXPECT_EQ(moved.getRows(), 2);
  EXPECT_EQ(moved.getCols(), 2);
  EXPECT_EQ(temp.getRows(), 0);
  EXPECT_EQ(temp.getCols(), 0);
  EXPECT_DOUBLE_EQ(moved(1, 1), 4.0);
}

TEST(TestConstructor, Assignment) {
  Matrix temp(2, 2);
  temp(1, 1) = 4.0;
  Matrix temp2(3, 3);
  temp2 = temp;
  EXPECT_EQ(temp2.getRows(), 2);
  EXPECT_EQ(temp2.getCols(), 2);
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_EQ(temp.getCols(), 2);
  EXPECT_DOUBLE_EQ(temp(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(temp2(1, 1), 4.0);
}

TEST(TestConstructor, MoveAssignment) {
  Matrix temp(2, 2);
  temp(1, 1) = 4.0;
  Matrix moved(3, 3);
  moved = std::move(temp);
  EXPECT_EQ(moved.getRows(), 2);
  EXPECT_EQ(moved.getCols(), 2);
  EXPECT_EQ(temp.getRows(), 0);
  EXPECT_EQ(temp.getCols(), 0);
  EXPECT_DOUBLE_EQ(moved(1, 1), 4.0);
}

TEST(TestConstructor, Exception1) { EXPECT_ANY_THROW(Matrix(0, 1)); }

TEST(TestConstructor, Exception2) { EXPECT_ANY_THROW(Matrix(0, 0)); }

TEST(TestConstructor, Exception3) { EXPECT_ANY_THROW(Matrix(1, 0)); }

TEST(TestConstructor, Exception4) { EXPECT_ANY_THROW(Matrix(0, -1)); }

TEST(TestConstructor, Exception5) { EXPECT_ANY_THROW(Matrix(-3, 2)); }

TEST(TestMutator, IncreaseSize1) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  temp.setRows(4);
  EXPECT_EQ(temp.getRows(), 4);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(3, 0), 0);
}

TEST(TestMutator, IncreaseSize2) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  temp.setCols(4);
  EXPECT_EQ(temp.getCols(), 4);
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(0, 3), 0);
}

TEST(TestMutator, DecreaseSize1) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  temp.setRows(1);
  EXPECT_EQ(temp.getRows(), 1);
  EXPECT_EQ(temp.getCols(), 2);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(0, 1), 2);
}

TEST(TestMutator, DecreaseSize2) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  temp.setCols(1);
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_EQ(temp.getCols(), 1);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(1, 0), 3);
}

TEST(TestMutator, NoChanges) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  temp.setCols(2);
  temp.setRows(2);
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_EQ(temp.getCols(), 2);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(1, 1), 4);
}

TEST(TestMutator, Exception1) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  EXPECT_ANY_THROW(temp.setRows(0));
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_EQ(temp.getCols(), 2);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(0, 1), 2);
}

TEST(TestMutator, Exception2) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  EXPECT_ANY_THROW(temp.setCols(-1));
  EXPECT_EQ(temp.getRows(), 2);
  EXPECT_EQ(temp.getCols(), 2);
  EXPECT_DOUBLE_EQ(temp(0, 0), 1);
  EXPECT_DOUBLE_EQ(temp(0, 1), 2);
}

TEST(TestIndexation, OutOfRange) {
  Matrix temp(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  EXPECT_ANY_THROW(temp(2, 1) = 5);
  EXPECT_ANY_THROW(temp(2, 2));
  EXPECT_ANY_THROW(temp(-1, 1));
}

TEST(TestEqMatrix, DifferentSizes) {
  Matrix first(2, 2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 1);
  second(0, 0) = 1;
  second(1, 0) = 3;
  EXPECT_FALSE(first.EqMatrix(second));
}
TEST(TestEqMatrixOperator, DifferentSizes) {
  Matrix first(2, 2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 1);
  second(0, 0) = 1;
  second(1, 0) = 3;
  EXPECT_FALSE(first == second);
}

TEST(TestEqMatrix, DifferentElements1) {
  Matrix first(2, 2);
  first(0, 0) = 5.2332892;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 5.2332897;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_FALSE(first.EqMatrix(second));
}

TEST(TestEqMatrixOperator, DifferentElements1) {
  Matrix first(2, 2);
  first(0, 0) = 5.2332892;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 5.2332897;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_FALSE(first == second);
}

TEST(TestEqMatrix, DifferentElements2) {
  Matrix first(2, 2);
  first(0, 0) = 9549845.2332891;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 9549845.2332892;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_FALSE(first.EqMatrix(second));
}

TEST(TestEqMatrixOperator, DifferentElements2) {
  Matrix first(2, 2);
  first(0, 0) = 9549845.2332891;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 9549845.2332892;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_FALSE(first == second);
}

TEST(TestEqMatrix, SameElements1) {
  Matrix first(2, 2);
  first(0, 0) = 5.2332896;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 5.2332896;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_TRUE(first.EqMatrix(second));
}

TEST(TestEqMatrixOperator, SameElements1) {
  Matrix first(2, 2);
  first(0, 0) = 5.2332896;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 5.2332896;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_TRUE(first == second);
}

TEST(TestEqMatrix, SameElements2) {
  Matrix first(2, 2);
  first(0, 0) = 9549845.23328928;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 9549845.23328923;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_TRUE(first.EqMatrix(second));
}

TEST(TestEqMatrixOperator, SameElements2) {
  Matrix first(2, 2);
  first(0, 0) = 9549845.23328928;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix second(2, 2);
  second(0, 0) = 9549845.23328923;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  EXPECT_TRUE(first == second);
}

TEST(TestSumMatrix, DifferentSizes) {
  Matrix first(2, 2);
  Matrix second(2, 1);
  EXPECT_ANY_THROW(first.SumMatrix(second));
}

TEST(TestPlusEqual, DifferentSizes) {
  Matrix first(2, 2);
  Matrix second(2, 1);
  EXPECT_ANY_THROW(first += second);
}

TEST(TestPlus, DifferentSizes) {
  Matrix first(2, 2);
  Matrix second(2, 1);
  EXPECT_ANY_THROW(first + second);
}

TEST(TestSumMatrix, Case1) {
  Matrix first(2, 2);
  first(0, 0) = 5.1;
  Matrix second(2, 2);
  second(0, 0) = 5.2;
  first.SumMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 10.3);
}

TEST(TestPlusEqual, Case1) {
  Matrix first(2, 2);
  first(0, 0) = 5.1;
  Matrix second(2, 2);
  second(0, 0) = 5.2;
  first += second;
  EXPECT_DOUBLE_EQ(first(0, 0), 10.3);
}

TEST(TestPlus, Case1) {
  Matrix first(2, 2);
  first(0, 0) = 5.1;
  Matrix second(2, 2);
  second(0, 0) = 5.2;
  Matrix result = first + second;
  EXPECT_DOUBLE_EQ(result(0, 0), 10.3);
}

TEST(TestSumMatrix, Case2) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  Matrix correct(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + j;
      second(i, j) = 2 * i - 3 * j;
      correct(i, j) = 3 * i - 2 * j;
    }
  }
  first.SumMatrix(second);
  EXPECT_TRUE(first.EqMatrix(correct));
}

TEST(TestPlusEqual, Case2) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  Matrix correct(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + j;
      second(i, j) = 2 * i - 3 * j;
      correct(i, j) = 3 * i - 2 * j;
    }
  }
  first += second;
  EXPECT_TRUE(first.EqMatrix(correct));
}

TEST(TestPlus, Case2) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  Matrix correct(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + j;
      second(i, j) = 2 * i - 3 * j;
      correct(i, j) = 3 * i - 2 * j;
    }
  }
  Matrix result = first + second;
  EXPECT_TRUE(result.EqMatrix(correct));
}

TEST(TestSumMatrix, Case3) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  first.SumMatrix(second);
  EXPECT_TRUE(first.EqMatrix(second));
}

TEST(TestPlusEqual, Case3) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  first += second;
  EXPECT_TRUE(first.EqMatrix(second));
}

TEST(TestPlus, Case3) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  Matrix result = first + second;
  EXPECT_TRUE(result.EqMatrix(second));
}

TEST(TestSubMatrix, DifferentSizes) {
  Matrix first(2, 2);
  Matrix second(2, 1);
  EXPECT_ANY_THROW(first.SubMatrix(second));
}

TEST(TestSubEqual, DifferentSizes) {
  Matrix first(2, 2);
  Matrix second(2, 1);
  EXPECT_ANY_THROW(first -= second);
}

TEST(TestSub, DifferentSizes) {
  Matrix first(2, 2);
  Matrix second(2, 1);
  EXPECT_ANY_THROW(first - second);
}

TEST(TestSubMatrix, Case1) {
  Matrix first(2, 2);
  first(0, 0) = 10;
  Matrix second(2, 2);
  second(0, 0) = 5;
  first.SubMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), 5);
}

TEST(TestSubEqual, Case1) {
  Matrix first(2, 2);
  first(0, 0) = 10;
  Matrix second(2, 2);
  second(0, 0) = 5;
  first -= second;
  EXPECT_DOUBLE_EQ(first(0, 0), 5);
}

TEST(TestSub, Case1) {
  Matrix first(2, 2);
  first(0, 0) = 10;
  Matrix second(2, 2);
  second(0, 0) = 5;
  Matrix result = first - second;
  EXPECT_DOUBLE_EQ(result(0, 0), 5);
}

TEST(TestSubMatrix, Case2) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  first.SubMatrix(second);
  EXPECT_TRUE(first.EqMatrix(second));
}

TEST(TestSubEqual, Case2) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  first -= second;
  EXPECT_TRUE(first.EqMatrix(second));
}

TEST(TestSub, Case2) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  Matrix result = first - second;
  EXPECT_TRUE(result.EqMatrix(second));
}

TEST(TestSubMatrix, Case3) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  Matrix correct(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + j;
      second(i, j) = 2 * i - 3 * j;
      correct(i, j) = -1 * i + 4 * j;
    }
  }
  first.SubMatrix(second);
  EXPECT_TRUE(first.EqMatrix(correct));
}

TEST(TestSubEqual, Case3) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  Matrix correct(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + j;
      second(i, j) = 2 * i - 3 * j;
      correct(i, j) = -1 * i + 4 * j;
    }
  }
  first -= second;
  EXPECT_TRUE(first.EqMatrix(correct));
}

TEST(TestSub, Case3) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  Matrix correct(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + j;
      second(i, j) = 2 * i - 3 * j;
      correct(i, j) = -1 * i + 4 * j;
    }
  }
  Matrix result = first - second;
  EXPECT_TRUE(result.EqMatrix(correct));
}

TEST(TestMulNumber, Zeros) {
  Matrix first(2, 3);
  first.MulNumber(2);
  EXPECT_DOUBLE_EQ(first(0, 0), 0);
}

TEST(TestMulEqualNumberOperator, Zeros) {
  Matrix first(2, 3);
  first *= 2;
  EXPECT_DOUBLE_EQ(first(0, 0), 0);
}

TEST(TestMulNumberOperator, Zeros) {
  Matrix first(2, 3);
  Matrix res1 = first * 2;
  Matrix res2 = 2 * first;
  EXPECT_DOUBLE_EQ(res1(0, 0), 0);
  EXPECT_DOUBLE_EQ(res1(0, 0), res2(0, 0));
}

TEST(TestMulNumber, PositiveNum) {
  Matrix first(2, 3);
  Matrix result(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + 3 * j;
      result(i, j) = 2 * (i + 3 * j);
    }
  }
  first.MulNumber(2);
  EXPECT_TRUE(first.EqMatrix(result));
}

TEST(TestMulEqualNumberOperator, PositiveNum) {
  Matrix first(2, 3);
  Matrix result(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + 3 * j;
      result(i, j) = 2 * (i + 3 * j);
    }
  }
  first *= 2;
  EXPECT_TRUE(first.EqMatrix(result));
}

TEST(TestMulNumberOperator, PositiveNum) {
  Matrix first(2, 3);
  Matrix result(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + 3 * j;
      result(i, j) = 2 * (i + 3 * j);
    }
  }
  Matrix res1 = first * 2;
  Matrix res2 = 2 * first;
  EXPECT_TRUE(res1.EqMatrix(result));
  EXPECT_TRUE(res1.EqMatrix(res2));
  EXPECT_FALSE(res1.EqMatrix(first));
  EXPECT_FALSE(res2.EqMatrix(first));
  EXPECT_FALSE(first.EqMatrix(result));
}

TEST(TestMulNumber, NegativeNum) {
  Matrix first(2, 3);
  Matrix result(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + 3 * j;
      result(i, j) = -2 * (i + 3 * j);
    }
  }
  first.MulNumber(-2);
  EXPECT_TRUE(first.EqMatrix(result));
}

TEST(TestMulEqualNumberOperator, NegativeNum) {
  Matrix first(2, 3);
  Matrix result(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + 3 * j;
      result(i, j) = -2 * (i + 3 * j);
    }
  }
  first *= -2;
  EXPECT_TRUE(first.EqMatrix(result));
}

TEST(TestMulNumberOperator, NegativeNum) {
  Matrix first(2, 3);
  Matrix result(2, 3);
  for (int i = 0; i < first.getRows(); i++) {
    for (int j = 0; j < first.getCols(); j++) {
      first(i, j) = i + 3 * j;
      result(i, j) = -2 * (i + 3 * j);
    }
  }
  Matrix res1 = first * -2;
  Matrix res2 = -2 * first;
  EXPECT_TRUE(res1.EqMatrix(result));
  EXPECT_TRUE(res2.EqMatrix(res1));
  EXPECT_FALSE(res1.EqMatrix(first));
  EXPECT_FALSE(res2.EqMatrix(first));
  EXPECT_FALSE(first.EqMatrix(result));
}

TEST(TestMulMatrix, IncorrectSizes) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  EXPECT_ANY_THROW(first.MulMatrix(second));
}

TEST(TestMulEqualMatrixOperator, IncorrectSizes) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  EXPECT_ANY_THROW(first *= second);
}

TEST(TestMulMatrixOperator, IncorrectSizes) {
  Matrix first(2, 3);
  Matrix second(2, 3);
  EXPECT_ANY_THROW(first * second);
}

TEST(TestMulMatrix, Zeros) {
  Matrix first(2, 3);
  Matrix second(3, 4);
  first.MulMatrix(second);
  EXPECT_DOUBLE_EQ(first(0, 0), second(0, 0));
  EXPECT_EQ(first.getRows(), 2);
  EXPECT_EQ(first.getCols(), 4);
}

TEST(TestMulEqualMatrixOperator, Zeros) {
  Matrix first(2, 3);
  Matrix second(3, 4);
  first *= second;
  EXPECT_DOUBLE_EQ(first(0, 0), second(0, 0));
  EXPECT_EQ(first.getRows(), 2);
  EXPECT_EQ(first.getCols(), 4);
}

TEST(TestMulMatrixOperator, Zeros) {
  Matrix first(2, 3);
  Matrix second(3, 4);
  Matrix result = first * second;
  EXPECT_DOUBLE_EQ(result(0, 0), second(0, 0));
  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 4);
  EXPECT_FALSE(first.EqMatrix(result));
}

TEST(TestMulMatrix, Case1) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  Matrix correct(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      first(i, j) = i + j + 1;
      second(i, j) = i + j + 1;
    }
  }
  correct(0, 0) = 5;
  correct(0, 1) = 8;
  correct(1, 0) = 8;
  correct(1, 1) = 13;
  first.MulMatrix(second);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), correct(i, j));
    }
  }
}

TEST(TestMulEqualMatrixOperator, Case1) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  Matrix correct(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      first(i, j) = i + j + 1;
      second(i, j) = i + j + 1;
    }
  }
  correct(0, 0) = 5;
  correct(0, 1) = 8;
  correct(1, 0) = 8;
  correct(1, 1) = 13;
  first *= second;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      EXPECT_DOUBLE_EQ(first(i, j), correct(i, j));
    }
  }
}

TEST(TestMulMatrixOperator, Case1) {
  Matrix first(2, 2);
  Matrix second(2, 2);
  Matrix correct(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      first(i, j) = i + j + 1;
      second(i, j) = i + j + 1;
    }
  }
  correct(0, 0) = 5;
  correct(0, 1) = 8;
  correct(1, 0) = 8;
  correct(1, 1) = 13;
  Matrix result = first * second;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      EXPECT_DOUBLE_EQ(result(i, j), correct(i, j));
    }
  }
  EXPECT_FALSE(result.EqMatrix(first));
  EXPECT_FALSE(result.EqMatrix(second));
  EXPECT_TRUE(result.EqMatrix(correct));
}

TEST(TestTranspose, Zeros) {
  Matrix first(2, 3);
  Matrix result = first.Transpose();
  EXPECT_EQ(result.getRows(), first.getCols());
}

TEST(TestTranspose, Test1) {
  Matrix first(3, 2);
  Matrix correct(2, 3);
  int counter = 0;
  for (int i = 0; i < first.getCols(); ++i) {
    for (int j = 0; j < first.getRows(); ++j) {
      first(j, i) = ++counter;
    }
  }
  counter = 0;
  for (int i = 0; i < correct.getRows(); i++) {
    for (int j = 0; j < correct.getCols(); j++) {
      correct(i, j) = ++counter;
    }
  }
  Matrix result = first.Transpose();
  EXPECT_TRUE(result.EqMatrix(correct));
}

TEST(TestCalcComplements, Zeros) {
  Matrix first(2, 2);
  Matrix result = first.CalcComplements();
  EXPECT_TRUE(first.EqMatrix(result));
}

TEST(TestCalcComplements, Case1) {
  double first_workpiece[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double correct_workpiece[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  Matrix first(3, 3);
  Matrix correct(3, 3);
  for (int i = 0; i < first.getRows(); ++i) {
    for (int j = 0; j < first.getCols(); ++j) {
      first(i, j) = first_workpiece[i][j];
      correct(i, j) = correct_workpiece[i][j];
    }
  }
  Matrix result = first.CalcComplements();
  for (int i = 0; i < first.getRows(); ++i) {
    for (int j = 0; j < first.getCols(); ++j) {
      EXPECT_DOUBLE_EQ(correct(i, j), result(i, j));
    }
  }
  EXPECT_TRUE(correct.EqMatrix(result));
}

TEST(TestCalcComplements, Case2) {
  double first_workpiece[3][3] = {{1, 8, 3}, {0, 4, 2}, {5, 2, 1}};
  double correct_workpiece[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  Matrix first(3, 3);
  Matrix correct(3, 3);
  for (int i = 0; i < first.getRows(); ++i) {
    for (int j = 0; j < first.getCols(); ++j) {
      first(i, j) = first_workpiece[i][j];
      correct(i, j) = correct_workpiece[i][j];
    }
  }
  Matrix result = first.CalcComplements();
  EXPECT_FALSE(correct.EqMatrix(result));
}

TEST(TestCalcComplements, NotSquare) {
  Matrix first(3, 2);
  EXPECT_ANY_THROW(first.CalcComplements());
}

TEST(TesDeterminant, Zeros) {
  Matrix first(2, 2);
  EXPECT_DOUBLE_EQ(first.Determinant(), 0.0);
  EXPECT_EQ(first.getRows(), 2);
}

TEST(TesDeterminant, NotSquare) {
  Matrix first(3, 2);
  EXPECT_ANY_THROW(first.Determinant());
}

TEST(TesDeterminant, OneElement) {
  Matrix first(1, 1);
  first(0, 0) = 5.0;
  EXPECT_EQ(first.Determinant(), 5.0);
}

TEST(TesDeterminant, 2x2) {
  Matrix first(2, 2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 0;
  first(1, 1) = 4;
  EXPECT_EQ(first.Determinant(), 4.0);
}

TEST(TesDeterminant, 2x2Neg) {
  Matrix first(2, 2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = -3;
  first(1, 1) = 4;
  EXPECT_EQ(first.Determinant(), 10.0);
}

TEST(TesDeterminant, 3x3Counter) {
  Matrix first(3, 3);
  double counter = 0.0;
  for (int i = 0; i < first.getRows(); ++i) {
    for (int j = 0; j < first.getCols(); ++j) {
      first(i, j) = ++counter;
    }
  }
  EXPECT_DOUBLE_EQ(first.Determinant(), 0.0);
}

TEST(TesDeterminant, Test1) {
  Matrix first(3, 3);
  first(0, 0) = 84;
  first(0, 1) = 965.87;
  first(0, 2) = -20;
  first(1, 0) = 8.2;
  first(1, 1) = 54;
  first(1, 2) = 0;
  first(2, 0) = -666.21;
  first(2, 1) = 41;
  first(2, 2) = 55;
  EXPECT_DOUBLE_EQ(first.Determinant(), -912358.17);
}

TEST(TestDeterminant, Test2) {
  Matrix first(4, 4);
  first(0, 0) = 84;
  first(0, 1) = 965.87;
  first(0, 2) = -20;
  first(0, 3) = 0;
  first(1, 0) = 8.2;
  first(1, 1) = 54;
  first(1, 2) = 0;
  first(1, 3) = 0;
  first(2, 0) = -666.21;
  first(2, 1) = 41;
  first(2, 2) = 55;
  first(2, 3) = 0;
  first(3, 0) = 0;
  first(3, 1) = 0;
  first(3, 2) = 0;
  first(3, 3) = 0;
  EXPECT_DOUBLE_EQ(first.Determinant(), 0.0);
}

TEST(TestDeterminant, Test3) {
  Matrix first(4, 4);
  first(0, 0) = 84;
  first(0, 1) = 965.87;
  first(0, 2) = -20;
  first(0, 3) = 4;
  first(1, 0) = 8.2;
  first(1, 1) = 54;
  first(1, 2) = 0;
  first(1, 3) = 51.7;
  first(2, 0) = -666.21;
  first(2, 1) = 41;
  first(2, 2) = 55;
  first(2, 3) = 0;
  first(3, 0) = 0;
  first(3, 1) = 10;
  first(3, 2) = 0;
  first(3, 3) = 2;
  EXPECT_DOUBLE_EQ(first.Determinant(), 2693395.06);
}

TEST(TestInverse, DetEquals0) {
  Matrix first(2, 2);
  EXPECT_ANY_THROW(first.InverseMatrix());
}

TEST(TestInverse, NotSquare) {
  Matrix first(2, 3);
  EXPECT_ANY_THROW(first.InverseMatrix());
}

TEST(TestInverse, Test1) {
  double first_workpiece[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double correct_workpiece[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  Matrix first(3, 3);
  Matrix correct(3, 3);
  for (int i = 0; i < first.getRows(); ++i) {
    for (int j = 0; j < first.getCols(); ++j) {
      first(i, j) = first_workpiece[i][j];
      correct(i, j) = correct_workpiece[i][j];
    }
  }
  Matrix result = first.InverseMatrix();
  EXPECT_TRUE(result.EqMatrix(correct));
}

TEST(TestInverse, Test2) {
  double first_workpiece[3][3] = {{2, 7, 7}, {6, 3, 4}, {5, -2, -3}};
  double correct_workpiece[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  Matrix first(3, 3);
  Matrix correct(3, 3);
  for (int i = 0; i < first.getRows(); ++i) {
    for (int j = 0; j < first.getCols(); ++j) {
      first(i, j) = first_workpiece[i][j];
      correct(i, j) = correct_workpiece[i][j];
    }
  }
  Matrix result = first.InverseMatrix();
  EXPECT_FALSE(result.EqMatrix(correct));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}