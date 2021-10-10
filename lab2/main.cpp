// Колобаев Дмитрий гр Б01-909
// Вариант Ж

#include <iostream>
#include "LinearSystem.hpp"
#include "Solvers.hpp"

using namespace coma;

static void fillSystem(LinearSystem &LS) {
    double a = 20;
    ssize_t dim = static_cast<ssize_t>(LS.getSize());
    for (ssize_t row = 0; row < dim; row++) {
        for (ssize_t col = row - 4; col <= row + 4; col++) {
            if (col >= 0 && col < dim) {
                LS.matrix()[row][col] = 1;
            }
        }
        LS.matrix()[row][row] = a;
        LS.consts(row) = static_cast<double>(row + 1);
    }
}

int main() {
    size_t dimension = 10;
    LinearSystem LS(dimension);
    fillSystem(LS);
    std::cout << LS;
    GaussSolver solver(&LS);
    Vector v = solver.solve();
    std::cout << v;
    return 0;
}
