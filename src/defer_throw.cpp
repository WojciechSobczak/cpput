#include "defer_throw.hpp"


namespace cpput {
    defer_throw::defer_throw(std::function<void()> on_destruction) : on_destruction(on_destruction) {};
    defer_throw::~defer_throw() {
        on_destruction();
    };
}


