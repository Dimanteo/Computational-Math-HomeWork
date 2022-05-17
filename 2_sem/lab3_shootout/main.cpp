#include <RKS.hpp>
#include <Dumper.hpp>
#include <Solvers.hpp>
#include <iostream>

using namespace coma;

int main(int argc, char **argv) {
    numb_t precision = 1e-6;
    constexpr numb_t step = 0.001;
    constexpr numb_t param_step = step;
    constexpr numb_t x_max = 1;
    if (argc >= 2) {
        char *endptr = 0;
        precision = strtod(argv[1], &endptr);
        if (endptr == argv[1]) {
            fprintf(stderr, "Invalid precision\n");
            return EXIT_FAILURE;
        }
    }

    // (x, y, p)
    FunctionMatrix f(1, 2);
    f.func(0, 0) = [&](FunctionMatrix::ArgTy point) {
        numb_t p = point(2);
        return p;
    };
    f.func(1, 0) = [&](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t y = point(1);
        return x * sqrt(y);
    };

    RungeKuttSolver ode_solver(&f);
    ode_solver.setSecondOrder();
    std::vector<Vector> solution;

    NewtonSolver newt_solver(1);
    FunctionMatrix &F = *newt_solver.function();
    FunctionMatrix &J = *newt_solver.jacobian();

    J.func(0, 0) = [&](FunctionMatrix::ArgTy point) {
        auto shift_point = point;
        shift_point(0) += param_step;
        return (F.func(0, 0)(shift_point) - F.func(0, 0)(point)) / param_step;
    };

    for (int var = 1; var <= 2; var++) {
        if (var == 1) {
            std::cout << "Variant A:\n";
            F.func(0, 0) = [&](FunctionMatrix::ArgTy point) {
                numb_t param = point(0);
                Vector init(2);
                init << 0, param;
                solution = ode_solver.solve(init, step, static_cast<size_t>(x_max / step));
                return solution.back()(0) - 2;
            };
        } else {
            std::cout << "Variant B:\n";
            F.func(0, 0) = [&](FunctionMatrix::ArgTy point) {
                numb_t param = point(0);
                Vector init(2);
                init << 0, param;
                solution = ode_solver.solve(init, step, static_cast<size_t>(x_max / step));
                numb_t integral = 0;
                for (auto pt : solution) {
                    integral += pt(0) * step;
                }
                return integral - 1;
            };
        }
        Vector base(1);
        base << 1;
        Vector alpha = newt_solver.solve(base, precision);

        std::cout << "Deduced initial parameter : y' = " << alpha(0) << "\n";

        Vector res_init(2);
        res_init << 0, alpha(0);
        solution = ode_solver.solve(res_init, step, static_cast<size_t>(x_max / step));

        std::ofstream ofstr;
        std::string filename = (var == 1) ? "resA.csv" : "resB.csv";
        ofstr.open(filename);
        Dumper::serialize(solution, ofstr);
        ofstr.close();
    }
    return EXIT_SUCCESS;
}