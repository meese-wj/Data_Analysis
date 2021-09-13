#pragma once
// Use this file to define some integer
// power functions

namespace Statistics
{
    namespace Math_Helpers
    {
        template<typename T, int power_value>
        struct IntPower
        {
            static constexpr T power(const T base)
            {
                return pow(base, power_value);
            } 
        };

        // Template specializations
        template<typename T>
        struct IntPower<T, 0>
        {
            static constexpr T power(const T base)
            {
                return static_cast<T>(1);
            }
        };

        template<typename T>
        struct IntPower<T, 1>
        {
            static constexpr T power(const T base)
            {
                return base;
            }
        };

        template<typename T>
        struct IntPower<T, 2>
        {
            static constexpr T power(const T base)
            {
                return base * base;
            }
        };

        template<typename T>
        struct IntPower<T, 3>
        {
            static constexpr T power(const T base)
            {
                return base * IntPower<T, 2>::power(base);
            }
        };

        template<typename T>
        struct IntPower<T, 4>
        {
            static constexpr T power(const T base)
            {
                return IntPower<T, 2>( IntPower<T, 2>::power(base) );
            }
        };
        
    }
}