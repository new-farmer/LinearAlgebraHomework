#include <Eigen/Dense>
#include <iostream>

Eigen::MatrixXd gramSchmidt(Eigen::MatrixXd basis) {
  for (int i = 0; i < basis.cols(); i++) {
    for (int j = 0; j < i; j++) {
      Eigen::VectorXd proj = basis.col(i).dot(basis.col(j)) /
                             basis.col(j).dot(basis.col(j)) * basis.col(j);
      basis.col(i) = basis.col(i) - proj;
    }
  }
  // 单位化向量
  for (int i = 0; i < basis.cols(); i++) {
    basis.col(i).normalize();
  }
  return basis;

}

// 测试Gram-Schmidt过程
void testGramSchmidt() {
  Eigen::MatrixXd basis1(2, 2);
  basis1 << 2, 1,
            1, 1;
  std::cout << "Orthonormal basis for basis1: \n"
            << gramSchmidt(basis1) << "\n";
  Eigen::MatrixXd basis2(2, 2);
  basis2 << 2, 4,
            3, 5;
  std::cout << "Orthonormal basis for basis2: \n"
            << gramSchmidt(basis2) << "\n";
  Eigen::MatrixXd basis3(3, 3);
  basis3 << 1, 3, -1,
            0, 1, -1,
            1, 1, -1;
  std::cout << "Orthonormal basis for basis3: \n"
            << gramSchmidt(basis3) << "\n";
  Eigen::MatrixXd basis4(4, 3);
  basis4 << 1, -3, -1,
            1, 3, -2,
            5, 4, 2,
            2, -2, 5;

  std::cout << "Orthonormal basis for basis4: \n"
            << gramSchmidt(basis4) << "\n";
}

void testQR() {
  Eigen::Matrix3f A1;
  A1 << 1, 1, 2, 1, 1, 0, 1, 0, 0;
  Eigen::HouseholderQR<Eigen::Matrix3f> qr1(A1);
  Eigen::Matrix3f Q1 = qr1.householderQ();
  Eigen::Matrix3f R1 = qr1.matrixQR().triangularView<Eigen::Upper>();
  std::cout << "Matrix Q1:\n" << Q1 << "\n\n";
  std::cout << "Matrix R1:\n" << R1 << "\n\n";
  std::cout << "Matrix Q1 * R1:\n" << Q1 * R1 << "\n\n";

  Eigen::Matrix3f A2;
  A2 << 2, -1, -1, 2, 0, 2, 2, -1, 3;
  Eigen::HouseholderQR<Eigen::Matrix3f> qr2(A2);
  Eigen::Matrix3f Q2 = qr2.householderQ();
  Eigen::Matrix3f R2 = qr2.matrixQR().triangularView<Eigen::Upper>();
  std::cout << "Matrix Q2:\n" << Q2 << "\n\n";
  std::cout << "Matrix R2:\n" << R2 << "\n\n";
  std::cout << "Matrix Q2 * R2:\n" << Q2 * R2 << "\n\n";
}

int main() {
  testGramSchmidt();
  testQR();

  return 0;
}
