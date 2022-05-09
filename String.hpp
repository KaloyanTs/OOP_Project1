#ifndef __STRING_HPP
#define __STRING_HPP
#include <iostream>

/// Class representing dynamic string (array of characters)
class String
{
    /// dynamic array of characters
    char *str;

    /// storage of the array
    size_t m_size, m_capacity;

    /**
     * @brief makes this String exact copy (deep copies) the String other
     *
     * @param other String
     */
    void copy(const String &other);

    /**
     * @brief resizes the array to newCap
     *
     * @param newCap new capacity of the array
     * @note newCap must be greater than capacity
     */
    void expand(size_t newCap);

public:
    /**
     * @brief Construct a new String object by array of chars
     *
     * @param _str
     */
    String(const char *_str = "");
    /**
     * @brief copy constructor (makes deep copy of other)
     *
     * @param other String
     */
    String(const String &other);

    /**
     * @brief makes deep copy of other into this
     *
     * @param other String
     * @return String& this String
     */
    String &operator=(const String &other);

    /**
     * @brief Destroy the String object
     *
     */
    ~String();

    /**
     * @brief get the size of the array (number of symbols before the '\0')
     */
    size_t size() const { return m_size; }

    /**
     * @brief get the maximum characters the array can store
     */
    size_t capacity() const { return m_capacity; }

    /**
     * @brief get pointer to the beginning of the array
     */
    char *c_str() const { return str; }

    /// concatenation of two strings
    String operator+(const String &other) const;

    /// concatenate another String to this String
    String &operator+=(const String &other);

    /// cast this String to const char * by returning pointer to the beginning
    operator const char *() const { return c_str(); }

    /// make the capacity equal to the size
    String &shrink_to_fit();
};

/// print this String to the given output stream
std::ostream &operator<<(std::ostream &os, const String &S);

#endif