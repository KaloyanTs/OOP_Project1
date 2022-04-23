#ifndef __RESERVATION_HPP
#define __RESERVATION_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "Date.hpp"
#include "Hotel.hpp"
#include <cstring>
#include <cassert>
#include <fstream>

enum ReservationState
{
    UNKNOWN = 0,
    PAST,
    ACTIVE,
    FUTURE
};

class Reservation
{
    char *guestName, *note;
    Date from, to;
    ReservationState state;
    bool service;

    void clear();

    void record(const Hotel &);

public:
    Reservation(const char *name, Date f, Date t, const char *n = "None.\n", bool s = false);
    Reservation(const Reservation &) = delete;
    Reservation &operator=(const Reservation &) = delete;
    // todo use String Reservation(const Reservation &other);
    // todo use String Reservation &operator=(const Reservation &other);
    ~Reservation();

    bool isActive() const { return state == ACTIVE; }
    bool isPast() const { return state == PAST; }
    bool isServiced() const { return service; }

    void onDate(Date d);

    ReservationState stateOnDate(Date) const;

    bool LeavingInAdvance(Date);
};

std::ostream &operator<<(std::ostream &, const Reservation &);

#endif