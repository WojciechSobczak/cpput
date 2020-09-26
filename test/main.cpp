#include <iostream>
#include <cpput/signaled_variable.hpp>

using namespace std::chrono_literals;

int main() {
    cpput::signaled_variable signaledVar;
    std::thread t1([&signaledVar]() {
        std::this_thread::sleep_for(2s);
        signaledVar.signal();
    });
    signaledVar.wait_for_signal();
    t1.join();
    return 1;
}