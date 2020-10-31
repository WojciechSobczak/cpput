#include "synchronized.hpp"


namespace cpput {

    void synchronized(std::mutex& mutex, std::function<void()> func) {
        std::lock_guard lock(mutex);
        func();
    }

}