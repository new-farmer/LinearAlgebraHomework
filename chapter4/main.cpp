#include <Eigen/Eigen>
#include <cmath>
#include <iostream>

int main() {
  // 定义一个矩阵
  Eigen::MatrixXf m = Eigen::MatrixXf::Random(3, 3);
  std::cout << "m:" << m << std::endl;

  // 获取矩阵的行数和列数
  std::cout << "rows: " << m.rows() << std::endl;
  std::cout << "cols: " << m.cols() << std::endl;

  // 获取矩阵元素的数量
  std::cout << "m_size: " << m.size() << std::endl;

  // 取出矩阵某一行的行向量
  Eigen::RowVectorXf row_vector = m.row(1);
  std::cout << "row_vector: " << row_vector << std::endl;

  // 取出矩阵某一列的列向量
  Eigen::VectorXf column_vector = m.col(1);
  std::cout << "column_vector:" << column_vector << std::endl;

  // 求矩阵的幂
  Eigen::MatrixXf m_n = m * m * m;
  std::cout << "m^n: " << m_n << std::endl;

  // 求矩阵的转置
  Eigen::MatrixXf m_transposed = m.transpose();
  std::cout << "transposed:" << m_transposed << std::endl;

  std::cout << "------" << std::endl;

  return 0;
}
