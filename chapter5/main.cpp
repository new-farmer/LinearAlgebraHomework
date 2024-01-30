#include <Eigen/Dense>
#include <cmath>
#include <iostream>

int main() {
  // 1.定义矩阵
  Eigen::Matrix<double, 2, 10> mat;
  mat << 0, 0, 3, 3, 1, 1, 2, 2, 1, 1,
         0, 5, 5, 4, 4, 3, 3, 2, 2, 0;

  std::cout << "mat:\n" << mat << std::endl;

  // 2.进行缩放
  Eigen::Matrix2d scale_mat;
  scale_mat << 2, 0, 0, 1.5;
  mat = scale_mat * mat;

  std::cout << "mat:\n" << mat << std::endl;

  // 3.顺时针旋转60度
  double angle = 60.0;
  double rad = angle * M_PI / 180.0;
  Eigen::Matrix2d rotate_mat;
  rotate_mat << cos(rad), sin(rad),
               -sin(rad), cos(rad);
  mat = rotate_mat * mat;

  std::cout << "mat:\n" << mat << std::endl;

  // 4.生成4*4单位矩阵
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(4, 4);

  // 5.求矩阵[[1, 2], [3, 4]]的逆矩阵
  Eigen::Matrix2d mat2;
  mat2 << 1, 2, 3, 4;
  Eigen::Matrix2d matInverse = mat2.inverse();

  return 0;
}
