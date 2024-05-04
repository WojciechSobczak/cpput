#pragma once

#include <functional>
#include <tuple>
#include <type_traits>

namespace cpput {

    template<typename Callable>
    class defer {
    protected:
        Callable on_destruction;
    public:
        defer(Callable&& on_destruction) : 
            on_destruction(std::forward<Callable>(on_destruction)) 
        {
            #ifdef __cpp_exceptions
            static_assert(
                std::is_invocable_v<Callable> && noexcept(on_destruction()),
                "Defer function should be invocable and noexcept!"
            );
            #else
            static_assert(std::is_invocable_v<Callable>, "Defer function should be invocable!");
            #endif//__cpp_exceptions
        };
        ~defer() {
            on_destruction();
        };

        defer(const defer& other) = delete;
        defer(defer&& other) = delete;
        defer& operator=(const defer& other) = delete;
        defer& operator=(defer&& other) = delete;
    };

    #ifdef __cpp_exceptions
    template<typename Callable>
    class defer_catch_squash {
    protected:
        Callable on_destruction;
    public:
        defer_catch_squash(Callable&& on_destruction) :
            on_destruction(std::forward<Callable>(on_destruction))         
        {
            static_assert(std::is_invocable_v<Callable>, "Defer function should be invocable!");
        };
        ~defer_catch_squash() {
            try {
                on_destruction();
            } catch (...) {}
        };

        defer_catch_squash(const defer_catch_squash& other) = delete;
        defer_catch_squash(defer_catch_squash&& other) = delete;
        defer_catch_squash& operator=(const defer_catch_squash& other) = delete;
        defer_catch_squash& operator=(defer_catch_squash&& other) = delete;
    };
    

    template<typename Callable>
    class defer_throw {
    protected:
        Callable on_destruction;
    public:
        defer_throw(Callable&& on_destruction) :
            on_destruction(std::forward<Callable>(on_destruction))
        {
            static_assert(std::is_invocable_v<Callable>, "Defer function should be invocable!");
        };
        ~defer_throw() {
            on_destruction();
        };

        defer_throw(const defer_throw& other) = delete;
        defer_throw(defer_throw&& other) = delete;
        defer_throw& operator=(const defer_throw& other) = delete;
        defer_throw& operator=(defer_throw&& other) = delete;
    };
    #endif //__cpp_exceptions
}