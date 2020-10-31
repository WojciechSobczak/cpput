#pragma once
#include <functional>

namespace cpput {

    class defer {
    protected:
        std::function<void()> on_destruction;
    public:
        defer(std::function<void()> on_destruction);
        ~defer();

        defer(const defer& other) = delete;
        defer(defer&& other) = delete;
        defer& operator=(const defer& other) = delete;
        defer& operator=(defer&& other) = delete;
    };

}