#pragma once
// This header defines a bunch of fast
// powers by template specialization.

namespace Statistics
{
    // Fast power computing
    template<typename T, T power>
    constexpr T fast_power( const T value )
    {
        return pow(value, power);
    }

    // Template-specialization for certain powers
    template<typename T>
    constexpr T fast_power<T, 0.5>( const T value )
    {
        return sqrt(value);
    }

    template<typename T>
    constexpr T fast_power<T, 2.>( const T value )
    {
        return value * value;
    }

    template<typename T>
    constexpr T fast_power<T, 3.>( const T value )
    {
        return value * value * value;
    }

    template<typename T>
    constexpr T fast_power<T, 4.>( const T value )
    {
        return fast_power<T, 2.>( fast_power<T, 2.>( value ) );
    }
    
    template<typename T>
    constexpr T fast_power<T, 5.>( const T value )
    {
        return fast_power<T, 2.>( value ) * fast_power<T, 3.>( value );
    }
    
    template<typename T>
    constexpr T fast_power<T, 6.>( const T value )
    {
        return fast_power<T, 2.>( fast_power<T, 3.>( value ) );
    }
    
    template<typename T>
    constexpr T fast_power<T, 7.>( const T value )
    {
        return fast_power<T, 3.>( value ) * fast_power<T, 4.>( value );
    }
   
    template<typename T>
    constexpr T fast_power<T, 8.>( const T value )
    {
        return fast_power<T, 2.>( fast_power<T, 6.>( value ) );
    }
}