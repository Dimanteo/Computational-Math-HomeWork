// Колобаев Дмитрий гр Б01-909
// Вариант Ж

#include "LinearSystem.hpp"
#include "Solvers.hpp"
#include <iostream>

using namespace coma;

static void fillSystem(LinearSystem &LS) {
    double a = 20;
    ssize_t dim = static_cast<ssize_t>(LS.getSize());
    for (ssize_t row = 0; row < dim; row++) {
        for (ssize_t col = row - 4; col <= row + 4; col++) {
            if (col >= 0 && col < dim) {
                LS.matrix(row, col) = 1;
            }
        }
        LS.matrix(row, row) = a;
        LS.consts(row) = static_cast<double>(row + 1);
    }
}

int main() {
    size_t dimension = 10;
    LinearSystem LS(dimension);
    fillSystem(LS);
    LinearSystem LScopy(LS);
    std::cout << LS << "\n";

    Matrix A = LS.matrix();
    Vector F = LS.consts();
    std::cout << "Обусловленность:" << A.norm() * A.adjoint().norm() << "\n";

    std::cout << "Метод Гаусса\n";
    GaussSolver Gsolver(&LS);
    Vector Gx = Gsolver.solve();
    std::cout << Gx << "\n";

    Vector r = A * Gx - F;
    std::cout << "Невязка r\n" << r << "\n";
    std::cout << "Норма невязки ||r||\n" << r.norm() << "\n";

    std::cout << "Метод Зейделя\n";
    fillSystem(LScopy);
    SeidelSolver Ssolver(&LS);
    Vector Sx = Ssolver.solve(1e-3);
    std::cout << Sx << "\n";

    r = A * Sx - F;
    std::cout << "Невязка r\n" << r << "\n";
    std::cout << "Норма невязки ||r||\n" << r.norm() << "\n";
    return 0;
}
