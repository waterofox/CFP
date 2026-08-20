#pragma once

#include <ctime>

class Date
{

public:
	short day  = 1;
	short month = 1;
	short year = 0;

	Date()  = default;
	~Date() = default;

	Date(long long const& unix_time);
};

