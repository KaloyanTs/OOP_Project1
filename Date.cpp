#include "Date.hpp"

bool Date::operator==(Date other) const
{
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(Date other) const
{
    if (year > other.year)
        return false;
    else if (year < other.year)
        return true;
    else if (month < other.month)
        return true;
    else if (month > other.month)
        return false;
    else
        return day < other.day;
}

bool Date::operator<=(Date other) const
{
    return !(*this > other);
}

bool Date::operator>(Date other) const
{
    if (year < other.year)
        return false;
    else if (year > other.year)
        return true;
    else if (month > other.month)
        return true;
    else if (month < other.month)
        return false;
    else
        return day > other.day;
}

bool Date::operator>=(Date other) const
{
    return !(*this < other);
}

const char *Date::operator()(char *buf) const
{
    short y = year;
    for (unsigned i = 3; i >= 0; --i, y /= 10)
        buf[i] = y % 10 + '0';
    buf[4] = '-';
    buf[5] = month % 10 + '0';
    buf[6] = month / 10 + '0';
    buf[7] = '-';
    buf[8] = day % 10 + '0';
    buf[9] = day / 10 + '0';
    buf[10] = '\0';
    return buf;
}

std::istream &operator>>(std::istream &is, Date &d)
{
    char c;
    if (&is == &std::cin)
        std::cout << "Enter a date in format DD/MM/YYYY: ";
    is >> d.day >> c >> d.month >> c >> d.year;
    if (!is.good() || !d.isVaid())
    {
        std::cerr << "Bad data entered!\n";
        d = Date();
    }
    return is;
}