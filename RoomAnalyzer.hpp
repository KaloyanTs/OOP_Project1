#ifndef __ROOMANALYZER_HPP
#define __ROOMANALYZER_HPP
#include "Types.hpp"
#include "HotelBuilding.hpp"
#include "Date.hpp"

/**
 * @brief max number of rooms to be printed
 *
 */
const size_t DISPLAY = 5;

class RoomAnalyzer
{
    /**
     * @brief sort the Rooms in a HotelBuilding based on some score
     *
     * @param hB HotelBuilding
     * @param score array of points for each Room
     * @param size size of the array
     */
    static void sortRooms(HotelBuilding &hB, unsigned *score, size_t size);

public:
    /**
     * @brief print top DISPLAY rooms info based on suitability of a Room (desired number of beds and period of time)
     *
     * @param hB HotelBuilding
     * @param beds desired number of beds
     * @param period period of time
     */
    static void suggest(HotelBuilding &hB, unsigned beds, DatePeriod period);

    /**
     * @brief print soonest period when a particular room is free for particular number of nights
     *
     * @param hB HotelBuilding
     * @param number ID of the Room
     * @param nights length of a period
     * @param today today's Date
     */
    static void soonestFreePeriod(const HotelBuilding &hB, unsigned number, unsigned nights, Date today);
};

#endif