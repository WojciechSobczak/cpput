#include <cpput/string.hpp>
#include <algorithm>
#include <cwctype>

namespace cpput {
    void to_lower_case(std::string& string) {
        std::transform(string.begin(), string.end(), string.begin(), std::tolower);
    }
    void to_upper_case(std::string& string) {
        std::transform(string.begin(), string.end(), string.begin(), std::toupper);
    }

    std::string to_lower_case_new(std::string& string) {
        std::string copy = string;
        to_lower_case(copy);
        return copy;
    }

    std::string to_upper_case_new(std::string& string) {
        std::string copy = string;
        to_upper_case(copy);
        return copy;
    }

    void to_lower_case(std::wstring& string) {
        std::transform(string.begin(), string.end(), string.begin(), std::towlower);
    }

    void to_upper_case(std::wstring& string) {
        std::transform(string.begin(), string.end(), string.begin(), std::towupper);
    }

    std::wstring to_lower_case_new(std::wstring& string) {
        std::wstring copy = string;
        to_lower_case(copy);
        return copy;
    }

    std::wstring to_upper_case_new(std::wstring& string) {
        std::wstring copy = string;
        to_upper_case(copy);
        return copy;
    }
}