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
        std::cout << '\t' << i + 1 << ".\t" << *hB.rooms[i] << " -> ";
        if ((int)score[i] == -2)
            std::cout << "NOT ";
        std::cout << "available from " << period.from << " to " << period.to << '\n';
    }

    delete[] score;
}

void RoomAnalyzer::sortRooms(HotelBuilding &hB, unsigned *score, size_t size)
{
    unsigned iMax = 0;
    for (unsigned i = 0; i < size - 1; ++i)
    {
        iMax = i;
        for (unsigned j = i + 1; j < size; ++j)
            if (score[j] < score[iMax] ||
                score[j] == score[iMax] &&
                    hB.rooms[j]->getNumber() < hB.rooms[iMax]->getNumber())
                iMax = j;
        Room *tmp = hB.rooms[i];
        hB.rooms[i] = hB.rooms[iMax];
        hB.rooms[iMax] = tmp;
        unsigned ftmp = score[i];
        score[i] = score[iMax];
        score[iMax] = ftmp;
    }
}

void RoomAnalyzer::soonestFreePeriod(const HotelBuilding &hB, unsigned number, unsigned nights, Date today)
{
    assert(nights > 0);
    DatePeriod per;
    per.from = per.to = today;
    for (unsigned i = 0; i < nights; ++i)
        ++per.to;
    assert(hB[number] != nullptr);
    while (!hB[number]->isFreeInPeriod(per))
        ++per;
    std::clog << "Room #" << number << " is available for " << nights << " nights from " << per.from << ".\n";
}
