#include "Reservation.hpp"

Reservation::Reservation(std::string name, DatePeriod p, std::string n, bool s)
    : guestName(name),
      note(n),
      period(p),
      service(s),
      state(UNKNOWN)
{
}

void Reservation::onDate(Date d)
{
    if (d < period.from)
        state = FUTURE;
    else if (d >= period.to)
        state = PAST;
    else
        state = ACTIVE;
}

ReservationState Reservation::stateOnDate(Date d) const
{
    if (d < period.from)
        return FUTURE;
    if (d >= period.to)
        return PAST;
    return ACTIVE;
}

bool Reservation::LeavingInAdvance(Date newTo)
{
    if (newTo >= period.to || newTo < period.from)
        return false;
    period.to = newTo;
    return true;
}
