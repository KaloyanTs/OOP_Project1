#include "HotelBuilding.hpp"

HotelBuilding::HotelBuilding(const char *roomsTextFile)
{
    std::ifstream ifs(roomsTextFile, std::ios::in);
    unsigned number, bedCount;
    if (!ifs.is_open())
    {
        std::cerr << "Something went wrong on reading Room data from \"" << roomsTextFile << "\".\n";
        rooms = nullptr;
        size = 0;
        return;
    }
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
