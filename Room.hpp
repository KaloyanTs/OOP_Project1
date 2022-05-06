#ifndef __ROOM_HPP
#define __ROOM_HPP
#include <iostream>
#include <string>
#include "Types.hpp"
#include "Reservation.hpp"
#include "Hotel.hpp"
#include "Constants.hpp"

/**
 * @brief Class representing a room in hotel
 *
 */
class Room
{
    /**
     * @brief ID of the room
     *
     */
    unsigned number;
    /**
     * @brief number of beds in the Room
     *
     */
    unsigned bedCount;
    /**
     * @brief list of reservations assigned to the Room
     *
     */
    Reservation **reservations;
    /**
     * @brief size and capacity of the reservations list
     *
     */
    size_t resCount, resCapacity;

    /**
     * @brief list of past reservations assigned to the Room
     *
     */
    Reservation **pastReservations;
    /**
     * @brief size and capacity of the past reservations list
     *
     */
    size_t pastCount, pastCapacity;

    /**
     * @brief expand a reservations list doubling its capacity
     *
     */
    void expand(Reservation **&arr, size_t &size, size_t &capacity);
    /**
     * @brief shrink a reservations list (capcity becomes as much as size)
     *
     */
    void shrink(Reservation **&arr, size_t &size, size_t &capacity);

    unsigned daysTakenInPeriod(const DatePeriod &period) const;

    bool newReservation(std::string name, std::string note, const DatePeriod &period, bool service);

    void moveToPast();

public:
    /**
     * @brief Construct a new Room object
     *
     * @param n number of constructed Room
     * @param bC number of beds in constructed Room
     */
    Room(unsigned n, unsigned bC);
    /**
     * @brief forbidden copying of rooms
     *
     */
    Room(const Room &) = delete;
    /**
     * @brief forbidden copying of rooms
     *
     */
    Room &operator=(const Room &) = delete;
    /**
     * @brief Destroy the Room object
     *
     */
    ~Room();

    unsigned getNumber() const { return number; }
    unsigned getBedCount() const { return bedCount; }
    bool isFreeNow() const;

    /**
     * @brief try to free this room
     *
     * @return true sucesfully freed room
     * @return false room is already free
     */
    bool freeRoom(Reservation *&currentRes);

    void changeLeaving(Reservation *, Date newDate);

    /**
     * @brief apply new Date to state of all reservations and respectively of the room availability
     *
     */
    void newDate(Date);

    /**
     * @brief see if this room is free in certain date
     *
     * @return true the room is free
     * @return false the room is taken
     */
    bool isFreeOnDate(Date) const;

    /**
     * @brief see if this Room is free in particular period of time (it is free in all days of the period)
     *
     * @param period period of time
     * @return true the room is free (in all days of the period)
     * @return false the room is not free (there is a day in period when the room is taken)
     */
    bool isFreeInPeriod(const DatePeriod &period) const;

    /**
     * @brief print to output stream info about the number of nights (if positive) in a period this Room has been taken
     *
     * @param os output stream
     * @param period period of time
     * @return true there has been taken for at least one night and info has been printed
     * @return false the room has been free during this period and no info has been printed
     */
    bool showReservationsInPeriod(std::ostream &os, const DatePeriod &period) const;

    /**
     * @brief try to add Reservation to this Room
     *
     * @param name name of the guest
     * @param note note to this Reservation
     * @param period period of time
     * @return true successfully added Reservation
     * @return false adding a Reservation failed (the room is not free in this DatePeriod)
     */
    bool addReservation(std::string name, std::string note, const DatePeriod &period);

    /**
     * @brief try to add Reservation (about a maintenance) to this Room
     *
     * @param note note to this maintenance
     * @param period period of time
     * @return true successfully added maintenance
     * @return false adding a maintenance failed (the room is not free in this DatePeriod)
     */
    bool closeForService(std::string note, const DatePeriod &period);

    /**
     * @brief print to stdout information about this Room latest busyness
     *
     */
    void showActivity() const;

    void writeToBinaryFile(std::ofstream &ofs);

    void readDataFromBinary(std::ifstream &ifs);
};

/**
 * @brief prints Room's base info (number and bedCount)
 *
 * @param os output stream
 * @param R Room to be printed
 * @return std::ostream& same output stream
 */
std::ostream &operator<<(std::ostream &os, const Room &R);

#endif