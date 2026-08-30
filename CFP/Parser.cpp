#include "Parser.h"

#include "src/system/Date.h"

bool Parser::start_models()
{

	printf("Now starting models...\n");

	if (!member_achivments_db.start()) return false;
	if (!member_contests_db.start()) return false;
	if (!member_tasks_db.start()) return false;
	if (!member_db.start()) return false;
	
	if (!member_stats.start()) return false;

	return true;
}

void Parser::stop_models()
{
	member_achivments_db.stop();
	member_contests_db.stop();
	member_tasks_db.stop();
	member_db.stop();

	member_stats.stop();
}

void Parser::update_db_models(const std::string& member, const std::string& contest, const std::string& task)
{
	if (!member_db.is_data_exsits(member))
	{
		member_db.add_member(member);
		member_stats.add_member(member_db.get_data_id(member));
	}
	if (!member_tasks_db.is_data_exsits(task))
	{
		member_tasks_db.add_data(task);
	}
	if (!member_contests_db.is_data_exsits(contest))
	{
		member_contests_db.add_data(contest);
	}
}

void Parser::handle_wa_status(const int& member_id)
{
	member_stats.set_value(member_id, "war_by_war", member_stats.get_value(member_id, "war_by_war") + 1);
	member_stats.set_value(member_id, "wa", 1);
}

void Parser::handle_ok_status(const int& member_id, const int& constest_id, const int& task_id)
{

}


void Parser::handle_contests_stats(const int& member_id, const std::string& contest)
{
	if (base_cpp_contests.find(contest) != base_cpp_contests.end())
	{
		member_stats.set_value(member_id, "total_base++", member_stats.get_value(member_id, "total_base++") + 1);
	}
	else if (base_algo_contests.find(contest) != base_algo_contests.end())
	{
		member_stats.set_value(member_id, "total_base_algo", member_stats.get_value(member_id, "total_base_algo") + 1);
	}
    else if (structs_contests.find(contest) != structs_contests.end())
	{
		member_stats.set_value(member_id, "total_struct", member_stats.get_value(member_id, "total_struct") + 1);
	}
	else if (math_contests.find(contest) != math_contests.end())
	{
		member_stats.set_value(member_id, "total_math", member_stats.get_value(member_id, "total_math") + 1);
	}
	else if (dp_contests.find(contest) != dp_contests.end())
	{
		member_stats.set_value(member_id, "total_dp", member_stats.get_value(member_id, "total_dp") + 1);
	}
	else if (graphs_contests.find(contest) != graphs_contests.end())
	{
		member_stats.set_value(member_id, "total_graphs", member_stats.get_value(member_id, "total_graphs") + 1);
	}

}

void Parser::handle_new_day(const int& member_id,const int& day_diff)
{

	member_stats.set_value(member_id, "day_wa", 0);

	member_stats.set_value(member_id, "total_days", member_stats.get_value(member_id, "total_days") + 1);

	if (day_diff == 1)
	{
		member_stats.set_value(member_id, "day_by_day", member_stats.get_value(member_id, "day_by_day") + 1);
	}
	else
	{
		member_stats.set_value(member_id, "day_by_day", 1);
	}
}

void Parser::start()
{

	if (!start_models())
	{
		printf("PARSER ERRROR: failed to start models\n");
		stop_models();
		return;
	}

	printf("All models started!\n");

	printf("\nStart parsing sc_status.xlsx\n");

	XLDocument cf_status;
	cf_status.open("cf_status.xlsx");
	if (!cf_status.isOpen())
	{
		printf("PARSER ERROR: falied to open cf table\n");
		stop_models();
		return;
	}
	//============================================================================================================================================

	std::unordered_set<int> members_on_stream;

	printf("Now parsing table...\n");

	//base package info
	std::string member;
	std::string task;
	std::string contest;
	std::string task_status;

	int member_id;
	int task_id;
	int contest_id;
	bool is_new_task = false; //true when package contains correct solution of unique task

	//date package info
	long long date_unix;
	Date date;
	Date last_date_task;

	//stream info
	bool is_stream = false;
	long long stream_start_time_unix;
	int stream_task_id;

	OpenXLSX::XLWorksheet wbs = cf_status.workbook().worksheet("Status");
	int len = wbs.rowCount();

	for (int i = 2; i <= len; ++i)
	{
		float inf = float(i) / float(len);
		printf("%f of 1\n", inf);

		is_new_task = false; 

		member      = wbs.cell(i, 3).value().getString();
		contest     = wbs.cell(i, 9).value().getString();
		task        = wbs.cell(i, 4).value().getString();

		task = (contest + " " + task); //contest num _ task

		task_status = wbs.cell(i, 6).value().getString();
		
		update_db_models(member, contest, task);

		member_id = member_db.get_data_id(member);
		task_id = member_tasks_db.get_data_id(task);
		contest_id = member_contests_db.get_data_id(contest);

		date_unix = wbs.cell(i, 2).value().get<long long>();
		date = Date(date_unix);
		last_date_task = Date(member_stats.get_value(member_id, "last_task_date"));
		
		//HANDLE STREAMER

		if (member == "WhiteSun97")
		{
			//streamer
			if (!is_stream)
			{
				stream_start_time_unix = date_unix;
				is_stream = true;
			}

			stream_task_id = task_id;
		}

		//HANDLE STREAM END
		
		if (is_stream)
		{
			if (date_unix - stream_start_time_unix > 10800 or i == len) //3h or last package in cf_status
			{
				is_stream = false;
			}
			else
			{
				if (stream_task_id == task_id)
				{
					//member on stream
					if (members_on_stream.find(member_id) == members_on_stream.end())
					{
						members_on_stream.insert(member_id);
						member_stats.set_value(member_id, "total_stream", member_stats.get_value(member_id, "total_stream") + 1);
					}
				}
			}
		}

		if (!is_stream)
		{
			members_on_stream.clear();
		}

		//HANDLE STATUSES OF TASKS

		if (task_status == "WRONG_ANSWER")
		{
			handle_wa_status(member_id);
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

				handle_contests_stats(member_id, contest);

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


		//HANDLE DATE N TIME OF PACKAGES
		//-------------------------------------------------------------------------------------------------------------------------------------------
		
		int day_diff = Date::days(date, last_date_task);

		if (day_diff >= 1)
		{
			//new day

			handle_new_day(member_id,day_diff);

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

			if (task_status == "WRONG_ANSWER")
			{
				member_stats.set_value(member_id, "day_wa",1);
			}
		}

		member_stats.set_value(member_id, "last_task_date", date_unix);

		//============================================================================================================================================
	}

	cf_status.close();

	stop_models();
}
