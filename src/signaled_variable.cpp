#include "signaled_variable.hpp"

namespace cpput {

    void signaled_variable::wait() noexcept {
        signaled_variable_def::wait(this->default_lock);
    }

    void signaled_variable::wait_for_signal() noexcept {
        signaled_variable_def::wait_for_signal(this->default_lock);
    }
    
};