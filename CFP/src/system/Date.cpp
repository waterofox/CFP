#include "Date.h"

Date::Date(long long const& unix_time)
{
    auto timeinfo = gmtime(&unix_time);

    day = timeinfo->tm_mday;
    month = timeinfo->tm_mon + 1;
    year = timeinfo->tm_year + 1900;
}
