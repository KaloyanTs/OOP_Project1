#ifndef __HOTEL_HPP
#define __HOTEL_HPP
#include "Types.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "Reservation.hpp"

class Hotel
{
    char *name;
    static Date now;
    bool init;
    class t
    {
        int a;
    };
    t b;

    static Date getToday();

public:
    Date today() const { return now; }
    const char *getName() const { return name; }

    static void nextDay();
};

#endif