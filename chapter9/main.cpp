#include <iostream>
#include <Eigen/Dense>

int GaussJordan(Eigen::MatrixXd& A) {
    int rows = A.rows();
    int cols = A.cols();
    int rank = 0;
    for(int r=0, c=0; r<rows && c<cols; ++c) {
        int pivot = r;
        for(int i=r+1; i<rows; ++i) {
            if(std::abs(A(i,c)) > std::abs(A(pivot,c))) {
                pivot = i;
            }
        }
        if(std::abs(A(pivot,c)) < 1e-10) {
            continue;
        }
        A.row(r).swap(A.row(pivot));
        A.row(r) /= A(r, c);
        for(int i=0; i<rows; ++i) {
            if(i != r) {
                A.row(i) -= A.row(r) * A(i,c);
            }
        }
        ++r;
        ++rank;
    }
    return rank;
}

int main() {
    Eigen::MatrixXd A(4,5);
    A << 1, -1, 2, 0, 3,
        -1, 1, 0, 2, -5,
        1, -1, 4, 2, 4,
        -2, 2, -5, -1, -3;

    std::cout << "Rank of A using Eigen: " << A.fullPivLu().rank() << std::endl;

    std::cout << "Rank of A using Gauss-Jordan: " << GaussJordan(A) << std::endl;

    return 0;
}
