#include "HotelInterface.hpp"

void HotelInterface::createHeader(Hotel &H)
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

void HotelInterface::beginDay()
{
    std::cout << "Today is " << Hotel::today() << ".\n";
    std::cout.fill(' ');
    for (unsigned i = 0; i < COMMANDS; ++i)
        std::cout << '\t' << cmdArr[i][0]
                  << std::right << std::setw(DISPLAY_WIDTH - strlen(cmdArr[i][0]))
                  << cmdArr[i][1] << '\n';
}
