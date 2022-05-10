#include <iostream>
#include <iomanip>
#include "Constants.hpp"
#include "String.hpp"
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