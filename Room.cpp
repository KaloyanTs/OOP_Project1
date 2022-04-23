#include "Room.hpp"

std::ostream &operator<<(std::ostream &os, const Room &R)
{
    return os << R.getNumber() << '\t' << R.getBedCount();
}

// bool Room::accomodateHere(const Reservation &res)
// {
//     if (!isFree())
//         return false;
//     return currentReservation = &res;
// }

bool Room::freeRoom()
{
    if (isFreeNow())
        return false;
    delete reservations[0];
    for (unsigned i = 0; i < resCount - 1; ++i)
        reservations[i] = reservations[i + 1];
    if (2 * resCount <= resCapacity && resCapacity > INIT_CAPACITY)
        shrink();
    return true;
}

Room::Room(unsigned n, unsigned bC)
    : number(n), bedCount(bC),
      reservations(new Reservation *[INIT_CAPACITY]),
      resCapacity(INIT_CAPACITY), resCount(0)
{
}

void Room::shrink()
{
    resCapacity = resCount;
    Reservation **newArr = new Reservation *[resCapacity];
    for (unsigned i = 0; i < resCount; ++i)
        newArr[i] = reservations[i];
    delete[] reservations;
    reservations = newArr;
}

void Room::expand()
{
    resCapacity = 2 * resCapacity;
    Reservation **newArr = new Reservation *[resCapacity];
    for (unsigned i = 0; i < resCount; ++i)
        newArr[i] = reservations[i];
    delete[] reservations;
    reservations = newArr;
}

bool Room::isFreeNow() const
{
    return !resCount || !reservations[0]->isActive();
}

void Room::newDate(Date newD)
{
    if (!resCount)
        return;
    for (unsigned i = 0; i < resCount; ++i)
        reservations[i]->onDate(newD);
}

bool Room::isFreeOnDate(Date d) const
{
    if (!resCount || reservations[0]->stateOnDate(d))
        return true;
    unsigned i = 0;
    while (i < resCount && reservations[i]->stateOnDate(d) == FUTURE)
        ++i;
    return i == resCount || reservations[i]->stateOnDate(d) == PAST;
}

Room::~Room()
{
    for (unsigned i = 0; i < resCount; ++i)
        delete reservations[i];
    delete[] reservations;
}
