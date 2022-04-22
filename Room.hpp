#ifndef __ROOM_HPP
#define __ROOM_HPP
#include <iostream>
#include "Types.hpp"
#include "Reservation.hpp"

class Room
{
    unsigned number;
    unsigned bedCount;
    bool free;

public:
    Room(unsigned n, unsigned bC, bool f = true) : number(n), bedCount(bC), free(f) {}

    unsigned getNumber() const { return number; }
    unsigned getBedCount() const { return bedCount; }
    bool isFree() const { return free; }

    bool accomodateHere();
    bool freeRoom();
    //friend Reservation::Reservation(const char *, Room *, Date, Date, const char *);
};

std::ostream &operator<<(std::ostream &os, const Room &R);

#endif