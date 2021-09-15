#include "datastream_tester.hpp"

int main()
{
    DataStream_Tests::DataStream_Tester quiz;
    quiz.test_noncontiguous_imports();
    return 0;
}