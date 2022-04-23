#include "Reservation.hpp"

Reservation::~Reservation()
{
    clear();
}

Reservation::Reservation(const char *name, Date f, Date t, const char *n)
    : guestName(new char[strlen(name) + 1]),
      note(new char[strlen(n) + 1]),
      from(f), to(t)
{
    assert(room && name && note);
    strcpy(guestName, name);
    strcpy(note, n);

    state = UNKNOWN;
    // todo check other reservations for simultaneousity
}

void Reservation::clear()
{
    delete[] guestName;
    delete[] note;
}

void Reservation::record(const Hotel &H)
{
    char buf[100]; // todo String
    strcpy(buf, H.getName());
    strcat(buf, ".history");
    std::ofstream ofs(buf, std::ios::out | std::ios::app);
    if (!ofs.is_open())
    {
        std::cerr << "Something went wrong on recording Reservation.\n";
        return;
    }
    ofs << from << '-' << to << ' ' << room->getNumber() << ' ';
    // todo use String ofs << guestName << ' ' << note << '\n';

    ofs.close();
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
