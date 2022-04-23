#ifndef __HOTELBUILDING_HPP
#define __HOTELBUILDING_HPP
#include "Room.hpp"
#include <fstream>

class HotelBuilding
{
    Room **rooms;
    size_t size;

public:
    HotelBuilding(const char *roomsTextFile); // todo String
    HotelBuilding(const HotelBuilding &other) = delete;
    HotelBuilding &operator=(HotelBuilding &other) = delete;
    ~HotelBuilding();

    Room *operator[](unsigned roomNumber) const;
};

#endif