#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

static inline std::string readLineTrimmed() {
    std::string s;
    std::getline(std::cin, s);
    // trim both ends
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a==std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b-a+1);
}

#endif // UTILS_HPP
