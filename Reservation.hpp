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
    Room *room;

    void clear();

    void record(const Hotel &H);

public:
    Reservation(const char *name, Date f, Date t, const char *n = "None.\n");
    Reservation(const Reservation &res) = delete;
    Reservation &operator=(const Reservation &other) = delete;
    // todo use String Reservation(const Reservation &other);
    // todo use String Reservation &operator=(const Reservation &other);
    ~Reservation();

    bool isActive() const { return state == ACTIVE; }
    bool isPast() const { return state == PAST; }

    void onDate(Date d);

    ReservationState stateOnDate(Date d)const;
};

std::ostream &operator<<(std::ostream &os, const Reservation &other);

#endif