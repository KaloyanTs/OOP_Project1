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
    do
    {
        std::cout << "Today is " << Hotel::today() << ".\n";
    } while (workDay(H));

    return 0;
}