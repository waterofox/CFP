#include "Member_Stats_Model.h"

void Member_Stats_Model::sync_table()
{
	auto wbs = table.workbook().worksheet("sta");
	std::unordered_map<unsigned short, unsigned int> meta_row;

	for (int i = 2; i <= wbs.columnCount(); ++i)
	{
		stats.insert({wbs.cell(1,i).value().getString(),i});
		meta_row[i] = 0;
	}

	for (int i = 2; i <= wbs.rowCount(); ++i)
	{
		members.insert({wbs.cell(i,1).value().getString(),i});
		members_stats.insert({i,meta_row});
	}
	
	for (auto& member : members)
	{
		unsigned short const& id = member.second;
		
		auto& row = members_stats[id];

		for (auto& stat : stats)
		{
			unsigned short const& id_st = stat.second;

			row[id_st] = wbs.cell(id, id_st).value().get<unsigned int>();
		}
	}

	
}

bool Member_Stats_Model::add_member(const std::string& member_name)
{
	if (is_member_exsits(member_name)) { return true; }

	auto wbs = table.workbook().worksheet("sta");

	wbs.cell(wbs.rowCount() + 1, 1).value() = member_name;

	std::unordered_map<unsigned short, unsigned int> meta_row;

	for (int i = 2; i <= wbs.columnCount(); ++i)
	{
		stats.insert({ wbs.cell(1,i).value().getString(),i });
		meta_row[i] = 0;
		wbs.cell(wbs.rowCount(), i).value() = 0;
	}

	//auto new_row = wbs.row(wbs.rowCount() + 1);
	//(*new_row.cells().begin()).value() = member_name;

	members.insert({member_name,wbs.rowCount()});
	members_stats.insert({ wbs.rowCount(),meta_row });
}

bool Member_Stats_Model::is_member_exsits(const std::string& member_name)
{
	auto pot_member = members.find(member_name);
	if (pot_member != members.end()) { return true; }
	return false;
}

int unsigned& Member_Stats_Model::get_value(const std::string& member_name, const std::string stat_name)
{
	return members_stats[members[member_name]][stats[stat_name]];
}

void Member_Stats_Model::set_value(const std::string& member_name, const std::string stat_name, int unsigned const& value)
{
	auto wbs = table.workbook().worksheet("sta");

	wbs.cell(members[member_name], stats[stat_name]).value() = value;
	members_stats[members[member_name]][stats[stat_name]] = value;
}

Member_Stats_Model::Member_Stats_Model()
{
	table_path = "tables\\mems_stats.xlsx";
}
