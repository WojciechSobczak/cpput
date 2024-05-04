#pragma once
#include <functional>
#include <mutex>
#include <type_traits>


namespace cpput 
{

template <typename Callable, typename ... Args>
void synchronized(std::mutex& mutex, Callable func, Args&& ... args) {
    const std::lock_guard lock(mutex);
    func(std::forward<Args>(args)...);
}

template <typename resource_type>
class synchronized {
private:
    resource_type resource;
    std::mutex mutex;
public:
    synchronized() = default;
    explicit synchronized(resource_type resource) : resource(std::move(resource)) {};

    void synchronized(const std::function<void(resource_type&)>& callback) {
        std::lock_guard lock(this->mutex);
        callback(this->resource);
    }
};

}