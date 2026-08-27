#include "Parser.h"

#include "src/system/Date.h"

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

	std::unordered_set<std::string> structs_contests   = {"570478","573635","604876" };
	std::unordered_set<std::string> math_contests      = {"568747","592220","596277","603194"};
	std::unordered_set<std::string> dp_contests        = {"580161","582016","598187","599925"};
	std::unordered_set<std::string> base_cpp_contests  = {"550879","552380","555156","557609","559129","561317"};
	std::unordered_set<std::string> graphs_contests    = {"585202","586871","588471","590577","601495","606492" };
	std::unordered_set<std::string> base_algo_contests = {"563482","565018","567104","572133","574668","583445","607871"};

	std::string member;
	std::string task;
	std::string contest;
	
	long long date_unix;
	Date date;
	Date last_date_task;

	int member_id;
	int task_id;
	int contest_id;

	bool is_new_task = false;

	std::string task_status;

	for (int i = 2; i <= len; ++i)
	{
		//pars_status_bar += tmp;
		//std::cout << pars_status_bar << "% - completed\n";

		is_new_task = false;

		member = wbs.cell(i, 3).value().getString();
		task = wbs.cell(i, 4).value().getString();
		contest = wbs.cell(i, 9).value().getString();

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

		member_id = member_db.get_data_id(member);
		task_id = member_tasks_db.get_data_id(task);
		contest_id = member_contests_db.get_data_id(contest);

		task_status = wbs.cell(i, 6).value().getString();

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

				is_new_task = true;

				member_stats.set_value(member_id, "correct_by_correct", member_stats.get_value(member_id, "correct_by_correct") + 1);
				member_stats.set_value(member_id, "total_tasks", member_stats.get_value(member_id, "total_tasks") + 1);

				member_info.tasks.insert(task_id);

				//base C++ check

				if (base_cpp_contests.find(contest) != base_cpp_contests.end())
				{
					member_stats.set_value(member_id, "total_base++", member_stats.get_value(member_id,"total_base++")+1);
				}

				//base algo check

				if (base_algo_contests.find(contest) != base_algo_contests.end())
				{
					member_stats.set_value(member_id, "total_base_algo", member_stats.get_value(member_id, "total_base_algo") + 1);
				}

				//structs check

				if (structs_contests.find(contest) != structs_contests.end())
				{
					member_stats.set_value(member_id, "total_struct", member_stats.get_value(member_id, "total_struct") + 1);
				}

				//math check

				if (math_contests.find(contest) != math_contests.end())
				{
					member_stats.set_value(member_id, "total_math", member_stats.get_value(member_id, "total_math") + 1);
				}

				//dp check

				if (dp_contests.find(contest) != dp_contests.end())
				{
					member_stats.set_value(member_id, "total_dp", member_stats.get_value(member_id, "total_dp") + 1);
				}

				//graphs check

				if (graphs_contests.find(contest) != graphs_contests.end())
				{
					member_stats.set_value(member_id, "total_graphs", member_stats.get_value(member_id, "total_graphs") + 1);
				}


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


		//dateing
		//-------------------------------------------------------------------------------------------------------------------------------------------
		
		date_unix = wbs.cell(i, 2).value().get<long long>();
		date = Date(date_unix);
		last_date_task = Date(member_stats.get_value(member_id, "last_task_date"));
		
		int day_diff = Date::days(date, last_date_task);

		if (day_diff >= 1)
		{
			//new day

			member_stats.set_value(member_id, "total_days", member_stats.get_value(member_id, "total_days") + 1);

			if (day_diff == 1)
			{
				member_stats.set_value(member_id, "day_by_day", member_stats.get_value(member_id, "day_by_day") + 1);	
			}
			else
			{
				member_stats.set_value(member_id, "day_by_day", 1);
			}

			if (task_status == "OK")
			{
				if (is_new_task)
				{
					member_stats.set_value(member_id, "day_tasks", 1);
					is_new_task = false;
				}
			}
			else
			{
				member_stats.set_value(member_id, "day_tasks", 0);
			}

		}
		else
		{
			//this day
			if (task_status == "OK" and is_new_task)
			{
				is_new_task = false;
				member_stats.set_value(member_id, "day_tasks", member_stats.get_value(member_id, "day_tasks") + 1);
			}
		}

		member_stats.set_value(member_id, "last_task_date", date_unix);

		//============================================================================================================================================
	}

	cf_status.close();

	member_achivments_db.stop();
	member_tasks_db.stop();
	member_contests_db.stop();
	member_db.stop();

	member_stats.stop();
}
