#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Constants.hpp"
#include "HotelInterface.hpp"
#include "Hotel.hpp"

int main()
{
    Hotel H("h.rooms");
    HotelInterface::createHeader(H);
    do
    {
        HotelInterface::beginDay();
    } while (H.workDay());

    return 0;
}