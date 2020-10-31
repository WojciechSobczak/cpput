#pragma once
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>

namespace cpput {

    class signaled_variable_def {
    protected:
    public:

        void wait(std::unique_lock<std::mutex>& lock) noexcept;
        void wait_for_signal(std::unique_lock<std::mutex>& lock) noexcept;

        template <typename Rep, typename Period>
        bool wait_for_signal_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept;

        bool is_signaled() const noexcept;
        void signal() noexcept;
    };

    class signaled_variable : public signaled_variable_def {
    protected:
    public:

        void wait() noexcept;
        void wait_for_signal() noexcept;

        template <typename Rep, typename Period>
        bool wait_for_signal_for(std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for(std::chrono::duration<Rep, Period> time) noexcept;
    };

    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for_signal_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        bool expected = true;
        if (this->signaled_state.compare_exchange_strong(expected, false)) {
            return false;
        }
        if (std::cv_status::timeout == this->conditional_variable.wait_for(lock, time)) {
            return true;
        } else {
            this->signaled_state.store(false);
            return false;
        }
    }

    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        if (std::cv_status::timeout == this->conditional_variable.wait_for(lock, time)) {
            return true;
        } else {
            this->signaled_state.store(false);
            return false;
        }
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for_signal_for(std::chrono::duration<Rep, Period> time) noexcept {
        return signaled_variable_def::wait_for_signal_for(this->defaultLock, time);
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for(std::chrono::duration<Rep, Period> time) noexcept {
        return signaled_variable_def::wait_for(this->defaultLock, time);
    }

};

