#include <CoMa.hpp>
#include <Dumper.hpp>
#include <FunctionMatrix.hpp>
#include <RKS.hpp>

using namespace coma;

int main(int argc, char **argv) {
    // Parameters
    numb_t e = 1;
    numb_t t_max = 100;
    numb_t step = 1;
    // Equation system: u' = f(x, z)
    FunctionMatrix f(1, 2);
    f.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        // numb_t x = point(0);
        numb_t z = point(1);
        return z;
    };
    f.func(1, 0) = [&](FunctionMatrix::ArgTy point) {
        numb_t x = point(0);
        numb_t z = point(1);
        return e * (1 - x*x) * z - x;
    };

    // Initial conditions
    Vector init_v(2); // (x, z)
    init_v(0) = 2;
    init_v(1) = 0;

    RungeKuttSolver solver(&f);
    solver.setEulerMethod();
    auto solveTable = solver.solve(init_v, step, static_cast<size_t>(t_max / step));
    std::ofstream ofstr;
    if (argc == 1) {
        ofstr.open("solution.csv");
    } else {
        ofstr.open(argv[1]);
    }
    Dumper::serialize(solveTable, ofstr);
    return 0;
}