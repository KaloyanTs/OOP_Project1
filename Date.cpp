#include "Date.hpp"

bool Date::operator==(const Date other) const
{
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(const Date other) const
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

bool Date::operator<=(const Date other) const
{
    return !(*this > other);
}

bool Date::operator>(const Date other) const
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

bool Date::operator>=(const Date other) const
{
    return !(*this < other);
}

const char *Date::operator()(char *buf) const
{
    short y = year;
    for (unsigned i = 0; i < 4; ++i, y /= 10)
        buf[4 - 1 - i] = y % 10 + '0';
    buf[4] = '-';
    buf[5] = month / 10 + '0';
    buf[6] = month % 10 + '0';
    buf[7] = '-';
    buf[8] = day / 10 + '0';
    buf[9] = day % 10 + '0';
    buf[10] = '\0';
    return buf;
}

std::istream &operator>>(std::istream &is, Date &d)
{
    char c1, c2;
    try
    {
        is >> d.day >> c1 >> d.month >> c2;
        if (c1 != '/' || c2 != '/')
            throw "Bad delimiter!\n";
        std::cin >> d.year;
        if (is.fail() || !d.isVaid())
            throw "Bad data entered!\n";
    }
    catch (const char *err)
    {
        std::cerr << err;
        d = Date();
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Date &d)
{
    os.width(2);
    os.fill('0');
    os << d.day << '/';
    os.width(2);
    os.fill('0');
    os << d.month << '/';
    os.width(4);
    os.fill('0');
    os << d.year;
    return os;
}

bool Date::isVaid() const
{
    if (day > 31 || month > 12)
        return false;
    if (month == 2)
        return day < 29 + isLeap(year);
    if (month == 4 ||
        month == 6 ||
        month == 9 ||
        month == 11)
        return day <= 30;
    return true;
}

bool Date::isLeap(unsigned y) const
{
    return y % 400 == 0 || y % 100 && y % 4 == 0;
}

Date &Date::operator++()
{
    ++day;
    if (!isVaid())
    {
        day = 1;
        ++month;
        if (!isVaid())
        {
            month = 1;
            ++year;
        }
    }
    return *this;
}

Date Date::getToday()
{
    std::time_t t = std::time(NULL);
    std::tm *now = std::localtime(&t);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

int Date::operator-(Date other) const
{
    short smallerYear = (year < other.year ? year : other.year);
    unsigned thisDays = day +
                        daysFromBeginning[month - 1] +
                        365 * (year - smallerYear - 1) +
                        (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    unsigned otherDays = other.day +
                         daysFromBeginning[other.month - 1] +
                         365 * (other.year - smallerYear - 1) +
                         (other.year - 1) / 4 - (other.year - 1) / 100 + (other.year - 1) / 400;
    return thisDays - otherDays;
}

std::istream &operator>>(std::istream &is, DatePeriod &dP)
{
    // if (&is == &std::cin)
    //     std::cout << "From: ";
    // is >> dP.from;
    // if (&is == &std::cin)
    //     std::cout << "To: ";
    return is >> dP.from >> dP.to;
}

DatePeriod &DatePeriod::operator++()
{
    ++from;
    ++to;
    return *this;
}

void DatePeriod::readProper()
{
    do
    {
        std::cin >> *this;
        if (from >= to)
            std::cerr << "Bad data! Input period again!\n";
    } while (from >= to);
}