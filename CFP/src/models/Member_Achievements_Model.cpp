#include "Member_Achievements_Model.h"
#include "Member_Stats_Model.h"


void Member_Achievements_Model::sync_table()
{
	auto wbs = table.workbook().worksheet("ach");

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
				members_achivments[j].insert(i);
			}
		}
	}
}

bool Member_Achievements_Model::add_member(const std::string& member_name)
{

	if (is_member_exits(member_name)) { return true; }

	if (!is_started())
	{
		printf("MODEL ERROR: failed to add member in table\n");
		return false;
	}
	
	auto wbs = table.workbook().worksheet("ach");
	unsigned short id = 0;  
	wbs.cell("C1").value() = 0;

	wbs.cell(2, id + 2).value() = member_name;
	members.insert({member_name,id+2});
	wbs.cell("C1").value() = id + 1;

	return true;
}


unsigned short Member_Achievements_Model::get_member(const std::string& member_name)
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

void Member_Achievements_Model::give_achivment(unsigned short const& achiment,const std::string& member_name)
{
	if (!is_started())
	{
		printf("MODEL ERROR: fialed to give an achivment");
		return;
	}

	if (!is_member_exits(member_name))
	{
		if (!add_member(member_name))
		{
			return;
		}
	}

	auto wbs = table.workbook().worksheet("ach");
	
	wbs.cell(achiment, members[member_name]).value() = 1;
	members_achivments[members[member_name]].insert(achiment);
	
}

const std::unordered_set<unsigned short>& Member_Achievements_Model::get_member_achivments(const std::string& member_name)
{
	if (is_member_exits(member_name))
	{
		return members_achivments[members[member_name]];
	}
	printf("MODEL ERROR: member %s does not exsits", "member");
	//return std::unordered_set<unsigned short>();
}

bool Member_Achievements_Model::is_member_exits(const std::string& member_name)
{
	auto pot_member = members.find(member_name);
	if (pot_member != members.end()) { return true; }
	return false;
}

Member_Achievements_Model::Member_Achievements_Model()
{
	table_path = "tables\\mems_achivments.xlsx";
}
