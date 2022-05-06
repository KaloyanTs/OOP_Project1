#ifndef __RESERVATION_HPP
#define __RESERVATION_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "Date.hpp"
#include "Hotel.hpp"
#include <cstring>
#include <cassert>
#include <fstream>
#include <string>
#include "Constants.hpp"

/**
 * @brief different states in time for a reservation
 *
 */
enum ReservationState
{
    UNKNOWN = 0,
    PAST,
    ACTIVE,
    FUTURE
};

/**
 * @brief Class representing information about a reservation
 *
 */
class Reservation
{
    /**
     * @brief name of the reserver
     *
     */
    std::string guestName;
    /**
     * @brief note about the reservation
     *
     */
    std::string note;
    /**
     * @brief time period for the reservation
     *
     */
    DatePeriod period;
    /**
     * @brief state of the reservation (determined by today's Date)
     *
     */
    ReservationState state;
    /**
     * @brief whether the room is closed for maintenance
     *
     */
    bool service;

public:
    /**
     * @brief Construct a new Reservation object
     *
     * @param name of the reserver
     * @param p
     * @param n note left for the reservation
     * @param s whether it is reservation or maintenance
     */
    Reservation(std::string name, const DatePeriod &p, std::string n = "None.\n", bool s = false);
    Reservation(const Reservation &) = delete;
    Reservation &operator=(const Reservation &) = delete;

    /**
     * @brief see if this Reservation is active (today is part of the period)
     *
     * @return true Reservation is active
     * @return false Reservation is not active (past or future)
     */
    bool isActive() const { return state == ACTIVE; }

    /**
     * @brief see if this Reservation is past (today is after end of period)
     *
     * @return true Reservation is past
     * @return false Reservation is not past (active or future)
     */
    bool isPast() const { return state == PAST; }

    /**
     * @brief see if this Reservation is a maintenance
     *
     * @return true this Reservation is a maintenace
     * @return false this Reservation is for a guest
     */
    bool isServiced() const { return service; }

    /**
     * @brief get beginning Date of this Reservation
     *
     * @return Date beginning of the Reservation
     */
    Date getFrom() const { return period.from; }

    /**
     * @brief get end Date of this Reservation
     *
     * @return Date end of the Reservation
     */
    Date getTo() const { return period.to; }

    /**
     * @brief get count of nights of this Reservation
     *
     * @return unsigned count of nights of this Reservation
     */
    unsigned getNights() const { return period.length(); }

    /**
     * @brief get the note to this Reservation
     *
     * @return std::string
     */
    std::string getNote() const { return note; }

    /**
     * @brief update the state of the reservation based on new today's Date (d)
     *
     * @param d new today's Date
     */
    void onDate(Date d);

    /**
     * @brief see what would the state of this Reservation be on particular Date
     *
     * @return ReservationState state on desired Date
     */
    ReservationState stateOnDate(Date) const;

    /**
     * @brief try to change end of period for earlier end of this Reservation
     *
     * @return true end date modified for leaving in advance
     * @return false new leaving Date not appropriate for earlier leaving
     */
    bool LeavingInAdvance(Date);

    /**
     * @brief write the Reservation data into binary file opened by ofstream
     *
     * @param ofs output stream connected to binary file
     */
    void writeToBinaryFile(std::ofstream &ofs);

    /**
     * @brief read the Reservation data from binary file opened by ifstream
     *
     * @param ofs input stream connected to binary file
     */
    void readDataFromBinary(std::ifstream &ifs);
};

/**
 * @brief overloaded operator for ouputting a reservation
 *
 * @return std::ostream& ouput stream
 */
std::ostream &operator<<(std::ostream &, const Reservation &);

#endif