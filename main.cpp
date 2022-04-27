#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include "Hotel.hpp"

const char cmdArr[6][2][100] = {
    {{"To make a reservation, enter "},
     {"<reserve [Room number] [Accomodation date] [Departure date] {Guest name} {Note}>"}},
    {{"To see list of free rooms for a particular date, enter "},
     {"<available [date]>"}},
    {{"To free a room now, enter "},
     {"<free [Room number]>"}},
    {{"To get report about the reservations of a room over a period of time, enter "},
     {"<report [From date] [To date]>"}},
    {{"To request a room for guests, enter"},
     {"<request [minimal number of beds] [Accomodation date] [Departure date]>"}},
    {{"To close a room for maintenance, enter"},
     {"<close [room number] [From date] [To date] [Note]>"}}};

bool workDay(Hotel &H)
{
    char cmd[100];
    std::cin.getline(cmd, 100);
    std::istringstream iss;
    iss.str(cmd);
    iss.getline(cmd, iss.str().size() + 1, ' ');
    while (*cmd && strcmp(cmd, "close"))
    {
        if (!strcmp(cmd, "day"))
        {
            H.nextDay();
            return true;
        }
        if (!strcmp(cmd, "request"))
        {
            unsigned beds;
            Date from, to;
            iss >> beds >> from >> to;
            iss.get();
            H.searchRoom(beds, {from, to});
        }
        else if (!strcmp(cmd, "free"))
        {
            unsigned number;
            iss >> number;
            iss.get();
            H.freeRoom(number);
        }
        // todo else if other commands
        std::cin.getline(cmd, 100);
        // fix iss.str(cmd);
        //  std::cout << iss.peek() << '\n';
        iss.getline(cmd, iss.str().size() + 1, ' ');
    }
    return false;
}

int main()
{
    Hotel H("h.rooms");
    std::cout << "<<< " << H.getName() << " SYSTEM >>>\n";
    // H.reserveRoom(102, {Date(10, 6, 2023), Date(5, 8, 2023)});
    // H.reserveRoom(102, {Date(10, 4, 2023), Date(5, 6, 2023)});
    // H.reserveRoom(102, {Date(10, 6, 2024), Date(5, 8, 2024)});
    // H.reserveRoom(102, {Date(10, 4, 2022), Date(11, 4, 2022)});
    // H.reserveRoom(102, {Date(10, 4, 2022), Date(11, 4, 2022)});
    // H.showAvailableRooms(std::cout, Date(12, 6, 2023));
    do
    {
        std::cout << "Today is " << Hotel::today() << ".\n";
        std::cout.fill(' ');
        for (unsigned i = 0; i < 6; ++i)
            std::cout << '\t' << cmdArr[i][0]
                      << std::right << std::setw(130 - strlen(cmdArr[i][0])) << cmdArr[i][1] << '\n';
    } while (workDay(H));

    return 0;
}