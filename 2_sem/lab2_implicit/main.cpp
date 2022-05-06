#include <CoMa.hpp>
#include <Dumper.hpp>
#include <RKS.hpp>
#include <stdlib.h>
#include <iostream>

using namespace coma;

int main(int argc, char **argv) {
    // E5 problem
    numb_t t_max = 1e3;
    numb_t step = 0.001;
    constexpr numb_t A = 7.89 * 1e-10;
    constexpr numb_t B = 1.1 * 1e7;
    constexpr numb_t C = 1.13 * 1e3;
    constexpr numb_t M = 1e6;
    if (argc >= 2) {
        char *endptr = 0;
        t_max = strtod(argv[1], &endptr);
        if (endptr == argv[1]) {
            fprintf(stderr, "Invalid time specified\n");
            return EXIT_FAILURE;
        }
        if (argc >= 3) {
            step = strtod(argv[2], &endptr);
            if (endptr == argv[2]) {
                fprintf(stderr, "Invalid time specified\n");
                return EXIT_FAILURE;
            }
        }
    }
    std::cout << "Solving for T = " << t_max << "; h = " << step << "\n";

    // Initial conditions
    Vector init_v(4);
    init_v << 1.76 * 1e-3, 0, 0, 0;

    // Equation system
    FunctionMatrix f(1, 4);
    // point (t, y_1 ... y_4)
    f.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t y1 = point(1);
        numb_t y3 = point(3);
        return -A*y1 * - B*y1*y3;
    };
    f.func(1, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t y1 = point(1);
        numb_t y2 = point(2);
        numb_t y3 = point(3);
        return A*y1 - M*C*y2*y3;
    };
    f.func(2, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t y1 = point(1);
        numb_t y2 = point(2);
        numb_t y3 = point(3);
        numb_t y4 = point(4);
        return A*y1 - B*y1*y3 - M*C*y2*y3 + C*y4;
    };
    f.func(3, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t y1 = point(1);
        numb_t y3 = point(3);
        numb_t y4 = point(4);
        return B*y1*y3 - C*y4;
    };

    // FunctionMatrix j(4, 4);
    // j.func(0, 0) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y3 = point(3);
    //     return -A - B*y3;
    // };
    // j.func(0, 1) = [](FunctionMatrix::ArgTy point) {
    //     return 0;
    // };
    // j.func(0, 2) = [](FunctionMatrix::ArgTy point) {
    //     return -B;
    // };
    // j.func(0, 3) = [](FunctionMatrix::ArgTy point) {
    //     return 0;
    // };
    // j.func(1, 0) = [](FunctionMatrix::ArgTy point) {
    //     return A;
    // };
    // j.func(1, 1) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y3 = point(3);
    //     return -M*C*y3;
    // };
    // j.func(1, 2) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y2 = point(2);
    //     return -M*C*y2;
    // };
    // j.func(1, 3) = [](FunctionMatrix::ArgTy point) {
    //     return 0;
    // };
    // j.func(2, 0) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y3 = point(3);
    //     return A - B*y3;
    // };
    // j.func(2, 1) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y3 = point(3);
    //     return -M*C*y3;
    // };
    // j.func(2, 2) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y1 = point(1);
    //     numb_t y2 = point(2);
    //     return -B*y1 - M*C*y2;
    // };
    // j.func(2, 3) = [](FunctionMatrix::ArgTy point) {
    //     return C;
    // };
    // j.func(3, 0) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y3 = point(3);
    //     return B*y3;
    // };
    // j.func(3, 1) = [](FunctionMatrix::ArgTy point) {
    //     return 0;
    // };
    // j.func(3, 2) = [](FunctionMatrix::ArgTy point) {
    //     numb_t y1 = point(1);
    //     return B*y1;
    // };
    // j.func(3, 3) = [](FunctionMatrix::ArgTy point) {
    //     return -C;
    // };

    RungeKuttSolver rk_solver(&f);
    std::ofstream ofstr;

    auto solveAndDump = [&](const char *output_csv, ODUSolver &solver) {
        auto solveTable = solver.solve(init_v, step, static_cast<size_t>(t_max / step), 10000);
        ofstr.open(output_csv);
        Dumper::serialize(solveTable, ofstr);
        ofstr.close();
    };

    rk_solver.setImplicit();
    solveAndDump("implicit.csv", rk_solver);

    return EXIT_SUCCESS;
}