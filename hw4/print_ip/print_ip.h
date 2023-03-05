#pragma once

#include <type_traits>

#include <my_type_traits/my_type_traits.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>

template<typename T>
void PrintIp(T ip)
{
    if constexpr(std::is_integral<T>::value)
    {
        if constexpr(is_int8_t<T>::value)
        {
            std::cout << std::to_string( static_cast<uint8_t>(ip) );
        }
        if constexpr(is_int16_t<T>::value)
        {
            uint8_t ip1 = ip & 0xff00 >> 8;
            uint8_t ip2 = ip & 0x00ff >> 0;
            std::cout   << std::to_string( static_cast<uint8_t>(ip1) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip2) );
        }
        if constexpr(is_int32_t<T>::value)
        {
            uint8_t ip1 = (ip & 0xff000000) >> 24;
            uint8_t ip2 = (ip & 0x00ff0000) >> 16;
            uint8_t ip3 = (ip & 0x0000ff00) >> 8;
            uint8_t ip4 = (ip & 0x000000ff) >> 0;
            std::cout   << std::to_string( static_cast<uint8_t>(ip1) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip2) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip3) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip4) );
        }
        if constexpr(is_int64_t<T>::value)
        {
            uint8_t ip1 = (ip & 0xff00000000000000) >> 56;
            uint8_t ip2 = (ip & 0x00ff000000000000) >> 48;
            uint8_t ip3 = (ip & 0x0000ff0000000000) >> 40;
            uint8_t ip4 = (ip & 0x000000ff00000000) >> 32;
            uint8_t ip5 = (ip & 0x00000000ff000000) >> 24;
            uint8_t ip6 = (ip & 0x0000000000ff0000) >> 16;
            uint8_t ip7 = (ip & 0x000000000000ff00) >> 8;
            uint8_t ip8 = (ip & 0x00000000000000ff) >> 0;
            std::cout   << std::to_string( static_cast<uint8_t>(ip1) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip2) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip3) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip4) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip5) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip6) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip7) ) << '.' 
                        << std::to_string( static_cast<uint8_t>(ip8) );
        }
    }
    
    if constexpr(is_string<T>::value)
    {
        std::cout << ip;
    }

    if constexpr(is_vector<T>::value || is_list<T>::value)
    {
        if(ip.empty())
        {
            return;
        }

        auto it = ip.cbegin();
        std::cout << std::to_string( *it );

        ++it;
        while(it != ip.cend())
        {
            std::cout << '.' << std::to_string( *it );
            ++it;
        }
    }
}