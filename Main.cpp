#include "rapidcheck.h"

#include "name_traits.hpp"
#include "Types.hpp"
#include "Realization.hpp"

void testStdSort() {
    rc::check(
        "result of std::sort is always equal to list of sorted elements",
        [](const std::vector<int>& in) {
            auto copy = in;
            std::sort(copy.begin(), copy.end());
            std::optional<int> prev;
            for (const auto elem : copy) {
                if (prev.has_value()) {
                    RC_ASSERT(elem >= *prev);
                }
                prev = elem;
            }
        });
}

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
    INVOKE_TEMPLATE_TEST_FUNCTION(testStdReverseInternal);
}

void testStdStringEmpty() {
    rc::check(
        "std::string::empty() == true always if std::string::size() == 0",
        [](const std::string& in) {
            if (in.size() == 0) {
                RC_ASSERT(in.empty());
            }
        });
}

void testStdVectorPushBack() {
    rc::check(
        "std::vector::push_back inserts elem to the end and doesn't affect existing elements",
        [](const std::vector<int>& in, int elemToPush) {
            auto copy = in;
            copy.push_back(elemToPush);
            RC_ASSERT(copy.size() == in.size() + 1);
            for (auto [it, i] = std::tuple { copy.begin(), 0 }; it != copy.end(); it++, i++) {
                if (i == copy.size() - 1) {
                    RC_ASSERT(*it == elemToPush);
                } else {
                    RC_ASSERT(*it == in.at(i));
                }
            }
        });
}

void testGcd() {
    rc::check(
        "every common divisor of a and b is a divisor of gcd(a, b)",
        [](int a, int b) {
            int foundGcd = gcd(a, b);
            for (int i = foundGcd; i > 0; i--) {
                if (foundGcd % i == 0) {
                    RC_ASSERT(a % i == 0);
                    RC_ASSERT(b % i == 0);
                }
            }
        });
    rc::check(
        "if a divides by b then gcd(a, b) is equal to b",
        [] {
            const auto max = *rc::gen::arbitrary<int>();
            const auto a = *rc::gen::inRange(0, max);
            const auto b = *rc::gen::inRange(1, max);
            int foundGcd = gcd(a, b);
            if (a % b == 0) {
                RC_ASSERT(b == foundGcd);
            } else {
                RC_ASSERT_FALSE(b == foundGcd);
            }
        });
    // And many other properties of GCD
}

int main() {
    testStdSort();
    testStdReverse();
    testStdStringEmpty();
    testStdVectorPushBack();
    testGcd();
    return 0;
}
