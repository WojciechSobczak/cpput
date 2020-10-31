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


    class defer_throw {
    protected:
        std::function<void()> on_destruction;
    public:
        defer_throw(std::function<void()> on_destruction);
        ~defer_throw();

        defer_throw(const defer& other) = delete;
        defer_throw(defer&& other) = delete;
        defer_throw& operator=(const defer& other) = delete;
        defer_throw& operator=(defer&& other) = delete;
    };

}