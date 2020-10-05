#pragma once
#include <condition_variable>
#include <atomic>
#include <thread>

namespace cpput {

    class signaled_variable {
    protected:
        std::condition_variable conditional_variable{};
        std::atomic_bool signaled_state{ false };
    public:
        signaled_variable() = default;
        signaled_variable(const signaled_variable& other) = delete;
        signaled_variable(signaled_variable&& other) = delete;
        signaled_variable& operator=(const signaled_variable& other) = delete;
        signaled_variable& operator=(signaled_variable&& other) = delete;

        void wait(std::unique_lock<std::mutex>& lock) noexcept;
        void wait_for_signal(std::unique_lock<std::mutex>& lock) noexcept;

        bool is_signaled() const noexcept;
        void signal() noexcept;
    };

    class signaled_variable_def : public signaled_variable {
    protected:
        std::mutex defaultMutex{};
        std::unique_lock<std::mutex> defaultLock{ defaultMutex };
    public:
        signaled_variable_def() = default;
        signaled_variable_def(const signaled_variable_def& other) = delete;
        signaled_variable_def(signaled_variable_def&& other) = delete;
        signaled_variable_def& operator=(const signaled_variable_def& other) = delete;
        signaled_variable_def& operator=(signaled_variable_def&& other) = delete;

        void wait() noexcept;
        void wait_for_signal() noexcept;
    };
};