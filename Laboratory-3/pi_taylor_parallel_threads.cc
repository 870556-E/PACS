#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = long double;

void pi_taylor_chunk(std::vector<my_float> &output, size_t thread_id, size_t start_step, size_t stop_step) {
    // std::cout << "pi_taylor_chunk function entered" << '\n';
    int num = (start_step % 2 == 0) ? 1 : -1;
    for (size_t i = start_step; i < stop_step; i++){
        output[thread_id] += num/static_cast<my_float>((i << 1) +1 ); // i << 1 is the bitwise operation of displacing a bit to the left, equal to n*2
        num = -num;
    }
}

std::pair<size_t, size_t>
usage(int argc, const char *argv[]) {
    // read the number of steps from the command line
    if (argc != 3) {
        std::cerr << "Invalid syntax: pi_taylor <steps> <threads>" << std::endl;
        exit(1);
    }

    size_t steps = std::stoll(argv[1]);
    size_t threads = std::stoll(argv[2]);

    if (steps < threads ){
        std::cerr << "The number of steps should be equal or larger than the number of threads" << std::endl;
        exit(1);

    }
    return std::make_pair(steps, threads);
}

int main(int argc, const char *argv[]) {


    auto ret_pair = usage(argc, argv);
    auto steps = ret_pair.first;
    auto threads = ret_pair.second;

    my_float pi;

    // please complete missing parts
    size_t chunk_start = 0;
    size_t chunk_end = 0;

    std::vector<my_float> partial_sums(threads);
    std::vector<std::thread> t(threads);
    // std::cout << "thread vector created" << '\n';
    

    for (int i=0; i < threads; i++){
        if (i == threads-1){
            chunk_end = steps;
        }
        else{
            chunk_end = (i+1)*steps/threads;
        }
        // std::cout << "workload divider entered" << '\n';
        t[i] = std::thread(pi_taylor_chunk, std::ref(partial_sums), i, chunk_start, chunk_end);
        // std::cout << "thread created" << '\n';
        chunk_start = chunk_end;
    }

    for (auto &thread : t){
        thread.join();
        // std::cout << "thread joined" << '\n';
    }
    
    pi = 4 * std::accumulate(partial_sums.begin(), partial_sums.end(), decltype(partial_sums)::value_type());

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;
}

