#include "Member_Contest_Model.h"

void Member_Contest_Model::sync_table()
{
	auto wbs = table.workbook().worksheet("db");

	for (int i = 3; i <= wbs.rowCount(); ++i)
	{
		contests.insert({ wbs.cell(1,i).value().getString(),i });
	}

	DB_Model::sync_table();
}

void Member_Contest_Model::attended_contest(unsigned short const& contest, const std::string& member_name)
{
	if (!is_started())
	{
		printf("MODEL ERROR: fialed to resume solution");
		return;
	}

	if (!is_member_exits(member_name))
	{
		if (!add_member(member_name))
		{
			printf("MODEL ERROR: fialed to resume solution");
			return;
		}
	}

	auto wbs = table.workbook().worksheet("db");

	wbs.cell(contest, members[member_name]).value() = 1;
	members_data[members[member_name]].insert(contest);
}

bool Member_Contest_Model::is_contest_exsits(const std::string& contest_name)
{
	auto pot_task = contests.find(contest_name);
	if (pot_task != contests.end())
	{
		return true;
	}

	return false;
}

const std::unordered_set<unsigned short>& Member_Contest_Model::get_member_contets(const std::string& member_name)
{
	return members_data[members[member_name]];
}

unsigned short Member_Contest_Model::get_contest(const std::string& task_name)
{
	if (is_contest_exsits(task_name))
	{
		return contests[task_name];
	}

	return 0;
}

unsigned short Member_Contest_Model::add_new_contest(const std::string& contest_name)
{
	if (is_contest_exsits(contest_name))
	{
		return get_contest(contest_name);
	}

	auto wbs = table.workbook().worksheet("db");

	wbs.cell(1, wbs.columnCount() + 1).value() = contest_name;
	contests[contest_name] = wbs.rowCount();
}

Member_Contest_Model::Member_Contest_Model()
{
	table_path = "tables\\mems_contests.xlsx";
}

