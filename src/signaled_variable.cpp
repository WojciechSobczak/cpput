#include "signaled_variable.hpp"

namespace cpput {

    void signaled_variable::wait() noexcept {
        signaled_variable_def::wait(this->defaultLock);
    }

    void signaled_variable::wait_for_signal() noexcept {
        signaled_variable_def::wait_for_signal(this->defaultLock);
    }

    void signaled_variable_def::wait(std::unique_lock<std::mutex>& lock) noexcept {
        this->conditional_variable.wait(lock);
        this->signaled_state.store(false);
    }

    void signaled_variable_def::wait_for_signal(std::unique_lock<std::mutex>& lock) noexcept {
        bool expected = true;
        if (this->signaled_state.compare_exchange_strong(expected, false)) {
            return;
        }
        this->conditional_variable.wait(lock);
        this->signaled_state.store(false);
    }

    bool signaled_variable_def::is_signaled() const noexcept {
        return this->signaled_state.load();
    }

    void signaled_variable_def::signal() noexcept {
        this->signaled_state.store(true);
        this->conditional_variable.notify_all();
    }
};