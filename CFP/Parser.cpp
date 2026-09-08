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

void Parser::give_an_achivment(Member_Model::member_info& member_inf, const int& achivment_id)
{
	std::unordered_set<unsigned int>& achivms = member_inf.achivments;
	if (achivms.find(achivment_id) == achivms.end())
	{
		achivms.insert(achivment_id);
		member_inf.new_achs.insert(achivment_id);
	}
}

void Parser::check_correct_by_correct(const int& member_id, Member_Model::member_info& member_inf)
{
	int cbc = member_stats.get_value(member_id, "correct_by_correct");
	if (cbc >= 5)
	{
		give_an_achivment(member_inf,3);
	}
	if (cbc >= 10)
	{
		give_an_achivment(member_inf, 11);
	}
	if (cbc >= 21)
	{
		give_an_achivment(member_inf, 2);
	}
}

void Parser::check_wa_by_wa(const int& member_id, Member_Model::member_info& member_inf)
{
	int wa_by_wa = member_stats.get_value(member_id, "war_by_war");
	if (wa_by_wa >= 5)
	{
		give_an_achivment(member_inf, 8);
	}
}

void Parser::check_total_tasks(const int& member_id, Member_Model::member_info& member_inf)
{
	int total = member_stats.get_value(member_id, "total_tasks");
	if (total >= 1)
	{
		give_an_achivment(member_inf, 9);
	}
	if (total >= 5)
	{
		give_an_achivment(member_inf, 57);
	}
	if (total >= 10)
	{
		give_an_achivment(member_inf, 59);
	}
	if (total >= 25)
	{
		give_an_achivment(member_inf, 61);
	}
	if (total >= 50)
	{
		give_an_achivment(member_inf, 58);
	}
	if (total >= 100)
	{
		give_an_achivment(member_inf, 53);
	}
	if (total >= 500)
	{
		give_an_achivment(member_inf, 54);
	}
	if (total >= 300)
	{
		give_an_achivment(member_inf, 55);
	}
	if (total >= 200)
	{
		give_an_achivment(member_inf, 56);
	}
	if (total >= 150)
	{
		give_an_achivment(member_inf, 62);
	}
	if (total >= 400)
	{
		give_an_achivment(member_inf, 60);
	}
}

void Parser::check_day_tasks(const int& member_id, Member_Model::member_info& member_inf)
{
	int day_tasks = member_stats.get_value(member_id, "day_tasks");
	if (day_tasks >= 3)
	{
		give_an_achivment(member_inf, 13);
	}
	if (day_tasks >= 5)
	{
		give_an_achivment(member_inf, 16);
	}
	if (day_tasks >= 7)
	{
		give_an_achivment(member_inf, 14);
	}
	if (day_tasks >= 9)
	{
		give_an_achivment(member_inf, 17);
	}
	if (day_tasks >= 11)
	{
		give_an_achivment(member_inf, 15);
	}
}

void Parser::day_by_day_check(const int& member_id, Member_Model::member_info& member_inf)
{
	int day_by_day = member_stats.get_value(member_id, "day_by_day");
	if (day_by_day >= 3)
	{
		give_an_achivment(member_inf, 18);
	}
	if (day_by_day >= 6)
	{
		give_an_achivment(member_inf, 19);

	}
	if (day_by_day >= 10)
	{
		give_an_achivment(member_inf, 20);

	}
	if (day_by_day >= 15)
	{
		give_an_achivment(member_inf, 21);

	}
	if (day_by_day >= 21)
	{
		give_an_achivment(member_inf, 22);

	}
	if (day_by_day >= 28)
	{
		give_an_achivment(member_inf, 23);

	}
}

void Parser::check_total_base_algo(const int& member_id, Member_Model::member_info& member_inf)
{
	int tba = member_stats.get_value(member_id, "total_base_algo");
	if (tba >= 5)
	{
		give_an_achivment(member_inf, 24);
	}
	if (tba >= 10)
	{
		give_an_achivment(member_inf, 25);

	}
	if (tba >= 25)
	{
		give_an_achivment(member_inf, 26);

	}
	if (tba >= 50)
	{
		give_an_achivment(member_inf, 27);

	}
}

