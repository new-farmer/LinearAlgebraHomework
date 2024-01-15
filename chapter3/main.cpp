#include <Eigen/Eigen>
#include <cmath>
#include <iostream>

int main() {
  Eigen::Vector3f vec1(3, 4, 0);
  Eigen::Vector3f vec2(-6, -8, 0);

  // 1.计算向量的模
  float norm = vec1.norm();
  std::cout << "norm: " << norm << std::endl;

  // 2.对向量进行归一化
  Eigen::Vector3f vec1_normalized = vec1.normalized();
  std::cout << "vec1 normalized : \n" << vec1_normalized << std::endl;

  // 3.向量的点乘
  float dot = vec1.dot(vec2);
  std::cout << "dot: " << dot << std::endl;

  // 4.计算两个向量的夹角
  float rad = std::acos(vec1.normalized().dot(vec2.normalized()));
  std::cout << "rad: " << rad << std::endl;

  // 5.计算一个向量到另一个向量投影点的坐标
  Eigen::Vector3f project = vec1.dot(vec2) / vec2.squaredNorm() * vec2;
  std::cout << "project: " << project.transpose() << std::endl;

  std::cout << "------" << std::endl;

  return 0;
}
