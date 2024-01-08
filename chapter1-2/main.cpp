#include <Eigen/Eigen>
#include <iostream>

int main() {
  // 1.矩阵定义
  Eigen::Matrix<double, 3, 3> a;
  a(0, 0) = 0;
  Eigen::MatrixXd b(4, 4);
  b(1, 1) = 1;
  Eigen::Matrix3f c;

  // 2.零矩阵零向量
  Eigen::MatrixXd d = Eigen::MatrixXd::Zero(3, 3);
  Eigen::VectorXd v(3);
  v.setZero();

  // 3.访问矩阵元素
  d(2, 2) = 22;

  // 4.运算
  a.setIdentity();
  Eigen::MatrixXd e = a + d;
  Eigen::MatrixXd f = d - a;
  Eigen::MatrixXd g = a * d;
  Eigen::MatrixXd h = d.transpose();
  Eigen::MatrixXd i = e * 0.5;

  std::cout << "i:" << std::endl;

  std::cout << i << std::endl;

  std::cout << "main finish..." << std::endl;
  return 0;
}