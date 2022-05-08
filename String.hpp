#ifndef __STRING_HPP
#define __STRING_HPP
#include <iostream>

class String
{
    char *str;
    size_t m_size, m_capacity;
    void copy(const String &other);
    void expand(size_t newCap);

public:
    String(const char *_str = "");
    String(const String &other);
    String &operator=(const String &other);
    ~String();

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    char *c_str() const { return str; }
    String operator+(const String &other) const;
    String &operator+=(const String &other);
    operator const char *() const { return c_str(); }
    String &shrink_to_fit();
};

std::ostream &operator<<(std::ostream &os, const String &S);

#endif