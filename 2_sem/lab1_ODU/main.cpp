#include <CoMa.hpp>
#include <Dumper.hpp>
#include <FunctionMatrix.hpp>
#include <RKS.hpp>
#include <stdlib.h>
#include <iostream>

using namespace coma;

int main(int argc, char **argv) {
    // Parameters
    if (argc < 2) {
        std::cerr << "Enter parameter e\n";
        exit(1);
    }
    numb_t e = strtold(argv[1], nullptr);
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
    ofstr.open("rc1.csv");
    // Add t to Vector
    size_t dim = solveTable[0].size() + 1;
    std::vector<Vector> plotData(solveTable.size());
    for (size_t vi = 0; vi < plotData.size(); vi++) {
        plotData[vi].resize(dim);
        plotData[vi](0) = step * vi;
        for (size_t c = 1; c < dim; c++) {
            plotData[vi](c) = solveTable[vi](c - 1);
        }
    }
    Dumper::serialize(plotData, ofstr);
    return 0;
}