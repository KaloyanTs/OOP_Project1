#ifndef __CONSTANTS_HPP
#define __CONSTANTS_HPP
#include <cstddef>

/**
 * @brief array keeping days past from January 1st
 *
 */
const unsigned daysFromBeginning[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

/**
 * @brief width of the console used for centering the text
 *
 */
const size_t DISPLAY_WIDTH = 130;

/**
 * @brief number of different commands to use for a Hotel
 *
 */
const size_t COMMANDS = 8;

/**
 * @brief max length of strings (char arrays)
 *
 */
const size_t STRING_MAX_LENGTH = 128;

/**
 * @brief const variable keeping minimal size of the reservations list
 *
 */
const size_t INIT_CAPACITY = 2;

/**
 * @brief max number of rooms to be printed
 *
 */
const size_t DISPLAY = 5;

/**
 * @brief array of all available commands and instructions how to use them
 *
 */
const char cmdArr[COMMANDS][2][STRING_MAX_LENGTH] = {
    {{"To make a reservation, enter "},
     {"reserve: <Room number> <Accomodation date> <Departure date> {Guest name<;>} {Note}"}},
    {{"To see list of free rooms for a particular date, enter "},
     {"available: <date>"}},
    {{"To free a room now, enter "},
     {"free: <Room number>"}},
    {{"To get report about the reservations of a room over a period of time, enter "},
     {"report: <From date> <To date>"}},
    {{"To request a room for guests, enter"},
     {"request: <minimal number of beds> <Accomodation date> <Departure date>"}},
    {{"To close a room for maintenance, enter"},
     {"maintenance: <room number> <From date> <To date> <Note>"}},
    {{"To see activity of all rooms, enter "}, {" <rooms:"}},
    {{"To see soonest date a room is free for some nights, enter "},
     {"plan: <Room number> <Number of nights>"}}};

#endif