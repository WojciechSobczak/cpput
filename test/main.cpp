#include <iostream>
#include <cpput/signaled_variable.hpp>

using namespace std::chrono_literals;


int main() {
    cpput::signaled_variable signaledVar;
    signaledVar.wait_for_signal();
    signaledVar.signal();

    return 1;
}