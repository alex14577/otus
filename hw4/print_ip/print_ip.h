#pragma once

#include <type_traits>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>

template<typename T>
std::array<uint8_t, sizeof(T)> Split(T n)
{
    std::array<uint8_t, sizeof(T)> res;
    for(size_t i = 0; i < sizeof(T); i++)
    {
        res[i] = (n >> (8 * (sizeof(T) - i - 1))) & 0xff;
    }
    return res;
}

template<typename T>
void PrintIp(T ip)
{
    if constexpr(std::is_integral<T>::value)
    {
        auto arr = Split(ip);
        for(size_t i = 0; i < arr.size(); ++i)
        {
            if(i != 0)
            {
                std::cout << '.';
            }
            std::cout << std::to_string(arr[i]);
        }
    }
    else if constexpr(std::is_same<T, std::string>::value)
    {
        std::cout << ip;
    }
    else if constexpr(  std::is_same<T, std::vector<typename T::value_type>>::value ||
                        std::is_same<T, std::list<typename T::value_type>>::value)
    {
        bool afterFirstPart = false;
        for(const auto& part : ip )
        {
            if(afterFirstPart)
            {  
                std::cout << '.';
            }
            else
            {
                afterFirstPart = true;    
            }
            std::cout << std::to_string( part);
        }
    }
}