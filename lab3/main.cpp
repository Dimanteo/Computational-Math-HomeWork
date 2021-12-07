#include <iostream>
#include <cmath>
#include <CoMa.hpp>
#include <FunctionMatrix.hpp>
#include <Solvers.hpp>

using namespace coma;

int main() {
    numb_t precision = 1e-6;
    NewtonSolver solver(2);
    FunctionMatrix &funcVec = *solver.function();
    FunctionMatrix &jacobian = *solver.jacobian();

    funcVec.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return tan(y - x) + y*x - 0.3;
    };
    funcVec.func(1, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return x*x + y*y - 1.5;
    };

    jacobian.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return -1.0 / pow(cos(y - x), 2) + y;
    };
    jacobian.func(0, 1) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return 1.0 / pow(cos(y - x), 2) + x;
    };
    jacobian.func(1, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        return 2.0 * x;
    };
    jacobian.func(1, 1) = [](FunctionMatrix::ArgTy point) {
        numb_t y = point(1);
        return 2.0 * y;
    };

    // Начальное приближение
    Vector positive_base(2);
    positive_base << 1, 1;
    Vector negative_base(2);
    negative_base << -1, -1;

    
    Vector positive_root = solver.solve(positive_base, precision);
    Vector negative_root = solver.solve(negative_base, precision);

    auto printRoot = [](const Vector v) {
        std::cout.precision(6);
        std::cout << "x = " << v(0) << "\ny = " << v(1) << "\n";
    };
    std::cout << "Positive root:\n";
    printRoot(positive_root);
    std::cout << "Negative root:\n";
    printRoot(negative_root);

    return 0;
}