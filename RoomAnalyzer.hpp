#ifndef __ROOMANALYZER_HPP
#define __ROOMANALYZER_HPP
#include "Types.hpp"
#include "HotelBuilding.hpp"
#include "Date.hpp"
const size_t DISPLAY = 5;

class RoomAnalyzer
{
    static void sortRooms(HotelBuilding &hB, unsigned *score, size_t size);

public:
    static void suggest(HotelBuilding &hB, unsigned beds, DatePeriod period);
};

#endif