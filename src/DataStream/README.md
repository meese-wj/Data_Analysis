# DataStream Library

This is a summary overview of the named headers in this library. All types are defined within the `DataStream` `namespace`. 

**Disclaimer**: This library is still very much a work in progress. At this point, a DataStream has no advantages over an STL `vector`, other than it can handle non-contiguous data ranges (albeit slowly). Eventually, I want to make it have more convenience features, like file writing and maybe histogram generation.

## DataStream
```c++
class DataStream<data_type>;
```
A `DataStream` is a contiguous chunk of memory similar to the STL `vector`. The need for the contiguity is in cache-friendliness for data processing. 

If the data import is non-contiguous, i.e. it is represented as an array of pointers, then the `DataStream` will copy it into a separate, contiguous chunk of memory.
