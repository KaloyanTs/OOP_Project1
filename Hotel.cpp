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

Hotel &Hotel::getReport(DatePeriod &period)
{
    building->createReport(period);
    return *this;
}

bool Hotel::reserveRoom(unsigned number, const DatePeriod &period, std::string name, std::string s)
{
    if (!((*building)[number]))
    {
        std::cerr << "No such Room.\n";
        return false;
    }
    if ((*building)[number]->addReservation(name, s, period))
    {
        std::clog << "Reservation successfully made!\n";
        return true;
    }
    std::cerr << "Room is reserved for this period.\n";
    return false;
}

Hotel::Hotel(std::string hotelDataFile)
{
    std::ifstream ifs(hotelDataFile, std::ios::in);
    assert(ifs.is_open());
    size_t length;
    ifs >> length;
    ifs.get();
    name = readFromIfstream(ifs, length);
    building = new HotelBuilding(ifs);
    ifs.close();
}

std::string readFromIfstream(std::ifstream &ifs, size_t len)
{
    char *buf = new char[len + 1];
    ifs.getline(buf, len + 1);
    buf[len] = '\0';
    std::string res(buf);
    delete[] buf;
    return res;
}

Hotel::~Hotel()
{
    delete building;
}

bool Hotel::serviceRoom(unsigned number, const DatePeriod &period, std::string note)
{
    if (!((*building)[number]))
    {
        std::cerr << "No such Room.\n";
        return false;
    }
    if ((*building)[number]->closeForService(note, period))
    {
        std::clog << "Service successfully planned!\n";
        return true;
    }
    std::cerr << "Room is reserved for this period.\n";
    return false;
}

bool Hotel::freeRoom(unsigned number)
{
    Reservation *tmp;
    if (!((*building)[number]))
    {
        std::cerr << "No such room.\n";
        return false;
    }
    if ((*building)[number]->freeRoom(tmp))
    {
        std::clog << "Room freed successfully.\n";
        return true;
    }
    std::cerr << "Room is free already!\n";
    return true;
}

void Hotel::searchRoom(unsigned minBeds, const DatePeriod &period) const
{
    building->suggestRoom(minBeds, period);
}

Hotel &Hotel::showToday()
{
    building->showRoomsStatesToday(now);
    return *this;
}