#ifndef __HOTELINTERFACE_HPP
#define __HOTELINTERFACE_HPP
#include <iomanip>
#include <iostream>
#include "Constants.hpp"
#include "Hotel.hpp"

class HotelInterface
{
public:
    static void createHeader(Hotel &H);
    static void beginDay();
};

#endif