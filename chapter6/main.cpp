#include <Eigen/Eigen>
#include <iostream>
#include <vector>

using namespace Eigen;
using namespace std;
#define EPSILON 1e-8

// 取出列向量对大的数
int GetMaxColIndex(const VectorXd& col) {
  int max_index = 0;
  double max_value = col(0, 0);
  for (int i = 1; i < col.rows(); ++i) {
    if (col(i, 0) > max_value) {
      max_value = col(i, 0);
      max_index = i;
    }
  }
  return max_index;
}

// 调用之前保证，线性方程满秩，具有唯一解
bool GaussJordanElimination(const MatrixXd& A, const VectorXd& b, VectorXd& x) {
  // 打印输入矩阵行列
  int rows = A.rows();
  // 异常判断
  if (A.rows() != b.rows()) {
    cout << "error.";
    return false;
  }

  // forward
  // 构建Ab矩阵
  MatrixXd Ab(rows, A.cols() + 1);
  Ab.block(0, 0, A.rows(), A.cols()) = A;
  Ab.block(0, A.cols(), b.rows(), b.cols()) = b;

  for (int i = 0; i < rows; ++i) {
    // 将最大的那一行提到前边
    int index = GetMaxColIndex(A.block(i, i, rows - i, 1));
    if (index != 0) {
      // 如果不是当前行，进行交换
      MatrixXd Ab_temp = Ab;
      Ab.row(i) = Ab_temp.row(i + index);
      Ab.row(i + index) = Ab_temp.row(i);
    }

    // 将主元归为1
    Ab.row(i) /= Ab(i, i);
    // 消元
    for (int j = i + 1; j < rows; ++j) {
      Ab.row(j) = Ab.row(j) - Ab.row(i) * Ab(j, i);
    }
  }
  // backward
  for (int i = rows - 1; i > 0; --i) {
    for (int j = i - 1; j >= 0; --j) {
      Ab.row(j) = Ab.row(j) - Ab.row(i) * Ab(j, i);
    }
  }
  cout << "Ab: \n" << Ab << endl;
  // x = Ab.col(A.rows());
  // 取出从右边数第一列
  x = Ab.rightCols(1);
  return true;
}

// 适应更一般的线性方程
bool GaussJordanElimination_normal(const MatrixXd& A, const VectorXd& b,
                                   VectorXd& x) {
  // 打印输入矩阵行列
  int rows = A.rows();
  int cols = A.cols();
  // 异常判断
  if (A.rows() != b.rows()) {
    cout << "error.";
    return false;
  }

  // 存储每一行主元的位置
  vector<int> pivots;

  // 构建Ab矩阵
  MatrixXd Ab(rows, A.cols() + 1);
  Ab.block(0, 0, A.rows(), A.cols()) = A;
  Ab.block(0, A.cols(), b.rows(), b.cols()) = b;

  // forward
  int i = 0, k = 0;
  while (i < rows && k < cols) {
    // 看Ab[i][k]位置是否可以是主元
    // 将最大的那一行提到前边
    int index = GetMaxColIndex(A.block(i, k, rows - i, 1));
    if (index != 0) {
      // 如果不是当前行，进行交换
      MatrixXd Ab_temp = Ab;
      Ab.row(i) = Ab_temp.row(i + index);
      Ab.row(i + index) = Ab_temp.row(i);
    }

    // 判断i,k主元为0
    if (abs(Ab(i, k)) < EPSILON) {
      ++k;
      continue;
    }

    // 将主元归为1
    Ab.row(i) /= Ab(i, k);
    // 消元
    for (int j = i + 1; j < rows; ++j) {
      Ab.row(j) = Ab.row(j) - Ab.row(i) * Ab(j, k);
    }
    pivots.push_back(k);
    ++i;
    ++k;
  }

  // backward
  // 非零行的元素个数
  int n = pivots.size();
  for (int i = n - 1; i > 0; --i) {
    // 取出主元位置
    int k = pivots[i];
    for (int j = i - 1; j >= 0; --j) {
      Ab.row(j) = Ab.row(j) - Ab.row(i) * Ab(j, k);
    }
  }
  cout << "Ab: \n" << Ab << endl;
  for (int i = pivots.size(); i < rows; ++i) {
    if (Ab(i, cols) != 0) {
      cout << "无解" << endl;
      return false;
    }
  }
  // 取出从右边数第一列
  x = Ab.rightCols(1);
  cout << "有解" << endl;
  return true;
}

int main(int argc, char** argv) {
  Matrix3d A;
  A << 1., 2., 4., 3., 7., 2., 2., 3., 3.;
  Vector3d b(7., -11., 1.);
  VectorXd x;

  // 使用高斯约旦消元法
  if (GaussJordanElimination(A, b, x)) {
    cout << "use gaussJordanElimination solve: \n" << x << endl;
  }

  Matrix<double, 4, 5> AA;
  AA << 1, -1, 2, 0, 3, -1, 1, 0, 2, -5, 1, -1, 4, 2, 4, -2, 2, -5, -1, -3;
  Vector4d bb(1, 5, 13, -1);
  VectorXd xx;
  // 使用高斯约旦消元法
  if (GaussJordanElimination_normal(AA, bb, xx)) {
    cout << "use GaussJordanElimination_normal solve: \n" << xx << endl;
  }
}