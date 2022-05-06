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

    // todo better scoring

    sortRoomsByScore(hB, score, 0, roomCount - 1);

    std::cout << "Most suitable rooms are:\n";
    for (unsigned i = 0; i < roomCount && i < DISPLAY; ++i)
    {
        std::cout << '\t' << i + 1 << ".\t" << *hB.rooms[i] << " -> ";
        if ((int)score[i] == -2)
            std::cout << "NOT ";
        std::cout << "available from " << period.from << " to " << period.to << '\n';
    }

    delete[] score;

    sortRoomsByNumber(hB, 0, roomCount - 1);
}

void RoomAnalyzer::sortRoomsByScore(HotelBuilding &hB, unsigned *score, size_t from, size_t to)
{
    if (to <= from + 1)
        return;
    size_t pivotIndex = from;
    for (size_t i = from; i < to; ++i)
    {
        if (score[i] < score[to] ||
            score[i] == score[to] &&
                hB.rooms[i]->getNumber() < hB.rooms[to]->getNumber())
        {
            swap<Room *>(hB.rooms[i], hB.rooms[pivotIndex]);
            swap<unsigned>(score[pivotIndex++], score[i]);
        }
    }
    swap<Room *>(hB.rooms[to], hB.rooms[pivotIndex]);
    swap<unsigned>(score[to], score[pivotIndex]);

    if (pivotIndex > from)
        sortRoomsByScore(hB, score, from, pivotIndex - 1);
    sortRoomsByScore(hB, score, pivotIndex + 1, to);
}

void RoomAnalyzer::sortRoomsByNumber(HotelBuilding &hB, size_t from, size_t to)
{
    if (to <= from + 1)
        return;
    size_t pivotIndex = from;
    for (size_t i = from; i < to; ++i)
        if (hB.rooms[i]->getNumber() < hB.rooms[to]->getNumber())
            swap<Room *>(hB.rooms[i], hB.rooms[pivotIndex++]);

    swap<Room *>(hB.rooms[to], hB.rooms[pivotIndex]);

    if (pivotIndex > from)
        sortRoomsByNumber(hB, from, pivotIndex - 1);
    sortRoomsByNumber(hB, pivotIndex + 1, to);
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