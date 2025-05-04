#ifndef CLOCK_H
#define CLOCK_H
#include <string>
#include <cctype>
#include "errors.h"
#include <iomanip>
#include <sstream>

struct Clock
{
    int hours;
    int minutes;

    Clock() = default;
    Clock(const std::string &clock_str);
    std::string to_string() const;
    bool operator>(const Clock &other) const;
    bool operator<(const Clock &other) const;
    bool operator==(const Clock &other) const;
    bool operator!=(const Clock &other) const;
    bool operator<=(const Clock &other) const;
    bool operator>=(const Clock &other) const;
    friend Clock operator+(const Clock &lhs, const Clock &rhs);
    friend Clock operator-(const Clock &lhs, const Clock &rhs);
};

#endif
