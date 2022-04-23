#ifndef __ROOM_HPP
#define __ROOM_HPP
#include <iostream>
#include "Types.hpp"
#include "Reservation.hpp"
const size_t INIT_CAPACITY = 2;

class Room
{
    unsigned number;
    unsigned bedCount;
    Reservation **reservations;
    size_t resCount, resCapacity;

    void expand();
    void shrink();

public:
    Room(unsigned n, unsigned bC);
    Room(const Room &) = delete;
    Room &operator=(const Room &) = delete;
    ~Room();

    unsigned getNumber() const { return number; }
    unsigned getBedCount() const { return bedCount; }
    bool isFreeNow() const;

    bool accomodateHere(const Reservation &res);
    bool freeRoom();

    void newDate(Date);

    bool isFreeOnDate(Date) const;
};

std::ostream &operator<<(std::ostream &os, const Room &R);

#endif