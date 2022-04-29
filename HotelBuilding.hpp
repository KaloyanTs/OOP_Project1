#ifndef __HOTELBUILDING_HPP
#define __HOTELBUILDING_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "RoomAnalyzer.hpp"
#include <fstream>

class HotelBuilding
{
    /**
     * @brief list of rooms
     *
     */
    Room **rooms;
    /**
     * @brief size of the list of rooms
     *
     */
    size_t size;

public:
    /**
     * @brief Construct a new HotelBuilding object from a text file containing rooms info
     * Format of the file:
     * 1.   <size>
     * ...
     * n(>1). <room #(n-2) number> <room #(n-2) count of beds>
     *
     * @param ifs input file stream to text file, containing rooms data
     */
    HotelBuilding(std::ifstream &ifs); // todo String
    HotelBuilding(const HotelBuilding &other) = delete;
    HotelBuilding &operator=(HotelBuilding &other) = delete;
    /**
     * @brief Destroy the HotelBuilding object
     *
     */
    ~HotelBuilding();

    /**
     * @brief Get the room count
     *
     * @return size_t count of rooms
     */
    size_t getRoomCount() const { return size; }

    /**
     * @brief seek for a room with particular number
     *
     * @param roomNumber number if the sought room
     * @return Room* if found -> pointer to this Room
     *               else -> nullptr
     */
    Room *operator[](unsigned roomNumber) const;

    /**
     * @brief update this HotelBuilding rooms data on a new Date
     *
     * @param d new Date
     */
    void newDate(Date d);

    /**
     * @brief show available rooms on a particular Date
     *
     * @param os output stream where the available rooms will be shown in format:
     * Available rooms for <today>:
     * Number: <room number> Bed count: <count of beds>
     * ...
     *
     * @param d Date
     */
    void showAvailableRooms(std::ostream &os, Date d) const;

    /**
     * @brief Create a report for the usage of rooms for a particular period of time (ending before the today Date)
     * Format of the report:
     * Report for the usage of the rooms between <beginning of period> and <end of period>:
     * // todo
     *
     *
     * @param period period of time
     */
    void createReport(DatePeriod &period) const;

    /**
     * @brief show top DISPLAY (or all rooms if less than DISPLAY + 1) sorted by suitabilty for the guest, given minimal number of beds and particular period of time for an eventual reservation
     *
     * @param beds minimal number of beds insisted in the room
     * @param period period of time
     */
    void suggestRoom(unsigned beds, const DatePeriod &period);

    /**
     * @brief prints to stdout all rooms together with up to today Date info about their Availability (now, in future or in the past)
     *
     * @param today Date
     */
    void showRoomsStatesToday(Date today) const;

    void showRoomForNights(unsigned number, unsigned nights, Date today) const;

    /**
     * @brief using RoomAnalyzer to perform algorithms for the room list (database)
     *
     */
    friend class RoomAnalyzer;
};

#endif