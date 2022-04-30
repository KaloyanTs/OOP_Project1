#include "HotelBuilding.hpp"

HotelBuilding::HotelBuilding(std::ifstream &ifs)
{
    unsigned number, bedCount;
    ifs >> size;
    rooms = new Room *[size];
    for (unsigned i = 0; i < size; ++i)
    {
        ifs >> number >> bedCount;
        rooms[i] = new Room(number, bedCount);
    }
}

HotelBuilding::~HotelBuilding()
{
    for (unsigned i = 0; i < size; ++i)
        delete rooms[i];
    delete[] rooms;
}

Room *HotelBuilding::operator[](unsigned roomNumber) const
{
    unsigned i = 0;
    while (i < size && roomNumber != rooms[i]->getNumber())
        ++i;
    if (i == size)
        return nullptr;
    return rooms[i];
}

void HotelBuilding::newDate(Date newD)
{
    for (unsigned i = 0; i < size; ++i)
        rooms[i]->newDate(newD);
}

void HotelBuilding::showAvailableRooms(std::ostream &os, Date d) const
{
    for (unsigned i = 0; i < size; ++i)
        if (rooms[i]->isFreeOnDate(d))
            os << *rooms[i] << '\n';
}

void HotelBuilding::createReport(DatePeriod &period) const
{
    if (period.from > Hotel::today())
        return;
    if (period.to > Hotel::today())
        period.to = Hotel::today();
    char buf[30];
    strcpy(buf, "reports/report-");
    period.from(buf + 15);
    strcat(buf, ".txt");
    std::ofstream ofs(buf, std::ios::out);
    if (!ofs.is_open())
        return;
    ofs << "Report for the usage of the rooms between " << period.from << " and " << period.to << ":\n\t";
    for (unsigned i = 0; i < size; ++i)
        if (rooms[i]->showReservationsInPeriod(ofs, period))
            ofs << '\t';
    ofs.close();
    std::clog << "Report \"" << period.from << "\" created successfully.\n";
}

void HotelBuilding::suggestRoom(unsigned beds, const DatePeriod &period)
{
    RoomAnalyzer::suggest(*this, beds, period);
}

void HotelBuilding::showRoomsStatesToday(Date today) const
{
    for (unsigned i = 0; i < size; ++i)
        rooms[i]->showActivity();
}

void HotelBuilding::showRoomForNights(unsigned number, unsigned nights, Date today) const
{
    RoomAnalyzer::soonestFreePeriod(*this, number, nights, today);
}