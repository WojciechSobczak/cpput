#pragma once
#include <condition_variable>
#include <atomic>
#include <thread>

namespace cpput {
    class signaled_variable {
    private:
        std::mutex defaultMutex{};
        std::unique_lock<std::mutex> defaultLock{ defaultMutex };
        std::condition_variable conditional_variable{};
        std::atomic_bool signaled_state{false};

    public:
        signaled_variable() = default;
        signaled_variable(const signaled_variable& other) = delete;
        signaled_variable(signaled_variable&& other) = delete;
        signaled_variable& operator=(const signaled_variable& other) = delete;
        signaled_variable& operator=(signaled_variable&& other) = delete;


        void wait(std::unique_lock<std::mutex>& lock);
        void wait_for_signal(std::unique_lock<std::mutex>& lock);

        void wait();
        void wait_for_signal();

        bool is_signaled();
        void signal();
    };
};