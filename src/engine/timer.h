#pragma once

#include <chrono>
#include <iostream>

using namespace std::chrono;

class Timer {
public:
    static void Start() {
        startTime = high_resolution_clock::now();
    }

    static void Stop() {
        stopTime = high_resolution_clock::now();
        std::cout << duration_cast<microseconds>(stopTime - startTime).count() << "μs" << std::endl;
    }

private:
    static inline time_point<high_resolution_clock> startTime;
    static inline time_point<high_resolution_clock> stopTime;
};

