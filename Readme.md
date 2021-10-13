# Лабораторные работы по вычислительной математике
Код выполняющий задание находится в папке `lab2`, а используемые алгоритмы выделены в отдельный git submodule Computational-Math. Алгоритмы Гаусса и Зейделя описаны в файле `Solver.cpp`. Вывод программы приведен в файле **lab2/output.txt**.

* Чтобы увидеть Solver.cpp сначала надо сделать `git submodule init && git submodule update`

Чтобы собрать проект используйте скрипт **build.sh** или вручную проделайте следующее
```bash
git submodule init # инициализирует сабмодули
git submodule update # скачивает код библиотеки
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
```
В результате в папке build будет лежать исполняемый файл lab2.out, который решает задачу из лабораторной.
