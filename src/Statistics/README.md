# Statistics Library

This is a summary overview of the tested types named in this library. All types are defined within the `Statistics` `namespace`. 

## Bootstrapper
```c++
class Bootstrapper<data_t>
```
This class uses the bootstrap resamping technique to compute sampling statistics from a finite number of _statistically independent_ measurements.

The bootstrap is conventionally used to calculate the resampled mean and standard error, however, it can be used to calculate the mean of any statistic and estimate its standard error. 

## Measures of Center
```c++
class Measures_of_Center<input_type, output_type = input_type>;
```
This class calculates the 

* `mean`: arithmetic mean
* `variance`: population mean-square deviation
    * The `standard_deviation` and `standard_errors` are members that exploit the known `variance`.
* `skewness`: population E(Z^3)
* `kurtosis`: population E(Z^4)

of a contiguous data set. E is the expectation value over the data set, and Z is defined by Z = (x - mu) / sigma, where mu is the mean and sigma is the standard deviation.

It also stores whether each measure has been computed yet with an array of `uint8_t`. Additionally, it can compute them all in an iterable manner by storing and array of function pointers. Other members include