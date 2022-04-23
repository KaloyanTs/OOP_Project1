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

bool Room::freeRoom(Reservation *&curRes)
{
    if (isFreeNow())
        return false;
    curRes = reservations[0];
    if (curRes->isActive())
        curRes->LeavingInAdvance(Hotel::today());

    if (!curRes->isServiced())
    {
        if (pastCount == pastCapacity)
            expand(pastReservations);
        pastReservations[pastCount++] = curRes;
    }
    else
        delete curRes;

    for (unsigned i = 0; i < resCount - 1; ++i)
        reservations[i] = reservations[i + 1];
    if (2 * resCount <= resCapacity && resCapacity > INIT_CAPACITY)
        shrink();
    return true;
}

Room::Room(unsigned n, unsigned bC)
    : number(n), bedCount(bC),
      reservations(new Reservation *[INIT_CAPACITY]),
      resCapacity(INIT_CAPACITY), resCount(0),
      pastReservations(new Reservation *[INIT_CAPACITY]),
      pastCapacity(INIT_CAPACITY), pastCount(0)
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

void Room::expand(Reservation **&arr)
{
    resCapacity = 2 * resCapacity;
    Reservation **newArr = new Reservation *[resCapacity];
    for (unsigned i = 0; i < resCount; ++i)
        newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
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
    if (reservations[0]->isPast())
    {
        if (pastCount == pastCapacity)
            expand(pastReservations);
        freeRoom(pastReservations[pastCount++]);
    }
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

unsigned Room::daysTakenInPeriod(Date from, Date to) const
{
    unsigned count = 0;
    if (to > Hotel::today())
        to = Hotel::today();
        
    // todo for(unsigned i=0;i<pastCount;++i)
    // todo calculations
}