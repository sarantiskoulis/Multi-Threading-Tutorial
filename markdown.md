# Multithreading Dice Roll Simulation Tutorial
This tutorial guides you through the process of simulating dice rolls using 
C++ multithreading. The objective is to distribute the computation across multiple threads, 
thereby speeding up the process of simulating a large number of dice rolls. This approach 
leverages the power of modern CPUs to perform concurrent operations, making it 
significantly faster than a single-threaded approach for large-scale simulations.

## Overview
The program simulates rolling a weighted six-sided dice a specified number of times (`total_iterations` ). 
Each side of the dice has a weight that influences the likelihood of its outcome. 
The simulation uses the C++ Standard Library's `<random>` and `<thread>` to achieve multithreading and random number generation.

## Key Components
Random Seed Initialization
A `std::mt19937` random number generator is initialized with a seed based on the current time. 
This ensures that the sequence of random numbers varies between program executions.

`static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());`

## Output Simulation Structure
The Results structure stores the outcome of the dice rolls. 
It holds a vector `diceRollSum` where each index corresponds to a dice face, and its value represents the total 
number of times that face was rolled.

`struct Results {
std::vector<long long int> diceRollSum = {0,0,0,0,0,0};
};`


## Worker Function
The Worker function is the heart of the multithreaded simulation. 
It takes a range of iterations to simulate (start to end) and updates the Results structure with the count of 
each dice outcome within its range.


`void Worker(int start, int end, std::discrete_distribution<> &dist, Results &results);
`
## Main Function
The main function initializes the weighted dice, creates worker threads based on the number of available CPU cores,
and aggregates the results after all threads have completed their execution.

### Steps:
- Initialize Dice Weights: Define the weights for each face of the dice.
- Create Threads: Distribute the total iterations across available CPU cores.
- Join Threads: Wait for all threads to complete their execution.
- Aggregate Results: Combine the results from all threads and display the total counts for each dice face.