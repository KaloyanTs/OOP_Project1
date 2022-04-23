#include "Reservation.hpp"

Reservation::~Reservation()
{
    clear();
}

Reservation::Reservation(const Hotel &h, const char *name, Room *r, Date f, Date t, const char *n)
    : guestName(new char[strlen(name) + 1]),
      note(new char[strlen(n) + 1]),
      room(r),
      from(f), to(t),
      active(false)
{
    assert(room && name && note);
    strcpy(guestName, name);
    strcpy(note, n);

    past = h.today() < from;
    active = !past && h.today() < to;
    if (active)
        r->accomodateHere(*this);
    if (!past)
        record(h);
    // todo check other reservations for simultaneousity

    // if ok
    // if active then
    // if accomodate there -> perfect
    // else something went wrong (on checking availability)
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
