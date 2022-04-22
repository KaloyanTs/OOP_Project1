#include "Room.hpp"

std::ostream &operator<<(std::ostream &os, const Room &R)
{
    return os << R.getNumber() << '\t' << R.getBedCount();
}

bool Room::accomodateHere()
{
    if (!free)
        return false;
    return !(free = false);
}

bool Room::freeRoom()
{
    if (free)
        return false;
    return !(free = true);
}
