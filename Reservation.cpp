#include "Reservation.hpp"

Reservation::Reservation(std::string name, Date f, Date t, std::string n, bool s)
    : guestName(name),
      note(n),
      from(f), to(t),
      service(s),
      state(UNKNOWN)
{
}

void Reservation::onDate(Date d)
{
    if (d < from)
        state = FUTURE;
    else if (d >= to)
        state = PAST;
    else
        state = ACTIVE;
}

ReservationState Reservation::stateOnDate(Date d) const
{
    if (d < from)
        return FUTURE;
    if (d >= to)
        return PAST;
    return ACTIVE;
}

bool Reservation::LeavingInAdvance(Date newTo)
{
    if (newTo >= to || newTo < from)
        return false;
    to = newTo;
    return true;
}
