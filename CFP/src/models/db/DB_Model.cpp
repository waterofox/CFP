#include "DB_Model.h"

void DB_Model::sync_table()
{
	auto wbs = table.workbook().worksheet("db");

	for (int i = 2; i <= wbs.columnCount(); ++i)
	{
		if (wbs.cell(2, i).value().getString().length() == 0) { continue; }
		members.insert({ wbs.cell(2,i).value().getString(),i });
	}


	for (int i = 3; i <= wbs.rowCount(); ++i)
	{
		for (int j = 2; j <= wbs.columnCount(); ++j)
		{
			if (wbs.cell(i, j).value() == 1)
			{
				members_data[j].insert(i);
			}
		}
	}
}

bool DB_Model::add_member(const std::string& member_name)
{

	if (is_member_exits(member_name)) { return true; }

	if (!is_started())
	{
		printf("MODEL ERROR: failed to add member in table\n");
		return false;
	}

	auto wbs = table.workbook().worksheet("db");
	wbs.cell(2, wbs.columnCount() + 1).value() = member_name;
	members.insert({ member_name,wbs.columnCount() });

	return true;
}

unsigned short DB_Model::get_member(const std::string& member_name)
{
	if (!is_member_exits(member_name))
	{
		return -1;
	}
	else
	{
		return members[member_name];
	}
}

bool DB_Model::is_member_exits(const std::string& member_name)
{
	auto pot_member = members.find(member_name);
	if (pot_member != members.end()) { return true; }
	return false;
}