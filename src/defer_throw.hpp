#include <functional>

namespace cpput {
    class defer_throw {
    protected:
        std::function<void()> on_destruction;
    public:
        defer_throw(std::function<void()> on_destruction);
        ~defer_throw();
    };
}