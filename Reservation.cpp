#include "Reservation.hpp"

Reservation::Reservation(std::string name, const DatePeriod &p, std::string n, bool s)
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

void Reservation::writeToBinaryFile(std::ofstream &ofs)
{
    size_t size = guestName.size();
    ofs.write((const char *)&size, sizeof(size));
    ofs.write(guestName.c_str(), size);

    size = note.size();
    ofs.write((const char *)&size, sizeof(size));
    ofs.write(note.c_str(), size);

    period.from.writeToBinaryFile(ofs);
    period.to.writeToBinaryFile(ofs);

    ofs.write((const char *)&service, sizeof(service));
}

void Reservation::readDataFromBinary(std::ifstream &ifs)
{
    size_t length;
    ifs.read((char *)&length, sizeof(length));
    char *buf = new char[length + 1];
    ifs.read(buf, length);
    buf[length] = '\0';
    guestName = buf;
    delete[] buf;

    ifs.read((char *)&length, sizeof(length));
    buf = new char[length + 1];
    ifs.read(buf, length);
    buf[length] = '\0';
    note = buf;
    delete[] buf;

    period.from.readDataFromBinary(ifs);
    period.to.readDataFromBinary(ifs);

    ifs.read((char *)&service, sizeof(service));
    onDate(Hotel::today());
}