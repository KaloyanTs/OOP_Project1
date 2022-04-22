#ifndef __RESERVATION_HPP
#define __RESERVATION_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "Date.hpp"
#include <cstring>
#include <cassert>

class Reservation
{
    char *guestName, *note;
    Date from, to;
    bool active;
    Room *room;

    void clear();

public:
    Reservation(const char *name, Room *r, Date f, Date t, const char *n = "None.\n");
    Reservation(const Reservation &other);
    Reservation &operator=(const Reservation &other);
    ~Reservation();

    bool isActive() const { return active; }
};

std::ostream &operator<<(std::ostream &os, const Reservation &other);

#endif