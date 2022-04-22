#ifndef __DATE_HPP
#define __DATE_HPP
#include <iostream>

class Date
{
    short day, month, year;
    bool isVaid() const;

public:
    Date(short d = 1, short m = 1, short y = 1900) : day(d), month(m), year(y) {}
    bool operator<(Date other) const;
    bool operator<=(Date other) const;
    bool operator>(Date other) const;
    bool operator>=(Date other) const;
    bool operator==(Date other) const;
    const char *operator()(char *buf) const;

    friend std::istream &operator>>(std::istream &is, Date &d);
};

#endif