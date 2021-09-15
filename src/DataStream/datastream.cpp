// Implementation file for the base DataStream
#include "datastream.hpp"

namespace DataStreams
{
    namespace TemplateDeclarations
    {
        void Declaration()
        {
            // Use this dummy function to declare a bunch
            // of different DataStream types.
            //
            // This is just to be sure that the template 
            // library compiles.
            DataStream<int> dsi;
            DataStream<std::uint8_t> dsus;
            DataStream<std::uint32_t> dsui;
            DataStream<std::uint64_t> dsul;
            DataStream<long> dsl;
            
            DataStream<float> dsf;
            DataStream<double> dsd;
            DataStream<long double> dsld;
        }
    }
}