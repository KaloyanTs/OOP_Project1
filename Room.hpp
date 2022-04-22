#ifndef __ROOM_HPP
#define __ROOM_HPP
#include <iostream>
#include "Types.hpp"
#include "Guest.hpp"

class Room
{
    unsigned number;
    unsigned bedCount;
    const Guest *guest;

public:
    Room(unsigned n, unsigned bC, const Guest &g) : number(n), bedCount(bC), guest(&g) {}
    unsigned getNumber() const { return number; }
    unsigned getBedCount() const { return bedCount; }
    bool accomodateHere(const Guest &);
    bool freeRoom();
};

std::ostream &operator<<(std::ostream &os, const Room &R);

#endif