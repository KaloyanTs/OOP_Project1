#include "RoomAnalyzer.hpp"

void RoomAnalyzer::suggest(HotelBuilding &hB, unsigned beds, DatePeriod period)
{
    size_t roomCount = hB.getRoomCount();
    unsigned *score = new unsigned[roomCount];
    for (unsigned i = 0; i < roomCount; ++i)
    {
        if (hB.rooms[i]->getBedCount() < beds)
            score[i] = -1;
        else if (!hB.rooms[i]->isFreeInPeriod(period))
            score[i] = -2;
        else
            score[i] = (hB.rooms[i]->getBedCount() - beds);
    }

    sortRooms(hB, score, roomCount);

    std::cout << "Most suitable rooms are:\n";
    for (unsigned i = 0; i < roomCount && i < DISPLAY; ++i)
    {
        std::cout << '\t' << i + 1 << ".\t" << *hB.rooms[i] << ": ";
        if (score[i] < 2)
            std::cout << "NOT ";
        std::cout << "available from " << period.from << " to " << period.to;
    }

    delete[] score;
}

void RoomAnalyzer::sortRooms(HotelBuilding &hB, unsigned *score, size_t size)
{
    unsigned iMax = 0;
    for (unsigned i = 0; i < size - 1; ++i)
    {
        iMax = 0;
        for (unsigned j = i + 1; j < size; ++j)
            if (score[j] < score[iMax] ||
                score[j] == score[iMax] &&
                    hB.rooms[j]->getNumber() < hB.rooms[iMax]->getNumber())
                iMax = j;
        Room *tmp = hB.rooms[i];
        hB.rooms[i] = hB.rooms[iMax];
        hB.rooms[iMax] = tmp;
        float ftmp = score[i];
        score[i] = score[iMax];
        score[iMax] = ftmp;
    }
}
