#pragma once

#include <string>

namespace cpput {

    void to_lower_case(std::string& string) noexcept;
    void to_upper_case(std::string& string) noexcept;

    std::string to_lower_case_new(const std::string& string) noexcept;
    std::string to_upper_case_new(const std::string& string) noexcept;

    void to_lower_case(std::wstring& string) noexcept;
    void to_upper_case(std::wstring& string) noexcept;

    std::wstring to_lower_case_new(const std::wstring& string) noexcept;
    std::wstring to_upper_case_new(const std::wstring& string) noexcept;

}
