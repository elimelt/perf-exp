// Copyright 2024 Elijah Melton
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>

[[nodiscard]] u_int64_t fun1(int n) {
    std::vector<int> a(n);
    std::vector<int> b(n);

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    u_int64_t sum = 0;
    for (int i = 0; i < n; i++)
        sum += static_cast<u_int64_t>(a[i]) + b[i];

    return sum;
}

[[nodiscard]] u_int64_t fun2(int n) {
    std::vector<int> a(n);
    std::vector<int> b(n);
    for (int i = 0; i < n; i++)
        a[i] = i;
    for (int i = 0; i < n; i++)
        b[i] = i;

    u_int64_t sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    for (int i = 0; i < n; i++)
        sum += b[i];

    return sum;
}

/**
 * @brief A function to time the execution of a block of code
 * The function takes a function pointer and an integer as arguments,
 * and calls the supplied function pointer on the supplied integer.
 */
u_int64_t time_execution(u_int64_t (*function)(int), int arg) {
    auto start = std::chrono::high_resolution_clock::now();
    // volatile to prevent optimization
    volatile u_int64_t result = function(arg);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>
        (end - start).count();
}

const int NUM_EXECUTIONS_PER_DATA_POINT = 100;
const int MAX_SIZE = 100000;
const int MIN_SIZE = 1000;
const int STEP_SIZE = 1000;
const char FILE_1[] = "fun1_data.txt";
const char FILE_2[] = "fun2_data.txt";

int main() {
    std::ofstream file1(FILE_1);
    std::ofstream file2(FILE_2);

    if (file1.is_open() && file2.is_open()) {
        for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
            u_int64_t sum1 = 0;
            u_int64_t sum2 = 0;
            for (int i = 0; i < NUM_EXECUTIONS_PER_DATA_POINT; i++) {
                sum1 += time_execution(&fun1, n);
                sum2 += time_execution(&fun2, n);
            }
            double avg1 = static_cast<double>
                (sum1) / NUM_EXECUTIONS_PER_DATA_POINT;
            double avg2 = static_cast<double>
                (sum2) / NUM_EXECUTIONS_PER_DATA_POINT;

            file1 << n << " " << std::fixed
                << std::setprecision(2) << avg1 << "\n";
            file2 << n << " " << std::fixed
                << std::setprecision(2) << avg2 << "\n";
        }

        file1.close();
        file2.close();
        std::cout   << "Data written to " << FILE_1
                    << " and " << FILE_2 << std::endl;
        return 0;
    } else {
        std::cout << "Failed to open files for writing\n";
        return 1;
    }
}
