# Data Analysis Library

This repo contains some data analysis objects that should help with the statistics generated from Monte Carlo simulations.

## Source structure
The `src` folder has the following substructure
```bash
src
|
|----DataFiles
|
|----DataStream
|    |----Tests
|
|----Statistics
     |----Tests
```
Each subfolder houses different base and derived classes that contain convenient numerical routines.

### Source Subfolder Overview
1. [**DataFiles**](src/DataFiles/): convenient data structures for housing CSV-type data as well as file parsing and writing.
1. [**DataStream**](src/DataStream/): contiguous container for data with a couple other features.
1. [**Statistics**](src/Statistics/): `Measures_of_Center` and `Bootstrapper` classes.

## Installation Instructions

This library is header-only, but the installation of the headers will be broken up into the subfolders shown above for downstream compatibility. The library is named `Data_Analysis`. The installation instructions with CMake's `find_package()` are as follows.

First, clone the repo, then:

```bash
cd <Data Analysis parent>
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<Data Analysis Installation Location> ..
cmake --build .
cmake --install .
```

Then this library can be implemented with `find_package(Data_Analysis)` when the installation location is added to the `PATH`, or by configuring CMake with `-DCMAKE_PREFIX_PATH=<Data Analysis Installation Location>`. 

A minimal CMake example is given below:

```cmake
...
add_executable(Example main.cpp)
find_package(Data_Analysis REQUIRED)
target_link_libraries(Example Data_Analysis::Data_Analysis)
...
```

The corresponding `C++` file that includes the `Measures_of_Center` calculator out of the `Statistics` library, for example, is shown below

```c++
// Example -- main.cpp

#include <Statistics/measures_of_center.hpp> // Include MoC header library

int main(int, char **)
{
     Statistics::Measures_of_Center<double> mocd;
     return 0;
}
```

