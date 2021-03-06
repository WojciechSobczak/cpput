#include "defer.hpp"


namespace cpput {

    defer::defer(std::function<void()> on_destruction) : on_destruction(on_destruction) {};
    defer::~defer() {
        try {
            on_destruction();
        } catch (...) {}
    };

}