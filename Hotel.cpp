#include "Hotel.hpp"

Date Hotel::now = Date::getToday();

void Hotel::nextDay()
{
    ++now;
}
