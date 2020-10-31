#pragma once
#include <functional>
#include <mutex>


namespace cpput {

    void synchronized(std::mutex& mutex, std::function<void()> func);

}