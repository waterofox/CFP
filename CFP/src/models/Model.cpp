#include "Model.h"

#include <ios>

bool Model::start()
{

	table.open(table_path);
	if (table.isOpen())
	{
		started = true;
		sync_table();
	}
	else
	{
		std::cout << "MODEL ERROR: table" + table_path + " isn't opened\n";
	}

	return started;
}

void Model::stop()
{
	if (started)
	{
		push_table();
		table.save();
		table.close();
		started = false;
	}
}

bool Model::is_started()
{
	return started;
}
