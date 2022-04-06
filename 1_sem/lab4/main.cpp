// VII.9.5(a)
// Вообще говоря может решать любой вариант в зависимости от входного файла
#include <Integrator.hpp>
#include <TableFunction.hpp>
#include <iostream>
#include <vector>

using namespace coma;

FILE *openFile(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: Wrong options. Usage: %s <filename>\n", argv[0]);
    }
    FILE *fptr = fopen(argv[1], "r");
    if (!fptr) {
        fprintf(stderr, "ERROR: Failed to open file %s\n", argv[1]);
    }
    return fptr;
}

// Input file format
// x , f(x)
void parseData(FILE *fptr, TableFunction &func) {
    numb_t f = NAN, x = NAN;

    while (!feof(fptr)) {
        fscanf(fptr, "%lf,%lf\n", &x, &f);
        func.insert(x, f);
    }
}

int main(int argc, char **argv) {
    TableFunction func;
    auto fptr = openFile(argc, argv);
    parseData(fptr, func);
    fclose(fptr);

    numb_t integral = Integrator::trapezoidal(func);
    numb_t sparse = Integrator::trapezoidal(func, 2);
    numb_t delta = Integrator::rungeDeviation(integral, sparse, 2, 2);
    std::cout << "Метод трапеций: " << integral << "\n";
    std::cout << "Экстраполяция Ричардсона: " << integral + delta << "\n";
    std::cout << "Метод Симпсона: " << Integrator::simpson(func) << "\n";
    return 0;
}