# Data Analysis Library

This repo contains some data analysis objects that should help with the statistics generated from Monte Carlo simulations.

## Source structure
The `src` folder has the following substructure
```bash
src
|----DataStream
|    |----Tests
|
|----Statistics
     |----Tests
```
Each subfolder houses different base and derived classes that contain convenient numerical routines.

### Source Subfolder Overview
1. [**DataStream**](src/DataStream/): contiguous container for data with a couple other features.
2. [**Statistics**](src/Statistics/): currently only `Measures_of_Center`.

## Installation Instructions

Each subfolder is a separate header-only library whose names are prepended with `Data_Analysis_`. For example, the `DataStream` library is named `Data_Analysis_DataStream`. The installation instructions with CMake's `find_package()` are as follows.

First, clone the repo, then:

```bash
cd <Data Analysis parent>
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<Data Analysis Installation Location> ..
cmake --build .
cmake --install .
```

Then this library can be implemented with `find_package(Data_Analysis_<Library Name>)` when the installation location is added to the `PATH`, or by configuring CMake with `-DCMAKE_PREFIX_PATH=<Data Analysis Installation Location>`.

