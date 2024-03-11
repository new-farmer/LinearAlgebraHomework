#include <Eigen/Dense>
#include <iostream>

Eigen::MatrixXd gaussJordan(Eigen::MatrixXd matrix) {
  int n = matrix.rows();  // 假设矩阵是方阵
  Eigen::MatrixXd identity = Eigen::MatrixXd::Identity(n, n);
  Eigen::MatrixXd InvMatrix;

  // 将单位矩阵拼接到输入矩阵后面
  Eigen::MatrixXd AugmentedMatrix(n, 2 * n);
  AugmentedMatrix << matrix, identity;

  for (int i = 0; i < n; i++) {
    // 如果对角线元素是0，交换行
    if (AugmentedMatrix(i, i) == 0) {
      for (int j = i + 1; j < n; j++) {
        if (AugmentedMatrix(j, i) != 0) {
          AugmentedMatrix.row(i).swap(AugmentedMatrix.row(j));
          break;
        }
      }
    }

    // 将当前行归一化
    AugmentedMatrix.row(i) = AugmentedMatrix.row(i) / AugmentedMatrix(i, i);

    for (int j = 0; j < n; j++) {
      // 对非对角线元素，消元
      if (i != j) {
        float ratio = AugmentedMatrix(j, i) / AugmentedMatrix(i, i);
        AugmentedMatrix.row(j) -= ratio * AugmentedMatrix.row(i);
      }
    }
  }

  // 得到逆矩阵
  InvMatrix = AugmentedMatrix.block(0, n, n, n);

  return InvMatrix;
}

std::pair<Eigen::MatrixXd, Eigen::MatrixXd> LU_decomposition(
    Eigen::MatrixXd matrix) {
  int n = matrix.rows();
  Eigen::MatrixXd L = Eigen::MatrixXd::Zero(n, n);
  Eigen::MatrixXd U = Eigen::MatrixXd::Zero(n, n);

  for (int i = 0; i < n; ++i) {
    L(i, i) = 1;

    for (int j = i; j < n; ++j) {
      U(i, j) = matrix(i, j);
      for (int k = 0; k < i; ++k) {
        U(i, j) -= L(i, k) * U(k, j);
      }
    }

    for (int j = i + 1; j < n; ++j) {
      L(j, i) = matrix(j, i);
      for (int k = 0; k < i; ++k) {
        L(j, i) -= L(j, k) * U(k, i);
      }
      L(j, i) /= U(i, i);
    }
  }

  return {L, U};
}

int main() {
  Eigen::MatrixXd A(2, 2);
  A << 1, 2, 3, 4;

  // 1.使用高斯-约旦消元法计算逆矩阵
  Eigen::MatrixXd AI, AI_eigen;
  AI = gaussJordan(A);
  std::cout << "矩阵A的逆矩阵AI是：\n" << AI << std::endl;
  AI_eigen = A.inverse();
  std::cout << "矩阵A的逆矩阵AI_eigen是：\n" << AI_eigen << "\n";

  // 2. 编程实现LU分解方阵：
  Eigen::Matrix3d AA;
  AA << 1, 2, 3, 4, 5, 6, 3, -3, 5;
  auto M = LU_decomposition(AA);
  std::cout << "Matrix L:\n" << M.first << "\n\n";
  std::cout << "Matrix U:\n" << M.second << "\n\n";
  std::cout << "Matrix AA:\n" << M.first * M.second << "\n\n";

  // 3. 使用eigen库PLU分解AA：
  Eigen::PartialPivLU<Eigen::Matrix3d> plu(AA);
  Eigen::Matrix3d L = plu.matrixLU().triangularView<Eigen::UnitLower>();
  Eigen::Matrix3d U = plu.matrixLU().triangularView<Eigen::Upper>();
  Eigen::Matrix3d P = AA * (L * U).inverse();
  std::cout << "Matrix P:\n" << P << "\n\n";
  std::cout << "Matrix L:\n" << L << "\n\n";
  std::cout << "Matrix U:\n" << U << "\n\n";
  std::cout << "matrix AA:\n" << P * L * U << std::endl;

  // 3. 使用eigen库PLUP分解AA： 
  Eigen::FullPivLU<Eigen::Matrix3d> lu(AA);
  U = lu.matrixLU().triangularView<Eigen::Upper>();
  L = lu.matrixLU().triangularView<Eigen::UnitLower>();
  P = lu.permutationP();
  Eigen::Matrix3d Q = lu.permutationQ();
  std::cout << "L = \n" << L << std::endl;
  std::cout << "U = \n" << U << std::endl;
  std::cout << "P = \n" << P << std::endl;
  std::cout << "Q = \n" << Q << std::endl;
  std::cout << "重构原始矩阵后的结果为：\n"
       << P.inverse() * L * U * Q.inverse() << std::endl;

  return 0;
}
