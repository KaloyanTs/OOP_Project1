#include "HotelBuilding.hpp"

HotelBuilding::HotelBuilding(std::ifstream &ifs)
{
    // if (!ifs.is_open())
    // {
    //     std::cerr << "Something went wrong on reading Room data from \"" << roomsTextFile << "\".\n";
    //     rooms = nullptr;
    //     size = 0;
    //     return;
    // }
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

void HotelBuilding::createReport(Date from, Date to) const
{
    if (from > Hotel::today())
        return;
    if (to > Hotel::today())
        to = Hotel::today();
    char buf[22];
    strcpy(buf, "report-");
    from(buf + 7);
    strcat(buf, ".txt");
    std::ofstream ofs(buf, std::ios::out);
    if (!ofs.is_open())
        return;
    ofs << "Report for the usage of the rooms between " << from << " and " << to << ":\n";
    for (unsigned i = 0; i < size; ++i)
    {
        ofs << '\t';
        rooms[i]->showReservationsInPeriod(ofs, from, to);
    }
    ofs.close();
}
