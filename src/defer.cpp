#include "defer.hpp"


namespace cpput {

    defer::defer(std::function<void()> on_destruction) : on_destruction(on_destruction) {};
    defer::~defer() {
        try {
            on_destruction();
        } catch (...) {}
    };

    defer_throw::defer_throw(std::function<void()> on_destruction) : on_destruction(on_destruction) {};
    defer_throw::~defer_throw() {
        on_destruction();
    };

}