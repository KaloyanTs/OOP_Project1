#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include "Constants.hpp"
#include "Hotel.hpp"

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
    {{"To see activity of all rooms, enter "}, {"<rooms:>"}},
    {{"To see soonest date a room is free for some nights, enter "},
     {"<plan: [Room number] [Number of nights]>"}}};

void createHeader(Hotel &H)
{
    unsigned countOfSpaces = (DISPLAY_WIDTH - strlen("<<< ") - strlen(" SYSTEM >>>") - H.getName().size()) / 2;
    std::cout << '\t';
    for (unsigned i = 0; i < DISPLAY_WIDTH; ++i)
        std::cout << '-';
    std::cout << '\n'
              << '\t';
    for (unsigned i = 0; i < countOfSpaces; ++i)
        std::cout << ' ';
    std::cout << "<<< " << H.getName() << " SYSTEM >>>\n";
    std::cout << '\t';
    for (unsigned i = 0; i < DISPLAY_WIDTH; ++i)
        std::cout << '-';
    std::cout << '\n';
}

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
            std::cin >> beds;
            per.readProper();
            std::cin.get();
            H.searchRoom(beds, per);
        }
        else if (!strcmp(cmd, "rooms"))
        {
            std::cin.get();
            H.showToday();
        }
        else if (!strcmp(cmd, "plan"))
        {
            unsigned number, nights;
            std::cin >> number >> nights;
            std::cin.get();
            H.seeRoomForNights(number, nights);
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
            per.readProper();
            std::cin.get();
            H.getReport(per);
        }
        else if (!strcmp(cmd, "reserve"))
        {
            unsigned number;
            DatePeriod per;
            std::cin >> number;
            per.readProper();
            std::string name = "", note = "";
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
                    H.reserveRoom(number, per, name);
            }
            else
                H.reserveRoom(number, per);
        }
        else if (!strcmp(cmd, "maintenance"))
        {
            unsigned number;
            DatePeriod per;
            std::cin >> number;
            per.readProper();
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
            std::cerr << "Unknown command!\n";
            std::cin.getline(cmd, 100);
            std::cin.getline(cmd, 100, ':');
        }
    }
    return false;
}

int main()
{
    Hotel H("h.rooms");
    createHeader(H);
    do
    {
        beginDay();
    } while (workDay(H));

    return 0;
}