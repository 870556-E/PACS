#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <cmath>

// Allow to change the floating point type
using my_float = long double;

my_float pi_taylor(size_t steps) {

    my_float result = 0.0f;

    for (size_t n = 0; n < steps; n++) {
        result += std::pow(-1, n) / (2 * n + 1);
    }
    
    result = result * 4;

    return result;
}

my_float pi_taylor2(size_t steps) {

    my_float result = 0.0f;

    int num = 1;
    for (size_t n = 0; n < steps; n++) {
        result += num / static_cast<my_float>((n << 1) + 1);
        num = -num;
    }

    return 4.0f * result;
}

int main(int argc, const char *argv[]) {

    // read the number of steps from the command line
    if (argc != 2) {
        std::cerr << "Invalid syntax: pi_taylor <steps>" << std::endl;
        exit(1);

    }

    size_t steps = std::stoll(argv[1]);
    auto pi = pi_taylor2(steps);

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<my_float>::digits10 + 1)
        << pi << std::endl;
}
