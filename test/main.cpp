#include <iostream>
#include <chrono>
#include <cpput/defer.hpp>

using namespace std::chrono_literals;

int main() {
    cpput::defer def([]() {
        std::cout << "DEATH\n";
    });
}