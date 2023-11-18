#pragma once
#include <optional>

namespace cpput {

    template <typename ErrorCode, typename ReturnType>
    class output {
    private:
        std::optional<ReturnType> _return_val = {};
        ErrorCode _error_code = {};
        bool _success = {};
    public:
        output(ReturnType return_val) : return_val(return_val) {};
        output(ErrorCode _error_code) : _error_code(_error_code) {};
        output(ReturnType& return_val) : return_val(return_val) {};
        output(ErrorCode& _error_code) : _error_code(_error_code) {};
        output(ReturnType&& return_val) : return_val(return_val) {};
        output(ErrorCode&& _error_code) : _error_code(_error_code) {};

        bool success() { return _success; };
        ErrorCode& error_code() { return _error_code; };
        ReturnType& retval() { return _return_value; };
    };



}
