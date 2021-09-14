# DataStream Library

This is a summary overview of the named in this library. All types are defined within the `DataStream` `namespace`. 

**Disclaimer**: This library is still very much a work in progress. At this point, a DataStream has no advantages over an STL `vector`. Eventually, I want to make it have more convenience features, like file writing and maybe histogram generation.

## DataStream
```c++
class DataStream<data_type>;
```
A `DataStream` is a contiguous chunk of memory similar to the STL `vector`. 
