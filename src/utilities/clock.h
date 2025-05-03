#ifndef CLOCK_H
#define CLOCK_H
#include <string>
#include <cctype>
#include "errors.h"

class Clock
{
    int hours;
    int minutes;

public:
    Clock() = default;
    Clock(const std::string &clock_str)
    {
        int seperator = clock_str.find(':');
        if (seperator == std::string::npos)
        {
            throw clockParseError(clock_str);
        }
        std::string hours_str = clock_str.substr(0, seperator);
        std::string minutes_str = clock_str.substr(seperator + 1);

        for (auto &element : hours_str)
        {
            if (!isdigit(element))
            {
                throw clockParseError(clock_str);
            }
        }
        for (auto &element : minutes_str)
        {
            if (!isdigit(element))
            {
                throw clockParseError(clock_str);
            }
        }

        int hours = std::stoi(hours_str);
        int minutes = std::stoi(minutes_str);

        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
        {
            throw clockParseError(clock_str);
        }
    }
    bool operator>(const Clock &other) const
    {
        if (hours != other.hours)
            return hours > other.hours;
        return minutes > other.minutes;
    }
    bool operator<(const Clock &other) const
    {
        return !(*this > other) && !(*this == other);
    }

    bool operator==(const Clock &other) const
    {
        return hours == other.hours && minutes == other.minutes;
    }
    bool operator!=(const Clock &other) const { return !(*this == other); }
    bool operator<=(const Clock &other) const { return *this < other || *this == other; }
    bool operator>=(const Clock &other) const { return *this > other || *this == other; }
    friend Clock operator+(const Clock &lhs, const Clock &rhs);
    friend Clock operator-(const Clock &lhs, const Clock &rhs);
};

Clock operator+(const Clock &lhs, const Clock &rhs)
{
    int total_minutes = (lhs.hours + rhs.hours) * 60 + lhs.minutes + rhs.minutes;
    int new_hours = total_minutes / 60;
    int new_minutes = total_minutes % 60;

    Clock result;
    result.hours = new_hours;
    result.minutes = new_minutes;

    return result;
}

Clock operator-(const Clock &lhs, const Clock &rhs)
{
    int lhs_total = lhs.hours * 60 + lhs.minutes;
    int rhs_total = rhs.hours * 60 + rhs.minutes;

    int diff_total = lhs_total - rhs_total;

    int diff_hours = diff_total / 60;
    int diff_minutes = diff_total % 60;

    Clock result;
    result.hours = diff_hours;
    result.minutes = diff_minutes;

    return result;
}
#endif
