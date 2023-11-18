#include "signaled_variable_def.hpp"

namespace cpput {

    void signaled_variable_def::wait(std::unique_lock<std::mutex>& lock) noexcept {
        this->condition_var.wait(lock);
        this->signaled_state.store(false);
    }

    void signaled_variable_def::wait_for_signal(std::unique_lock<std::mutex>& lock) noexcept {
        bool expected = true;
        if (this->signaled_state.compare_exchange_strong(expected, false)) {
            return;
        }
        this->condition_var.wait(lock);
        this->signaled_state.store(false);
    }

    bool signaled_variable_def::is_signaled() const noexcept {
        return this->signaled_state.load();
    }

    void signaled_variable_def::signal() noexcept {
        this->signaled_state.store(true);
        this->condition_var.notify_all();
    }
}

