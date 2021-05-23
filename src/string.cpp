#include <cpput/string.hpp>
#include <algorithm>
#include <cwctype>

namespace cpput {

    void to_lower_case(std::string& string) noexcept {
        std::transform(string.begin(), string.end(), string.begin(), std::tolower);
    }
    void to_upper_case(std::string& string) noexcept {
        std::transform(string.begin(), string.end(), string.begin(), std::toupper);
    }

    std::string to_lower_case_new(const std::string& string) noexcept {
        std::string copy = string;
        to_lower_case(copy);
        return copy;
    }

    std::string to_upper_case_new(const std::string& string) noexcept {
        std::string copy = string;
        to_upper_case(copy);
        return copy;
    }

    void to_lower_case(std::wstring& string) noexcept {
        std::transform(string.begin(), string.end(), string.begin(), std::towlower);
    }

    void to_upper_case(std::wstring& string) noexcept {
        std::transform(string.begin(), string.end(), string.begin(), std::towupper);
    }

    std::wstring to_lower_case_new(const std::wstring& string) noexcept {
        std::wstring copy = string;
        to_lower_case(copy);
        return copy;
    }

    std::wstring to_upper_case_new(const std::wstring& string) noexcept {
        std::wstring copy = string;
        to_upper_case(copy);
        return copy;
    }
}