#pragma once
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>

namespace cpput {

    class signaled_variable_def {
    protected:
        std::condition_variable conditional_variable{};
        std::atomic_bool signaled_state{ false };
    public:
        signaled_variable_def() = default;
        signaled_variable_def(const signaled_variable_def& other) = delete;
        signaled_variable_def(signaled_variable_def&& other) = delete;
        signaled_variable_def& operator=(const signaled_variable_def& other) = delete;
        signaled_variable_def& operator=(signaled_variable_def&& other) = delete;

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
        std::mutex defaultMutex{};
        std::unique_lock<std::mutex> defaultLock{ defaultMutex };
    public:
        signaled_variable() = default;
        signaled_variable(const signaled_variable& other) = delete;
        signaled_variable(signaled_variable&& other) = delete;
        signaled_variable& operator=(const signaled_variable& other) = delete;
        signaled_variable& operator=(signaled_variable&& other) = delete;

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
            return;
        }
        this->conditional_variable.wait_for(lock, time);
        this->signaled_state.store(false);
    }

    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        this->conditional_variable.wait_for(lock, time);
        this->signaled_state.store(false);
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for_signal_for(std::chrono::duration<Rep, Period> time) noexcept {
        signaled_variable::wait_for_signal_for(this->defaultLock, time);
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for(std::chrono::duration<Rep, Period> time) noexcept {
        signaled_variable::wait_for(this->defaultLock, time);
    }

};

