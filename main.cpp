#include <iostream>
#include <random>
#include <chrono>
#include <thread>


// Random Seed Initilization
static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());

// Output Simulation Structure for a single iteration
struct Results {
    std::vector<long long int> diceRollSum = {0,0,0,0,0,0};
};

// Worker Function
void Worker(int start, int end,
            std::discrete_distribution<> & dist,
            Results & results) {
    for (int k = start; k < end; ++k) {
        results.diceRollSum[dist(gen)] += 1;
    }
}

int main() {
    std::vector<int> weights = {10, 10, 10, 10, 10, 30};
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    std::vector<std::thread> threads;
    long long int total_iterations = 1'000'000;
    int num_threads = std::thread::hardware_concurrency();
    std::vector<Results> results(num_threads);
//    Results results;

    const int elements_per_thread = total_iterations / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * elements_per_thread;
        int end = (i == num_threads - 1) ? total_iterations : start + elements_per_thread;
        threads.emplace_back(Worker,
                             start, end,
                             std::ref(dist),
                             std::ref(results[i])

        );

    }
    for (auto &thread: threads) {
        thread.join();
    }
    long long int total = 0;
    for (auto& res: results) {
        for (auto & r: res.diceRollSum) {
            total += r;
         std::cout << r << " ";
        }
        std::cout << std::endl;
    }
    std::cout << total << std::endl;

    return 0;
}
