#include "Room.hpp"

std::ostream &operator<<(std::ostream &os, const Room &R)
{
    return os << R.getNumber() << '\t' << R.getBedCount();
}

bool Room::accomodateHere(const Reservation &res)
{
    if (!isFree())
        return false;
    return currentReservation = &res;
}

bool Room::freeRoom()
{
    if (isFree())
        return false;
    return !(currentReservation = nullptr);
}
