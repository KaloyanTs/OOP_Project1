#include <iostream>
#include <cstring>
#include <string>
#include "Hotel.hpp"

bool workDay(Hotel &H)
{
    char cmd[100];
    std::cin.getline(cmd, 100);
    if (!strcmp(cmd, "close"))
        return false;
    if (!strcmp(cmd, "end day"))
    {
        H.nextDay();
        return true;
    }
    return false;
}

int main()
{
    Hotel H("h.history");
    std::cout << "<<< " << H.getName() << " SYSTEM >>>\n";
    // fix H.reserveRoom(102,{Date(10,6,2023),Date(5,8,2023)});
    H.showAvailableRooms(std::cout, Date(12, 6, 2023));
    do
    {
        std::cout << "Today is " << Hotel::today() << ".\n";
    } while (workDay(H));

    return 0;
}