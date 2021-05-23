#pragma once

#include <string>

namespace cpput {
    void to_lower_case(std::string& string);
    void to_upper_case(std::string& string);

    std::string to_lower_case_new(std::string& string);
    std::string to_upper_case_new(std::string& string);

    void to_lower_case(std::wstring& string);
    void to_upper_case(std::wstring& string);

    std::wstring to_lower_case_new(std::wstring& string);
    std::wstring to_upper_case_new(std::wstring& string);
}
