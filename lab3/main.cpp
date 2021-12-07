#include <CoMa.hpp>
#include <FunctionMatrix.hpp>
#include <Solvers.hpp>
#include <cmath>
#include <iostream>

using namespace coma;

void printRoot(const Vector &v) { std::cout << "x = " << v(0) << "\ny = " << v(1) << "\n"; };

void task12_2() {
    std::cout << "## Задача 12.2 ##\n";

    NewtonSolver solver(2);
    FunctionMatrix &funcVec = *solver.function();
    FunctionMatrix &jacobian = *solver.jacobian();

    funcVec.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return tan(y - x) + y * x - 0.3;
    };
    funcVec.func(1, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return x * x + y * y - 1.5;
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

    numb_t precision = 1e-6;
    ;
    // Начальное приближение
    Vector positive_base(2);
    positive_base << 1, 1;
    Vector negative_base(2);
    negative_base << -1, -1;

    Vector positive_root = solver.solve(positive_base, precision);
    Vector negative_root = solver.solve(negative_base, precision);

    std::cout.precision(6);
    std::cout << "Positive root:\n";
    printRoot(positive_root);
    std::cout << "Negative root:\n";
    printRoot(negative_root);
}

void task12_7() {
    std::cout << "## Задача 12.7(г) ##\n";

    NewtonSolver solver(2);
    FunctionMatrix &funcVec = *solver.function();
    FunctionMatrix &jacobian = *solver.jacobian();

    funcVec.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return sin(x) - y - 1.32;
    };
    funcVec.func(1, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return cos(y) - x + 0.85;
    };

    jacobian.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        return cos(x);
    };
    jacobian.func(0, 1) = [](FunctionMatrix::ArgTy point) { return -1; };
    jacobian.func(1, 0) = [](FunctionMatrix::ArgTy point) { return -1; };
    jacobian.func(1, 1) = [](FunctionMatrix::ArgTy point) {
        numb_t y = point(1);
        return -sin(y);
    };

    numb_t precision = 1e-5;
    Vector base(2);
    base << 1.5, -0.5;
    Vector root = solver.solve(base, precision);

    std::cout.precision(5);
    std::cout << "Root:\n";
    printRoot(root);
}

int main() {
    task12_2();
    task12_7();
    return 0;
}