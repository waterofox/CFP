#include "Member_Tasks_Model.h"
#include "Member_Contest_Model.h"

void Member_Tasks_Model::sync_table()
{
	auto wbs = table.workbook().worksheet("db");

	for (int i = 3; i <= wbs.rowCount(); ++i)
	{
		tasks.insert({ wbs.cell(1,i).value().getString(),i });
	}

	DB_Model::sync_table();
}

void Member_Tasks_Model::complete_solution(unsigned short const& task, const std::string& member_name)
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

	wbs.cell(task, members[member_name]).value() = 1;
	members_data[members[member_name]].insert(task);

}


bool Member_Tasks_Model::is_task_exsits(const std::string& task_name)
{
	auto pot_task = tasks.find(task_name);
	if (pot_task != tasks.end())
	{
		return true;
	}

	return false;
}

const std::unordered_set<unsigned short>& Member_Tasks_Model::get_member_tasks(const std::string& member_name)
{
	return members_data[members[member_name]];
}

unsigned short Member_Tasks_Model::get_task(const std::string& task_name)
{
	if (is_task_exsits(task_name))
	{
		return tasks[task_name];
	}
	
	return 0;
}

unsigned short Member_Tasks_Model::add_new_task(const std::string& task_name)
{
	if (is_task_exsits(task_name))
	{
		return get_task(task_name);
	}

	auto wbs = table.workbook().worksheet("db");
	
	wbs.cell(1, wbs.columnCount() + 1).value() = task_name;
	tasks[task_name] = wbs.rowCount();
}

Member_Tasks_Model::Member_Tasks_Model()
{
	table_path = "tables\\mems_tasks.xlsx";
}
