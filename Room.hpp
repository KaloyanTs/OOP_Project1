#ifndef __ROOM_HPP
#define __ROOM_HPP
#include <iostream>
#include <string>
#include "Types.hpp"
#include "Reservation.hpp"
#include "Hotel.hpp"

/**
 * @brief const varieble keeping minimal size of the reservations list
 *
 */
const size_t INIT_CAPACITY = 2;

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
     * @brief expand a reservations list
     *
     */
    void expand(Reservation **&arr, size_t &size, size_t &capacity);
    /**
     * @brief shrink a reservations list
     *
     */
    void shrink(Reservation **&arr, size_t &size, size_t &capacity);

    unsigned daysTakenInPeriod(Date from, Date to) const;

    bool newReservation(std::string name, std::string note, Date from, Date to, bool service);

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
    void changeLeaving(Reservation *, Date newDate); // todo must be private

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

    void showReservationsInPeriod(std::ostream &os, Date from, Date to) const;

    bool addReservation(std::string name, std::string note, Date from, Date to);

    bool closeForService(std::string note, Date from, Date to);
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