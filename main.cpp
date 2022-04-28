#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include "Hotel.hpp"
const size_t DISPLAY_WIDTH = 130;

const char cmdArr[6][2][100] = {
    {{"To make a reservation, enter "},
     {"<reserve: [Room number] [Accomodation date] [Departure date] {Guest name[;]} {Note}>"}},
    {{"To see list of free rooms for a particular date, enter "},
     {"<available: [date]>"}},
    {{"To free a room now, enter "},
     {"<free: [Room number]>"}},
    {{"To get report about the reservations of a room over a period of time, enter "},
     {"<report: [From date] [To date]>"}},
    {{"To request a room for guests, enter"},
     {"<request: [minimal number of beds] [Accomodation date] [Departure date]>"}},
    {{"To close a room for maintenance, enter"},
     {"<maintenance: [room number] [From date] [To date] [Note]>"}}};

bool workDay(Hotel &H)
{
    char cmd[100];
    std::cin.getline(cmd, 100, ':');
    while (strchr(cmd, '\n'))
    {
        std::cerr << "Uknown command!\n";
        std::cin.getline(cmd, 100);
        std::cin.getline(cmd, 100, ':');
    }
    while (*cmd && strcmp(cmd, "close"))
    {
        if (!strcmp(cmd, "day"))
        {
            H.nextDay();
            std::cin.get();
            return true;
        }
        if (!strcmp(cmd, "request"))
        {
            unsigned beds;
            DatePeriod per;
            std::cin >> beds >> per;
            std::cin.get();
            H.searchRoom(beds, per);
        }
        else if (!strcmp(cmd, "free"))
        {
            unsigned number;
            std::cin >> number;
            std::cin.get();
            H.freeRoom(number);
        }
        else if (!strcmp(cmd, "report"))
        {
            DatePeriod per;
            std::cin >> per;
            std::cin.get();
            H.getReport(per);
        }
        else if (!strcmp(cmd, "reserve"))
        {
            unsigned number;
            DatePeriod per;
            std::string name = "", note = "";
            std::cin >> number >> per;
            std::cin.get(*cmd);
            if (*cmd != '\n')
            {
                std::cin.getline(cmd, 100, ';');
                name = cmd;
                std::cin.getline(cmd, 100);
                if (*cmd)
                {
                    note = cmd;
                    H.reserveRoom(number, per, name, note);
                }
                else
                {
                    H.reserveRoom(number, per, name);
                }
            }
            else
                H.reserveRoom(number, per);
        }
        // todo else if other commands
        std::cin.getline(cmd, 100, ':');
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
                      << std::right << std::setw(DISPLAY_WIDTH - strlen(cmdArr[i][0]))
                      << cmdArr[i][1] << '\n';
    } while (workDay(H));

    return 0;
}