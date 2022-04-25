#include "Room.hpp"

std::ostream &operator<<(std::ostream &os, const Room &R)
{
    if (&os == &std::cout)
        os << "Number: ";
    os << R.getNumber() << '\t';
    if (&os == &std::cout)
        os << "Beds: ";
    return os << R.getBedCount();
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
            expand(pastReservations, pastCount, pastCapacity);
        pastReservations[pastCount++] = curRes;
    }
    else
        delete curRes;

    for (unsigned i = 0; i < resCount - 1; ++i)
        reservations[i] = reservations[i + 1];
    if (2 * resCount <= resCapacity && resCapacity > INIT_CAPACITY)
        shrink(reservations, resCount, resCapacity);
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

void Room::shrink(Reservation **&arr, size_t &size, size_t &cap)
{
    if (!size)
        return;
    cap = size;
    Reservation **newArr = new Reservation *[cap];
    for (unsigned i = 0; i < size; ++i)
        newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
}

void Room::expand(Reservation **&arr, size_t &size, size_t &cap)
{
    cap = 2 * cap;
    Reservation **newArr = new Reservation *[cap];
    for (unsigned i = 0; i < size; ++i)
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
            expand(pastReservations, pastCount, pastCapacity);
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
    for (unsigned i = 0; i < pastCount; ++i)
        delete pastReservations[i];
    delete[] pastReservations;
}

unsigned Room::daysTakenInPeriod(DatePeriod period) const
{
    unsigned count = 0, firstRes, lastRes;
    firstRes = 0;
    while (firstRes < pastCount && pastReservations[firstRes]->stateOnDate(period.from) == PAST)
        ++firstRes;

    if (firstRes < pastCount)
    {
        if (pastReservations[firstRes]->stateOnDate(period.from) == ACTIVE)
            count += period.from - pastReservations[firstRes]->getFrom();
        lastRes = firstRes + 1;
        while (lastRes < pastCount && pastReservations[lastRes]->stateOnDate(period.to) != FUTURE)
        {
            ++lastRes;
            count += pastReservations[lastRes]->getNights();
        }
        if (lastRes < pastCount && pastReservations[lastRes]->stateOnDate(period.to) == ACTIVE)
            count -= pastReservations[lastRes]->getTo() - period.to;
    }

    return count;
}

void Room::showReservationsInPeriod(std::ostream &os, DatePeriod period) const
{
    unsigned count = daysTakenInPeriod(period);
    if (!count)
        return;
    os << "Room #" << number << " between " << period.from << " and " << period.to << ": " << count << " nights.\n";
}

bool Room::newReservation(std::string name, std::string note, DatePeriod period, bool service)
{
    if (!isFreeInPeriod(period))
        return false;

    if (resCapacity == resCount)
        expand(reservations, resCount, resCapacity);

    reservations[resCount++] = new Reservation(name, period, note, service);
    return true;
}

bool Room::addReservation(std::string name, std::string note, DatePeriod period)
{
    return newReservation(name, note, period, false);
}

bool Room::closeForService(std::string note, DatePeriod period)
{
    return newReservation(std::string("-"), note, period, true);
}

bool Room::isFreeInPeriod(DatePeriod period) const
{
    unsigned i = 0;
    while (i < resCount && reservations[i]->stateOnDate(period.from) == PAST)
        ++i;
    return !(i < resCount &&
             !(reservations[i]->stateOnDate(period.from) == FUTURE &&
               reservations[i]->stateOnDate(period.to) == FUTURE));
}