#ifndef __HOTEL_HPP
#define __HOTEL_HPP
#include "Types.hpp"
#include "Date.hpp"
#include "Room.hpp"
#include "Reservation.hpp"
#include "HotelBuilding.hpp"
#include <string>

/**
 * @brief read string from input file stream with certain length
 *
 * @param ifs input stream
 * @param len maximum length of the read string
 * @return std::string
 */
std::string readFromIfstream(std::ifstream &ifs, size_t len);

class Hotel
{
    /**
     * @brief name of Hotel
     *
     */
    std::string name;

    /**
     * @brief current Date according to all hotels
     *
     */
    static Date now;

    /**
     * @brief pointer to the vector of rooms
     *
     */
    HotelBuilding *building;

public:
    Hotel() = delete;

    /**
     * @brief Construct a new Hotel object
     *
     * @param hotelDataFile path to file where rooms are recorded
     */
    Hotel(std::string hotelDataFile);
    Hotel(const Hotel &) = delete;
    Hotel &operator=(const Hotel &) = delete;

    /**
     * @brief Destroy the Hotel object
     *
     */
    ~Hotel();

    /**
     * @brief get today's Date according to all Hotels
     *
     * @return Date
     */
    static Date today() { return now; }

    /**
     * @brief get the name of this Hotel
     *
     * @return std::string
     */
    std::string getName() const { return name; }

    /**
     * @brief advance to the nextDay
     *
     */
    void nextDay();

    /**
     * @brief makes a new Reservation for particular Room and period with options for name of guest and notes to the Reservation
     *
     * @param number of the desired Room
     * @param from accomodation Date
     * @param to leaving Date
     * @param name guest's name
     * @param note note to the reservation
     * @return true successfull reservation
     * @return false failed reservation (not made)
     */
    bool reserveRoom(unsigned number, Date from, Date to, std::string name = "-", std::string note = "None\n");

    /**
     * @brief output to stream all available rooms for a particular Date
     *
     * @return Hotel& this Hotel
     */
    Hotel &showAvailableRooms(std::ostream &, Date);

    /**
     * @brief tries to free Room with particular ID
     *
     * @param number Room's ID
     * @return true room is now free
     * @return false room not found
     */
    bool freeRoom(unsigned number);

    /**
     * @brief Creates report for the usage of this Hotel's rooms in the period from-to. Report written in file named "report-YYYY-MM-DD.txt" where YYYY-MM-DD is the beginning of the period
     *
     * @param from beginning of period
     * @param to end of period
     * @return Hotel& this Hotel
     */
    Hotel &getReport(Date from, Date to);
    unsigned searchRoom(unsigned minBeds) const;

    /**
     * @brief plans maintenance for particular Room and period leaving note for the service
     *
     * @param number Room's ID
     * @param from beginning of period
     * @param to end of periof
     * @param note any notes to the service
     * @return true service planned successfully
     * @return false service planning failed (room not found or is reserved for the period)
     */
    bool serviceRoom(unsigned number, Date from, Date to, std::string note);
};

#endif