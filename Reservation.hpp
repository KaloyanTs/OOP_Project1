#ifndef __RESERVATION_HPP
#define __RESERVATION_HPP
#include "Types.hpp"
#include "Room.hpp"
#include "Date.hpp"
#include "Hotel.hpp"
#include <cstring>
#include <cassert>
#include <fstream>
#include <string>

enum ReservationState
{
    UNKNOWN = 0,
    PAST,
    ACTIVE,
    FUTURE
};

class Reservation
{
    std::string guestName, note;
    DatePeriod period;
    ReservationState state;
    bool service;

public:
    Reservation(std::string name, DatePeriod p, std::string n = "None.\n", bool s = false);
    Reservation(const Reservation &) = delete;
    Reservation &operator=(const Reservation &) = delete;

    bool isActive() const { return state == ACTIVE; }
    bool isPast() const { return state == PAST; }
    bool isServiced() const { return service; }
    Date getFrom() const { return period.from; }
    Date getTo() const { return period.to; }
    unsigned getNights() const { return period.length(); }

    void onDate(Date d);

    ReservationState stateOnDate(Date) const;

    bool LeavingInAdvance(Date);
};

std::ostream &operator<<(std::ostream &, const Reservation &);

#endif