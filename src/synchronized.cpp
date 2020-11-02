#include "synchronized.hpp"

namespace cpput {

    template <typename Callable, typename ... Args>
    void synchronized(std::mutex& mutex, Callable func, Args&& ... args) {
        const std::lock_guard lock(mutex);
        func(args...);
    }

}