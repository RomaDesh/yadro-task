#include "globals.h"
#include "time.h"
#include "utils.h"

#include <iomanip>


Time::Time(const std::string& timeStr) {
    h = custom_stoi(timeStr.substr(0, 2));
    m = custom_stoi(timeStr.substr(3, 2));
    if (timeStr.at(2) != ':' || h < 0 || h > 23 || m < 0 || m > 59) {
        throw std::runtime_error("Wrong format");
    }
}

Time::Time(int hours, int minutes) : h(hours), m(minutes) {}

bool Time::operator==(const Time& other) const {
    return h == other.h && m == other.m;
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    return (h < other.h) || (h == other.h && m < other.m);
}

bool Time::operator>(const Time& other) const {
    return (h > other.h) || (h == other.h && m > other.m);
}

bool Time::operator<=(const Time& other) const {
    return !(*this > other);
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

Time Time::operator+(const Time& other) const {
    int totalMinutes = (h + other.h) * 60 + (m + other.m);
    return Time(totalMinutes / 60, totalMinutes % 60);
}

Time Time::operator+=(const Time& other) {
    m += other.m;
    h += other.h + m / 60;
    m %= 60;
    return *this;
}

Time Time::operator-(const Time& other) const {
    int totalMinutes = (h * 60 + m) - (other.h * 60 + other.m); 
    return Time(totalMinutes / 60, totalMinutes % 60); }

int countPayment(const Time& time) {
    int res = 0;
    if (time.m)
        res += _price;
    res += _price * time.h;
    return res;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setw(2) << std::setfill('0') << time.h << ":" << std::setw(2) << std::setfill('0') << time.m;
    return os;
}
