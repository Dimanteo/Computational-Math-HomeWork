git submodule init
git submodule update
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make