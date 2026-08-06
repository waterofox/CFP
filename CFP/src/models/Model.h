#pragma once
#include <string>

#include <OpenXLSX.hpp>

using namespace OpenXLSX;

class Model
{
protected:
	XLDocument table;
	std::string table_path;
	virtual void sync_table() = 0;

private:
	bool started = false;
	
public:

	virtual bool start();
	virtual void stop();

	bool is_started();
	virtual ~Model() = default;
};

