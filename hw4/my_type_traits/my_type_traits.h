#pragma once 

#include <stdint.h>
#include <string>
#include <vector>
#include <list>

template<typename T>
struct is_int8_t
{
    static const bool value = false;
};
template<>
struct is_int8_t<int8_t>
{
    static const bool value = true;
};

template<typename T>
struct is_int16_t
{
    static const bool value = false;
};
template<>
struct is_int16_t<int16_t>
{
    static const bool value = true;
};

template<typename T>
struct is_int32_t
{
    static const bool value = false;
};
template<>
struct is_int32_t<int32_t>
{
    static const bool value = true;
};

template<typename T>
struct is_int64_t
{
    static const bool value = false;
};
template<>
struct is_int64_t<int64_t>
{
    static const bool value = true;
};

template<typename T>
struct is_string
{
    static const bool value = false;
};
template<>
struct is_string<std::string>
{
    static const bool value = true;
};

template<typename T>
struct is_vector
{
    static const bool value = false;
};
template<typename U>
struct is_vector<std::vector<U>>
{
    static const bool value = true;
};

template<typename T>
struct is_list
{
    static const bool value = false;
};
template<typename U>
struct is_list<std::list<U>>
{
    static const bool value = true;
};