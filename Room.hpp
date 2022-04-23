#ifndef __ROOM_HPP
#define __ROOM_HPP
#include <iostream>
#include "Types.hpp"
#include "Reservation.hpp"

class Room
{
    unsigned number;
    unsigned bedCount;
    const Reservation *currentReservation;

public:
    Room(unsigned n, unsigned bC) : number(n), bedCount(bC), currentReservation(nullptr) {}

    unsigned getNumber() const { return number; }
    unsigned getBedCount() const { return bedCount; }
    bool isFree() const { return !currentReservation; }

    bool accomodateHere(const Reservation &res);
    bool freeRoom();
    // friend Reservation::Reservation(const char *, Room *, Date, Date, const char *);
};

std::ostream &operator<<(std::ostream &os, const Room &R);

#endif