#pragma once

#include "Types.hpp"

template<typename T>
struct name_traits {
    static std::string name() { return std::string(typeid(T).name()); }
};

template<>
struct name_traits<int> {
    static std::string name() { return "int"; }
};

template<>
struct name_traits<double> {
    static std::string name() { return "double"; }
};

template<>
struct name_traits<std::string> {
    static std::string name() { return "std::string"; }
};

template<>
struct name_traits<SomeType> {
    static std::string name() { return "SomeType"; }
};