void Parser::check_total_graphs(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_graphs");

	if (tmp >= 5)
	{
		give_an_achivment(member_inf, 28);
	}
	if (tmp >= 10)
	{
		give_an_achivment(member_inf, 29);
	}
	if (tmp >= 25)
	{
		give_an_achivment(member_inf, 30);
	}
	if (tmp >= 50)
	{
		give_an_achivment(member_inf, 31);
	}
}

void Parser::check_total_math(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_math");
	if (tmp >= 5)
	{
		give_an_achivment(member_inf, 32);
	}
	if (tmp >= 10)
	{
		give_an_achivment(member_inf, 33);
	}
	if (tmp >= 25)
	{
		give_an_achivment(member_inf, 34);
	}
	if (tmp >= 50)
	{
		give_an_achivment(member_inf, 35);
	}
}

void Parser::check_total_basepp(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_base++");
	if (tmp >= 5)
	{
		give_an_achivment(member_inf, 36);
	}
	if (tmp >= 10)
	{
		give_an_achivment(member_inf, 37);
	}
	if (tmp >= 25)
	{
		give_an_achivment(member_inf, 38);
	}
	if (tmp >= 50)
	{
		give_an_achivment(member_inf, 39);
	}
}

void Parser::check_total_dp(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_dp");
	if (tmp >= 5)
	{
		give_an_achivment(member_inf, 40);
	}
	if (tmp >= 10)
	{
		give_an_achivment(member_inf, 41);
	}
	if (tmp >= 25)
	{
		give_an_achivment(member_inf, 42);
	}
	if (tmp >= 50)
	{
		give_an_achivment(member_inf, 43);
	}
}

void Parser::check_total_struct(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_struct");
	if (tmp >= 5)
	{
		give_an_achivment(member_inf, 44);
	}
	if (tmp >= 10)
	{
		give_an_achivment(member_inf, 45);
	}
	if (tmp >= 25)
	{
		give_an_achivment(member_inf, 46);
	}
	if (tmp >= 50)
	{
		give_an_achivment(member_inf, 47);
	}
}

void Parser::check_total_contest(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_contest");
	if (tmp >= 3)
	{
		give_an_achivment(member_inf, 51);
	}
	if (tmp >= 7)
	{
		give_an_achivment(member_inf, 50);
	}
	if (tmp >= 13)
	{
		give_an_achivment(member_inf, 49);
	}
	if (tmp >= 21)
	{
		give_an_achivment(member_inf, 52);
	}
	if (tmp >= 31)
	{
		give_an_achivment(member_inf, 48);
	}

}

void Parser::check_total_streams(const int& member_id, Member_Model::member_info& member_inf)
{
	int tmp = member_stats.get_value(member_id, "total_stream");
	if (tmp >= 5)
	{
		give_an_achivment(member_inf, 79);
	}
	if (tmp >= 10)
	{
		give_an_achivment(member_inf, 80);
	}
	if (tmp >= 20)
	{
		give_an_achivment(member_inf, 81);
	}
	if (tmp >= 3)
	{
		give_an_achivment(member_inf, 82);
	}
	if (tmp >= 15)
	{
		give_an_achivment(member_inf, 83);
	}
}

void Parser::check_holydays(const int& member_id, Member_Model::member_info& member_inf)
{
	Date date(member_stats.get_value(member_id, "last_task_date"));
	
	if (date.month == 10 and date.day == 4)
	{
		give_an_achivment(member_inf, 64);
		return;
	}
	else if (date.month == 5 and date.day == 9)
	{
		give_an_achivment(member_inf, 65);
		return;
	}
	else if (date.month == 6 and date.day == 12)
	{
		give_an_achivment(member_inf, 66);
		return;
	}
	else if (date.month == 2 and date.day == 23)
	{
		give_an_achivment(member_inf, 67);
		return;
	}
	else if (date.month == 5 and date.day == 1)
	{
		give_an_achivment(member_inf, 68);
		return;
	}
	else if (date.month == 2 and date.day == 14)
	{
		give_an_achivment(member_inf, 69);
		return;
	}
	else if ((date.month == 12 and date.day == 31) or\
		(date.month == 1 and date.day == 1))
	{
		give_an_achivment(member_inf, 70);
		return;
	}
	else if (date.month == 3 and date.day == 8)
	{
		give_an_achivment(member_inf, 71);
		return;
	}
	else if (date.month == 9 and date.day == 1)
	{
		give_an_achivment(member_inf, 72);
		return;
	}
	else if ((date.month == 10 and date.day == 31) or \
		(date.month == 11 and date.day == 1))
	{
		give_an_achivment(member_inf, 73);
		return;
	}
}

