#pragma once
#include <functional>
#include <mutex>
#include <type_traits>


namespace cpput {

    template <typename Callable, typename ... Args>
    void synchronized(std::mutex& mutex, Callable func, Args&& ... args) {
        const std::lock_guard lock(mutex);
        func(std::forward<Args>(args)...);
    }

}