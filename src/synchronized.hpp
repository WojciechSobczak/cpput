#pragma once
#include <functional>
#include <mutex>
#include <type_traits>


namespace cpput 
{

template <typename resource_type>
class synchronized {
private:
    resource_type resource;
    std::mutex mutex;
public:
    explicit synchronized(resource_type resource) : resource(std::move(resource)) {};

    void use(const std::function<void(resource_type&)>& callback) {
        std::lock_guard lock(this->mutex);
        callback(this->resource);
    }
};

}