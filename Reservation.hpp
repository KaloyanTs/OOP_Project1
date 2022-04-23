#ifndef __RESERVATION_HPP
#define __RESERVATION_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "Date.hpp"
#include "Hotel.hpp"
#include <cstring>
#include <cassert>
#include <fstream>

class Reservation
{
    char *guestName, *note;
    Date from, to;
    bool active, past;
    Room *room;

    void clear();

    void record(const Hotel &H);

public:
    Reservation(const Hotel &h, const char *name, Room *r, Date f, Date t, const char *n = "None.\n");
    Reservation(const Reservation &res) = delete;
    Reservation &operator=(const Reservation &other) = delete;
    // todo use String Reservation(const Reservation &other);
    // todo use String Reservation &operator=(const Reservation &other);
    ~Reservation();

    bool isActive() const { return active; }
    bool isPast() const { return past; }
};

std::ostream &operator<<(std::ostream &os, const Reservation &other);

#endif