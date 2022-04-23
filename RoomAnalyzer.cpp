#include "RoomAnalyzer.hpp"

Room *RoomAnalyzer::suggest(HotelBuilding &hB, unsigned beds, Date from, Date to)
{
    size_t roomCount = hB.getRoomCount();
    float *score = new float[roomCount];
    for (unsigned i = 0; i < roomCount; ++i)
    {
        if (hB.rooms[i]->getBedCount() < beds)
            score[i] = -1;
        else
        {
            // todo
        }
    }

    sortRooms(hB, score);

    std::cout << "Most suitable reservations are:\n";
    for (unsigned i = 0; i < roomCount && i < DISPLAY; ++i)
        std::cout << '\t' << i + 1 << ".\t" << hB.rooms[i] << '\n';

    size_t choose;
    do
    {
        std::cout << "Choose a room among 1-" << (DISPLAY < roomCount ? DISPLAY : roomCount) << ": ";
        std::cin >> choose;
    } while (choose < 1 || choose > DISPLAY && choose > roomCount);

    delete[] score;
    return hB.rooms[choose - 1];
}

void RoomAnalyzer::sortRooms(HotelBuilding &hB, float *score)
{
}
