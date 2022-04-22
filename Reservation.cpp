#include "Reservation.hpp"

Reservation::Reservation(const Reservation &other)
{
}

Reservation::~Reservation()
{
    clear();
}

Reservation::Reservation(const char *name, Room *r, Date f, Date t, const char *n)
    : guestName(new char[strlen(name) + 1]),
      note(new char[strlen(n) + 1]),
      room(r),
      from(f), to(t),
      active(false)
{
    assert(room && name && note);
    strcpy(guestName, name);
    strcpy(note, n);
    // todo class must be defined inside the hotel class
    //  active = date>=from && date<to;
}

void Reservation::clear()
{
    delete[] guestName;
    delete[] note;
}
