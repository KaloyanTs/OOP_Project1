#ifndef __HOTELBUILDING_HPP
#define __HOTELBUILDING_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "RoomAnalyzer.hpp"
#include <fstream>

class HotelBuilding
{
    Room **rooms;
    size_t size;

public:
    HotelBuilding(std::ifstream &ifs); // todo String
    HotelBuilding(const HotelBuilding &other) = delete;
    HotelBuilding &operator=(HotelBuilding &other) = delete;
    ~HotelBuilding();

    size_t getRoomCount() const { return size; }

    Room *operator[](unsigned roomNumber) const;

    void newDate(Date d);

    void showAvailableRooms(std::ostream &os, Date d) const;

    void createReport(DatePeriod &period) const;

    void suggestRoom(unsigned beds, const DatePeriod &period);

    void showRoomsStatesToday(Date today) const;

    friend class RoomAnalyzer;
};

#endif