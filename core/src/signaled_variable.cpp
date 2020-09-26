#include "signaled_variable.hpp"

namespace cpput {

    void signaled_variable::wait() {
        this->wait(this->defaultLock);
    }

    void signaled_variable::wait_for_signal() {
        this->wait_for_signal(this->defaultLock);
    }

    void signaled_variable::wait(std::unique_lock<std::mutex>& lock) {
        this->conditional_variable.wait(lock);
        this->signaled_state.store(false);
    }

    void signaled_variable::wait_for_signal(std::unique_lock<std::mutex>& lock) {
        bool expected = true;
        if (this->signaled_state.compare_exchange_strong(expected, false)) {
            return;
        }
        this->conditional_variable.wait(lock);
        this->signaled_state.store(false);
    }

    bool signaled_variable::is_signaled() {
        return this->signaled_state;
    }

    void signaled_variable::signal() {
        this->signaled_state.store(true);
        this->conditional_variable.notify_all();
    }
};