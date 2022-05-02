#ifndef __DATE_HPP
#define __DATE_HPP
#include <iostream>
#include <ctime>

/**
 * @brief array keeping days past from January 1st
 *
 */
const unsigned daysFromBeginning[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

class Date
{
    /**
     * @brief containers for day, month and year of the Date
     *
     */
    unsigned short day, month, year;
    /**
     * @brief function telling validity if this Date
     *
     * @return true this Date is valid
     * @return false this Date is not valid
     */
    bool isVaid() const;
    /**
     * @brief checks if a year is leap
     *
     * @param y checked year
     * @return true the year is leap
     * @return false the year is not leap
     */
    bool isLeap(unsigned y) const;

public:
    /**
     * @brief Construct a new Date object from day, month and year. Default Date is 1/1/1900
     *
     * @param d day
     * @param m month
     * @param y year
     */
    Date(unsigned short d = 1, unsigned short m = 1, unsigned short y = 1900) : day(d), month(m), year(y) {}
    /**
     * @brief checks if this Date is chronologically before other Date
     *
     * @param other compared Date
     * @return true this Date is chronologically before other
     * @return false this Date is not chronologically before other
     */
    bool operator<(const Date other) const;
    /**
     * @brief see operator<
     */
    bool operator<=(const Date other) const;
    /**
     * @brief checks if this Date is chronologically after other Date
     *
     * @param other compared Date
     * @return true this Date is chronologically after other
     * @return false this Date is not chronologically after other
     */
    bool operator>(const Date other) const;
    /**
     * @brief see operator>
     */
    bool operator>=(const Date other) const;
    /**
     * @brief checks if two dates are identical
     *
     * @param other compared Date
     * @return true the dates are identical
     * @return false the dates are not identical
     */
    bool operator==(const Date other) const;
    /**
     * @brief records this Date in buffer in format YYYY-MM-DD
     *
     * @param buf buffer where Date is recorded
     * @return const char* pointer to beginning of buf
     */
    const char *operator()(char *buf) const;
    /**
     * @brief
     *
     * @param other Date
     * @return int difference between of this Date and other
     */
    int operator-(Date other) const;
    /**
     * @brief overloaded prefix incremention operator for Date
     *
     * @return Date& reference to this Date
     */
    Date &operator++();

    /**
     * @brief Get the today date
     *
     * @return Date
     */
    static Date getToday();

    /**
     * @brief overloaded operator for inputing Date
     *
     * @param is input stream
     * @param d Date to be input
     * @return std::istream& reference to the input stream
     */
    friend std::istream &operator>>(std::istream &is, Date &d);
    /**
     * @brief overloaded operator for outputing Date
     *
     * @param os output stream
     * @param d Date to be output
     * @return std::ostream& reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Date &d);
};

struct DatePeriod
{
    /**
     * @brief beginning Date of the period
     *
     */
    Date from;

    /**
     * @brief end Date of the period
     *
     */
    Date to;

    /**
     * @brief distance in days of the period
     *
     * @return unsigned days between beginning and end
     */
    unsigned length() const { return to - from; }

    /**
     * @brief moving period one day froward
     *
     * @return DatePeriod& this DatePeriod
     */
    DatePeriod &operator++();

    void readProper();
};

/**
 * @brief overloaded operator>> for DatePeriod input
 *
 * @param is input stream
 * @param dP DatePeriod to be input
 * @return std::istream& this input stream
 */
std::istream &operator>>(std::istream &is, DatePeriod &dP);

#endif