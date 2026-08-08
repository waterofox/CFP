#include "Parser.h"

void Parser::start()
{
	bool models_started_flag = true;
	if (!member_achivments_db.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member achivments model started\n");
	}

	if (!member_contests_db.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member contests model started\n");
	}

	if (!member_tasks_db.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member tasks model started\n");
	}
	
	if (!member_stats.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member stats model started\n");
	}

	if (!models_started_flag) 
	{
		printf("PARSER ERROR: failed to start models\n");
		return;
	}

	XLDocument cf_status;
	cf_status.open("cf_status.xlsx");
	if (!cf_status.isOpen())
	{
		printf("PARSER ERROR: falied to open cf table\n");
		return;
	}

	//============================================================================================================================================

	auto wbs = cf_status.workbook().worksheet("Status");

	for (int i = 1; i <= wbs.rowCount(); ++i)
	{
		std::string member = wbs.cell(i, 3).value().getString();
		std::string task = wbs.cell(i, 4).value().getString();
		std::string contest = wbs.cell(i, 10).value().getString();

		//---------------------------------------------------------------------------------------------------------------------------------------
		//member parsing

		if (!member_achivments_db.is_member_exits(member))
		{
			member_achivments_db.add_member(member);
			member_contests_db.add_member(member);
			member_tasks_db.add_member(member);

			member_stats.add_member(member);
		}

		//---------------------------------------------------------------------------------------------------------------------------------------
		//task parsing

		if (!member_tasks_db.is_task_exsits(task))
		{
			member_tasks_db.add_new_task(task);
		}

		std::string task_status = wbs.cell(i, 6).value().getString();

		if (task_status == "OK") 
		{
			auto pot_task = member_tasks_db.get_member_tasks(member).find(member_tasks_db.get_task(task));
			if (pot_task == member_tasks_db.get_member_tasks(member).end())
			{
				member_stats.set_value(member, "correct_by_correct",
					member_stats.get_value(member, "correct_by_correct") + 1);

				member_stats.set_value(member, "total_tasks",
					member_stats.get_value(member, "total_tasks") + 1);

				member_tasks_db.complete_solution(member_tasks_db.get_task(task), member);
			}
		}
	}


	//============================================================================================================================================

	cf_status.close();

	member_achivments_db.stop();
	member_tasks_db.stop();
	member_contests_db.stop();

	member_stats.stop();

}
