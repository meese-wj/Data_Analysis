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
1. [**DataStream**](src/DataStream/README.md): contiguous container for data with a couple other features.
2. [**Statistics**](src/Statistics/README.md): currently only _Measures-of-Center_.
