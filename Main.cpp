#include "rapidcheck.h"

#include "Data.hpp"
#include "name_traits.hpp"

template<typename T>
void testStdReverseInternal() {
    rc::check(
        name_traits<T>::name() + ": double reversal yields the original value",
        [](const std::vector<T>& in) {
            auto copy = in;
            std::reverse(std::begin(copy), std::end(copy));
            std::reverse(std::begin(copy), std::end(copy));
            RC_ASSERT(in == copy);
        });
}

void testStdReverse() {
    testStdReverseInternal<int>();
    testStdReverseInternal<double>();
    testStdReverseInternal<std::string>();
    testStdReverseInternal<SomeType>();
}

int main() {
    testStdReverse();
    return 0;
}
