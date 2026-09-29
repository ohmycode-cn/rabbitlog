#include <print>

#if defined(UNIT_TEST)
#include "rbbt.hpp"
#endif

int main() {
#if defined(UNIT_TEST)
    std::println("UNIT TEST MODE");
    rbbl::test::exec_unit_test();
#else
    std::println("MAIN RUNING");
#endif
    return 0;
}