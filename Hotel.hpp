#ifndef __HOTEL_HPP
#define __HOTEL_HPP
#include "Types.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "Reservation.hpp"
#include "HotelBuilding.hpp"
#include <string>

std::string readFromIfstream(std::ifstream &ifs, size_t len);

class Hotel
{
    std::string name;
    static Date now;
    HotelBuilding *building;

    static Date getToday();

public:
    Hotel() = delete;
    Hotel(const char *hotelDataFile);
    Hotel(const Hotel &) = delete;
    Hotel &operator=(const Hotel &) = delete;
    ~Hotel();

    static Date today() { return now; }
    std::string getName() const { return name; }

    void nextDay();
    bool reserveRoom(unsigned number, Date from, Date to, std::string name = "-", std::string s = "None\n");
    Hotel &showAvailableRooms(std::ostream &, Date);
    bool freeRoom(unsigned number);
    Hotel &getReport(Date from, Date to);
    unsigned searchRoom(unsigned minBeds) const;
    bool serviceRoom(unsigned number, Date from, Date to, std::string note);
};

#endif