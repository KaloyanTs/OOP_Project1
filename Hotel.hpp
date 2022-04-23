#ifndef __HOTEL_HPP
#define __HOTEL_HPP
#include "Types.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "Reservation.hpp"
#include "HotelBuilding.hpp"

class Hotel
{
    char *name;
    static Date now;
    bool init;
    HotelBuilding *building;

    static Date getToday();

public:
    Hotel(const char *hotelDataFile);

    static Date today() { return now; }
    const char *getName() const { return name; }

    void nextDay();
    Hotel &showAvailableRooms(std::ostream &, Date);
};

#endif