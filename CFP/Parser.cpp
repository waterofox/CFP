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

	if (!member_db.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member model started\n");
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

	printf("\nstart parsing sc_status.xlsx\n");
	system("pause");

	auto wbs = cf_status.workbook().worksheet("Status");
	int len = wbs.rowCount();

	float one_ps = float(len) / 100.f;
	float tmp = 1.f / one_ps;
	float pars_status_bar = 0;

	for (int i = 2; i <= len; ++i)
	{
		//pars_status_bar += tmp;
		//std::cout << pars_status_bar << "% - completed\n";

		std::string member = wbs.cell(i, 3).value().getString();
		std::string task = wbs.cell(i, 4).value().getString();
		std::string contest = wbs.cell(i, 9).value().getString();

		//---------------------------------------------------------------------------------------------------------------------------------------
		//member parsing

		if (!member_db.is_data_exsits(member))
		{
			member_db.add_member(member);
			member_stats.add_member(member_db.get_data_id(member));
		}


		//---------------------------------------------------------------------------------------------------------------------------------------
		//task parsings

		if (!member_tasks_db.is_data_exsits(task))
		{
			member_tasks_db.add_data(task);
		}

		//---------------------------------------------------------------------------------------------------------------------------------------
		//contest parsing

		if (!member_contests_db.is_data_exsits(contest))
		{
			member_contests_db.add_data(contest);
		}

		int member_id = member_db.get_data_id(member);
		int task_id = member_tasks_db.get_data_id(task);
		int contest_id = member_contests_db.get_data_id(contest);

		std::string task_status = wbs.cell(i, 6).value().getString();

		if (task_status == "WRONG_ANSWER")
		{
			int current_wa_by_wa = member_stats.get_value(member_id, "war_by_war");
			member_stats.set_value(member_id, "war_by_war", current_wa_by_wa + 1);
			
			member_stats.set_value(member_id, "wa", 1);
		}
		else
		{
			member_stats.set_value(member_id, "war_by_war", 0);
		}

		if (task_status == "OK")
		{

			auto& member_info = member_db.members[member_id];

			if (member_info.tasks.find(task_id) == member_info.tasks.end())
			{
				//first correcet solution of task

				member_stats.set_value(member_id, "correct_by_correct", member_stats.get_value(member_id, "correct_by_correct") + 1);
				member_stats.set_value(member_id, "total_tasks", member_stats.get_value(member_id, "total_tasks") + 1);

				member_info.tasks.insert(task_id);

				//new contest check

				if (member_info.contests.find(contest_id) == member_info.contests.end())
				{
					member_stats.set_value(member_id, "total_contest", member_stats.get_value(member_id, "total_contest") + 1);

					member_info.contests.insert(contest_id);
				}
			}
		}
		else
		{
			member_stats.set_value(member_id, "correct_by_correct", 0);
		}

		if (task_status == "COMPILATION_ERROR")
		{
			member_stats.set_value(member_id, "ce", 1);
		}
		
		if (task_status == "TIME_LIMIT_EXCEEDED")
		{
			member_stats.set_value(member_id, "tl", 1);
		}

		if (task_status == "MEMORY_LIMIT_EXCEEDED")
		{
			member_stats.set_value(member_id, "ml", 1);
		}

		//============================================================================================================================================
	}

	cf_status.close();

	member_achivments_db.stop();
	member_tasks_db.stop();
	member_contests_db.stop();
	member_db.stop();

	member_stats.stop();
}