void Parser::check_time(const int& member_id, Member_Model::member_info& memebr_inf)
{
	Date tmp(member_stats.get_value(member_id, "last_task_date"));

	if (tmp.h >= 2 and tmp.h <= 5)
	{
		give_an_achivment(memebr_inf, 6);
	}
	
	if ((tmp.h == 5 and tmp.m >= 50) or (tmp.h == 6 and tmp.m <= 10))
	{
		give_an_achivment(memebr_inf, 5);
	}
	
}

void Parser::check_achivments_post(const int& member_id,Member_Model::member_info& member_inf)
{
	check_correct_by_correct(member_id,member_inf);
	check_wa_by_wa(member_id, member_inf);
	day_by_day_check(member_id, member_inf);

	check_day_tasks(member_id,member_inf);

	check_total_tasks(member_id, member_inf);
	check_total_base_algo(member_id, member_inf);
	check_total_graphs(member_id, member_inf);
	check_total_math(member_id, member_inf);
	check_total_basepp(member_id, member_inf);
	check_total_dp(member_id, member_inf);
	check_total_struct(member_id, member_inf);
	check_total_contest(member_id, member_inf);
	check_total_streams(member_id, member_inf);

	//STATUSES ACHIVMENT
	int tmp = member_stats.get_value(member_id, "ml") \
		+member_stats.get_value(member_id, "ce") \
		+member_stats.get_value(member_id, "tl") \
		+member_stats.get_value(member_id, "wa");
	if (tmp == 4)
	{
		give_an_achivment(member_inf, 63);
	}

	check_holydays(member_id, member_inf);
	check_time(member_id, member_inf);
 
}

void Parser::export_achivments()
{
	OpenXLSX::XLDocument doc;
	doc.create("export\\achivments_for_masloy.xlsx",true);
	
	if (!doc.isOpen())
	{
		doc.open("export\\achivments_for_masloy.xlsx");
	}

	auto wbs = doc.workbook().worksheet("Sheet1");

	auto& achivs = member_achivments_db.get_fulldata();
	for (auto& el : achivs)
	{
		wbs.cell(1, el.second).value() = el.first;
	}
	auto& mems = member_db.get_fulldata();
	for (auto& el : mems)
	{
		wbs.cell(el.second, 1).value() = el.first;
		
		auto& member_info = member_db.members[el.second];
		for (auto& ach : member_info.achivments)
		{
			wbs.cell(el.second, ach).value() = 1;
		}

	}
	
	doc.save();
	doc.close();


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

		auto& member_info = member_db.members[member_id];

		
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

					if (task_status == "OK")
					{
						give_an_achivment(member_info, 10);
					}
				}
				else
				{
					give_an_achivment(member_info, 7);
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
			if (member_info.tasks.find(task_id) == member_info.tasks.end())
			{
				//first correcet solution of task

				if (task_id == 261)
				{
					give_an_achivment(member_info, 75);
				}
				else if (task_id == 150)
				{
					give_an_achivment(member_info, 74);
				}
				else if (task_id == 174 or task_id ==  175 or task_id == 189)
				{
					give_an_achivment(member_info, 76);
				}
				else if (task_id == 88)
				{
					give_an_achivment(member_info, 74);
				}

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

			if (day_diff >= 30)
			{
				give_an_achivment(member_info, 4);
			}

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
		//ACHIVMENTS
		check_achivments_post(member_id, member_info);
	}

	cf_status.close();

	export_achivments();

	stop_models();
}
