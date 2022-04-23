#ifndef __DATE_HPP
#define __DATE_HPP
#include <iostream>
#include <ctime>

class Date
{
    unsigned short day, month, year;
    bool isVaid() const;
    bool isLeap(unsigned y) const;

public:
    Date(unsigned short d = 1, unsigned short m = 1, unsigned short y = 1900) : day(d), month(m), year(y) {}
    bool operator<(Date other) const;
    bool operator<=(Date other) const;
    bool operator>(Date other) const;
    bool operator>=(Date other) const;
    bool operator==(Date other) const;
    const char *operator()(char *buf) const;
    Date &operator++();

    static Date getToday();

    friend std::istream &operator>>(std::istream &is, Date &d);
    friend std::ostream &operator<<(std::ostream &os, const Date &d);
};

#endif