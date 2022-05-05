#ifndef __CONSTANTS_HPP
#define __CONSTANTS_HPP
#include <iostream>

/**
 * @brief array keeping days past from January 1st
 *
 */
const unsigned daysFromBeginning[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

const size_t DISPLAY_WIDTH = 130;

const size_t COMMANDS = 8;

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

#endif