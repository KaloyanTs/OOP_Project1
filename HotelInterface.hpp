#ifndef __HOTELINTERFACE_HPP
#define __HOTELINTERFACE_HPP
#include <iomanip>
#include <iostream>
#include "Constants.hpp"
#include "Hotel.hpp"

/// Utility Class taking care of the UI of the program
class HotelInterface
{
public:
    /**
     * @brief print to stdout centered name of the Hotel
     *
     * @param H Hotel whose name is to be printed
     */
    static void createHeader(Hotel &H);

    /**
     * @brief print the today's date and available commands to use for a Hotel
     *
     */
    static void beginDay();
};

#endif