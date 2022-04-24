#include "Hotel.hpp"

Date Hotel::now = Date::getToday();

void Hotel::nextDay()
{
    building->newDate(++now);
}

Hotel &Hotel::showAvailableRooms(std::ostream &os, Date d)
{
    os << "Available rooms for " << d << " are:\n";
    building->showAvailableRooms(os, d);
    return *this;
}

Hotel &Hotel::getReport(Date from, Date to)
{
    building->createReport(from, to);
    return *this;
}
