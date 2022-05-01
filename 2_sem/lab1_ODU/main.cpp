#include <CoMa.hpp>
#include <Dumper.hpp>
#include <RKS.hpp>
#include <Adams.hpp>
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
    numb_t step = 0.001;
    // Equation system: u' = f(x, z)
    FunctionMatrix f(1, 2);
    f.func(0, 0) = [](FunctionMatrix::ArgTy point) {
        numb_t t = point(0);
        if (t < 0) {
            return static_cast<numb_t>(0);
        }
        // numb_t x = point(1);
        numb_t z = point(2);
        return z;
    };
    f.func(1, 0) = [&](FunctionMatrix::ArgTy point) {
        numb_t t = point(0);
        if (t < 0) {
            return static_cast<numb_t>(0);
        }
        numb_t x = point(1);
        numb_t z = point(2);
        return e * (1 - x*x) * z - x;
    };

    // Initial conditions
    Vector init_v(2); // (x, z)
    init_v(0) = 2;
    init_v(1) = 0;

    RungeKuttSolver rk_solver(&f);
    std::ofstream ofstr;

    auto solveAndDump = [&](const char *output_csv, ODUSolver &solver) {
        auto solveTable = solver.solve(init_v, step, static_cast<size_t>(t_max / step));
        ofstr.open(output_csv);
        size_t dim = solveTable[0].size() + 1;
        std::vector<Vector> plotData(solveTable.size());
        for (size_t vi = 0; vi < plotData.size(); vi++) {
            plotData[vi].resize(dim);
            plotData[vi] << solveTable[vi], static_cast<numb_t>(vi) * step;
        }
        Dumper::serialize(plotData, ofstr);
        ofstr.close();
    };

    rk_solver.setFirstOrder();
    solveAndDump("rk1.csv", rk_solver);

    rk_solver.setSecondOrder();
    solveAndDump("rk2.csv", rk_solver);

    rk_solver.setThirdOrder();
    solveAndDump("rk3.csv", rk_solver);

    rk_solver.setForthOrder();
    solveAndDump("rk4.csv", rk_solver);

    AdamsSolver a_solver(&f, 2);
    solveAndDump("ad2.csv", a_solver);

    a_solver.setOrder(3);
    solveAndDump("ad3.csv", a_solver);

    a_solver.setOrder(4);
    solveAndDump("ad4.csv", a_solver);

    return 0;
}