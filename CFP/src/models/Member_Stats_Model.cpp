#include "Member_Stats_Model.h"

void Member_Stats_Model::sync_table()
{
	auto wbs = table.workbook().worksheet("sta");
	std::unordered_map<unsigned short, unsigned int> meta_row;

	for (int i = 1; i <= wbs.columnCount(); ++i)
	{
		stats.insert({wbs.cell(1,i).value().getString(),i});
		meta_row[i] = 0;
	}

	for (int i = 2; i <= wbs.rowCount(); ++i)
	{
		members_stats.insert({i,meta_row});
	}

	for (auto& row : members_stats)
	{
		for (auto& stat : stats)
		{
			(row.second)[stat.second] = wbs.cell(row.first, stat.second).value();
		}
	}
	
}

void Member_Stats_Model::push_table()
{
	auto wbs = table.workbook().worksheet("sta");

	for (auto& row : members_stats)
	{
		for (auto& stat : stats)
		{
			wbs.cell(row.first, stat.second).value() = (row.second)[stat.second];
		}
	}
}

void Member_Stats_Model::add_member(unsigned int const& member_id)
{
	if (is_member_exsits(member_id)) { return; }
	std::unordered_map<unsigned short, unsigned int> meta_row;
	
	members_stats.insert({ members_stats.size()+2,meta_row});
	
}

bool Member_Stats_Model::is_member_exsits(unsigned int const& member_id)
{;
	if (members_stats.find(member_id) != members_stats.end()) { return true; }
	return false;
}

int unsigned& Member_Stats_Model::get_value(unsigned int const& member_id, const std::string& stat_name)
{
	return members_stats[member_id][stats[stat_name]];
}

void Member_Stats_Model::set_value(unsigned int const& member_id, const std::string& stat_name, unsigned int const& value)
{
	members_stats[member_id][stats[stat_name]] = value;
}

Member_Stats_Model::Member_Stats_Model()
{
	table_path = "tables\\mems_stats.xlsx";
}
