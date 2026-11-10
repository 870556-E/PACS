#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <cmath>
#include <chrono>
#include <cstdlib>


using my_float = long double;

// Original implementation
my_float pi_taylor(size_t steps) {
    my_float result = 0.0L;

    for (size_t n = 0; n < steps; n++) {
        result += std::pow(-1, n) / (2 * n + 1);
    }

    return result * 4.0L;
}

// Optimized implementation
my_float pi_taylor2(size_t steps) {
    my_float result = 0.0L;
    int num = 1;

    for (size_t n = 0; n < steps; n++) {
        result += num / static_cast<my_float>((n << 1) + 1);
        num = -num;
    }

    return 4.0L * result;
}

int main(int argc, const char* argv[]) {

    // Read the number of steps from the command line
    if (argc != 2) {
        std::cerr << "Invalid syntax: pi_taylor <steps>" << std::endl;
        return 1;
    }

    size_t steps = std::stoull(argv[1]);

    // Measure original implementation
    auto start1 = std::chrono::steady_clock::now();

    auto pi1 = pi_taylor(steps);

    auto end1 = std::chrono::steady_clock::now();

    std::chrono::duration<double> time1 = end1 - start1;

    // Measure optimized implementation
    auto start2 = std::chrono::steady_clock::now();

    auto pi2 = pi_taylor2(steps);

    auto end2 = std::chrono::steady_clock::now();

    std::chrono::duration<double> time2 = end2 - start2;

    // Print results
    std::cout << std::setprecision(
        std::numeric_limits<my_float>::digits10 + 1
    );

    std::cout << "Steps: " << steps << "\n";

    std::cout << "Original PI: " << pi1 << "\n";
    std::cout << "Original time: " << time1.count() << " s\n";

    std::cout << "Optimized PI: " << pi2 << "\n";
    std::cout << "Optimized time: " << time2.count() << " s\n";

    return 0;
}