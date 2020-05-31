#pragma once

#include <string>

#include "rapidcheck.h"

#define INVOKE_TEMPLATE_TEST_FUNCTION(func) \
    func<int>();                            \
    func<double>();                         \
    func<std::string>();                    \
    func<SomeType>()

struct SomeType {
    int SomeInteger;
    double SomeFloatingPoint;
    std::string SomeString;

    bool operator==(const SomeType& entry) const {
        return SomeInteger == entry.SomeInteger
            && SomeFloatingPoint == entry.SomeFloatingPoint
            && SomeString == entry.SomeString;
    }
};

namespace rc {

template<>
struct Arbitrary<SomeType> {
    static Gen<SomeType> arbitrary() {
        return gen::build<SomeType>(
            gen::set(&SomeType::SomeInteger),
            gen::set(&SomeType::SomeFloatingPoint),
            gen::set(&SomeType::SomeString));
    }
};

}
