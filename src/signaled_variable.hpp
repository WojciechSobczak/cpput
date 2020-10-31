#pragma once
#include <condition_variable>
#include <atomic>
#include <thread>
#include <chrono>
#include "signaled_variable_def.hpp"

namespace cpput {

    class signaled_variable : public signaled_variable_def {
    protected:
        std::mutex default_mutex{};
        std::unique_lock<std::mutex> default_lock{ default_mutex };

    public:
        void wait() noexcept;
        void wait_for_signal() noexcept;

        template <typename Rep, typename Period>
        bool wait_for_signal_for_no_reset(std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for_signal_for(std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for_no_reset(std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for(std::chrono::duration<Rep, Period> time) noexcept;
    };


    template <typename Rep, typename Period>
    bool signaled_variable::wait_for_signal_for_no_reset(std::chrono::duration<Rep, Period> time) noexcept {
        return signaled_variable_def::wait_for_signal_for_no_reset(this->default_lock, time);
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for_signal_for(std::chrono::duration<Rep, Period> time) noexcept {
        return signaled_variable_def::wait_for_signal_for(this->default_lock, time);
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for_no_reset(std::chrono::duration<Rep, Period> time) noexcept {
        return signaled_variable_def::wait_for_no_reset(this->default_lock, time);
    }

    template <typename Rep, typename Period>
    bool signaled_variable::wait_for(std::chrono::duration<Rep, Period> time) noexcept {
        return signaled_variable_def::wait_for(this->default_lock, time);
    }

};

