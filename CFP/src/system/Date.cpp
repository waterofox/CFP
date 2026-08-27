#include "Date.h"

Date::Date(long long const& unix_time)
{
    tm timeinfo;
    gmtime_s(&timeinfo ,&unix_time);

    day = timeinfo.tm_mday;
    month = timeinfo.tm_mon + 1;
    year = timeinfo.tm_year + 1900;

    h = timeinfo.tm_hour;
    m = timeinfo.tm_min;
    s = timeinfo.tm_sec;
}

int Date::days(const Date& date1, const Date& date2) {
    tm tm1;
    tm1.tm_year = date1.year - 1900;
    tm1.tm_mon = date1.month - 1;
    tm1.tm_mday = date1.day;
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 0;
    time_t time1 = mktime(&tm1);

    tm tm2;
    tm2.tm_year = date2.year - 1900;
    tm2.tm_mon = date2.month - 1;
    tm2.tm_mday = date2.day;
    tm2.tm_hour = 0;
    tm2.tm_min = 0;
    tm2.tm_sec = 0;
    time_t time2 = mktime(&tm2);

    double diffSeconds = difftime(time2, time1);
    int diffDays = static_cast<int>(diffSeconds / 86400);

    return (diffDays < 0) ? -diffDays : diffDays;
}