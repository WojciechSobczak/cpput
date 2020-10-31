#include <atomic>
#include <condition_variable>
#include <mutex>

namespace cpput {

    class signaled_variable_def {
    protected:
        std::atomic<bool> signaled_state;
        std::condition_variable condition_var;

    public:
        void wait(std::unique_lock<std::mutex>& lock) noexcept;
        void wait_for_signal(std::unique_lock<std::mutex>& lock) noexcept;

        template <typename Rep, typename Period>
        bool wait_for_signal_for_no_reset(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for_signal_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for_no_reset(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept;

        template <typename Rep, typename Period>
        bool wait_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept;

        bool is_signaled() const noexcept;
        void signal() noexcept;
    };


    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for_signal_for_no_reset(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        bool expected = true;
        if (this->signaled_state.compare_exchange_strong(expected, false)) {
            return false;
        }
        if (std::cv_status::timeout == this->condition_var.wait_for(lock, time)) {
            return true;
        } else {
            return false;
        }
    }


    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for_signal_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        if (!this->wait_for_signal_for_no_reset(lock, time)) {
            this->signaled_state.store(false);
        }
    }

    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for_no_reset(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        if (std::cv_status::timeout == this->condition_var.wait_for(lock, time)) {
            return true;
        } else {
            return false;
        }
    }

    template <typename Rep, typename Period>
    bool signaled_variable_def::wait_for(std::unique_lock<std::mutex>& lock, std::chrono::duration<Rep, Period> time) noexcept {
        if (!this->wait_for_no_reset(lock, time)) {
            this->signaled_state.store(false);
            return false;
        }
    }

}