#include "String.hpp"

String::String(const char *_str)
    : m_size(0)
{
    for (const char *p = _str; *p; ++p)
        ++m_size;
    m_capacity = m_size;
    str = new char[m_capacity + 1];
    for (unsigned i = 0; i < m_size; ++i)
        str[i] = _str[i];
    str[m_size] = '\0';
}

void String::copy(const String &other)
{
    delete[] str;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    str = new char[m_capacity + 1];
    for (unsigned i = 0; i <= m_size; ++i)
        str[i] = other.str[i];
}

void String::expand(size_t newCap)
{
    if (newCap <= m_capacity)
    {
        std::cerr << "Error on expanding String!\n";
        return;
    }
    m_capacity = newCap;
    char *newStr = new char[m_capacity + 1];
    for (unsigned i = 0; i <= m_size; ++i)
        newStr[i] = str[i];
    delete[] str;
    str = newStr;
}

String::String(const String &other)
    : str(nullptr)
{
    copy(other);
}

String &String::operator+=(const String &other)
{
    return *this = *this + other;
}

String::~String()
{
    delete[] str;
}

String String::operator+(const String &other) const
{
    String res;
    delete[] res.str;
    res.str = new char[m_size + other.m_size + 1];
    for (unsigned i = 0; i < m_size; ++i)
        res.str[i] = str[i];
    for (unsigned i = 0; i < other.m_size; ++i)
        res.str[m_size + i] = other.str[i];
    res.str[m_size + other.m_size] = '\0';
    res.m_size = m_size + other.m_size;
    res.m_capacity = res.m_size;
    return res;
}

String &String::operator=(const String &other)
{
    if (this != &other)
        copy(other);
    return *this;
}

String &String::shrink_to_fit()
{
    return *this = String(c_str());
}

std::ostream &operator<<(std::ostream &os, const String &S)
{
    return os << S.c_str();
}