#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include "Hotel.hpp"
const size_t DISPLAY_WIDTH = 130;
const size_t COMMANDS = 7;

const char cmdArr[COMMANDS][2][100] = {
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
     {"<maintenance: [room number] [From date] [To date] [Note]>"}},
    {{"To see activity of all rooms, enter "}, {"<rooms:>"}}};

void beginDay()
{
    std::cout << "Today is " << Hotel::today() << ".\n";
    std::cout.fill(' ');
    for (unsigned i = 0; i < COMMANDS; ++i)
        std::cout << '\t' << cmdArr[i][0]
                  << std::right << std::setw(DISPLAY_WIDTH - strlen(cmdArr[i][0]))
                  << cmdArr[i][1] << '\n';
}

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
        else if (!strcmp(cmd, "rooms"))
        {
            std::cin.get();
            H.showToday();
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
        else if (!strcmp(cmd, "maintenance"))
        {
            unsigned number;
            DatePeriod per;
            std::cin >> number >> per;
            std::cin.get();
            std::cin.getline(cmd, 100);
            H.serviceRoom(number, per, cmd);
        }
        else if (!strcmp(cmd, "available"))
        {
            Date d;
            std::cin >> d;
            std::cin.get();
            H.showAvailableRooms(std::cout, d);
        }
        std::cin.getline(cmd, 100, ':');
        while (strchr(cmd, '\n'))
        {
            std::cerr << "Uknown command!\n";
            std::cin.getline(cmd, 100);
            std::cin.getline(cmd, 100, ':');
        }
    }
    return false;
}

int main()
// fix last reservation end date problem
{
    Hotel H("h.rooms");
    unsigned countOfSpaces = (DISPLAY_WIDTH - strlen("<<< ") - strlen(" SYSTEM >>>") - H.getName().size()) / 2;
    std::cout << '\t';
    for (unsigned i = 0; i < DISPLAY_WIDTH; ++i)
        std::cout << '-';
    std::cout << '\n';
    for (unsigned i = 0; i < countOfSpaces; ++i)
        std::cout << ' ';
    std::cout << "<<< " << H.getName() << " SYSTEM >>>\n";
    std::cout << '\t';
    for (unsigned i = 0; i < DISPLAY_WIDTH; ++i)
        std::cout << '-';
    std::cout << '\n';
    // H.reserveRoom(102, {Date(10, 6, 2023), Date(5, 8, 2023)});
    // H.reserveRoom(102, {Date(10, 4, 2023), Date(5, 6, 2023)});
    // H.reserveRoom(102, {Date(10, 6, 2024), Date(5, 8, 2024)});
    // H.reserveRoom(102, {Date(10, 4, 2022), Date(11, 4, 2022)});
    // H.reserveRoom(102, {Date(10, 4, 2022), Date(11, 4, 2022)});
    // H.showAvailableRooms(std::cout, Date(12, 6, 2023));
    do
    {
        beginDay();
    } while (workDay(H));

    return 0;
}