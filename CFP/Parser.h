#pragma once

#include "src/models/db/Member_Achievements_Model.h"
#include "src/models/db/Member_Contest_Model.h"
#include "src/models/db/Member_Tasks_Model.h"
#include "src/models/db/Member_Model.h"

#include "src/models/Member_Stats_Model.h";

class Parser
{
	//base for checking contests
	std::unordered_set<std::string> structs_contests = { "570478","573635","604876" };
	std::unordered_set<std::string> math_contests = { "568747","592220","596277","603194" };
	std::unordered_set<std::string> dp_contests = { "580161","582016","598187","599925" };
	std::unordered_set<std::string> base_cpp_contests = { "550879","552380","555156","557609","559129","561317" };
	std::unordered_set<std::string> graphs_contests = { "585202","586871","588471","590577","601495","606492" };
	std::unordered_set<std::string> base_algo_contests = { "563482","565018","567104","572133","574668","583445","607871" };

//---------------------------------------------------------------
	//MODELS DB
	Member_Achievements_Model member_achivments_db;
	Member_Contest_Model member_contests_db;
	Member_Tasks_Model member_tasks_db;
	Member_Model member_db;

	//MODELS
	Member_Stats_Model	      member_stats;
	
	bool start_models();
	void stop_models();
//---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
	void update_db_models(const std::string& member, const std::string& contest, const std::string& task);
//------------------------------------------------------------------------------------------------------------
	//LOGIC

	//STATUSES
	void handle_wa_status(const int& member_id);
	void handle_ok_status(const int& member_id,const int& constest_id, const int& task_id);

	//STATS
	void handle_contests_stats(const int& member_id,const std::string& contest);
	void handle_new_day(const int& member_id,const int& day_diff);
public:
	void start();

	Parser() = default;
	~Parser() = default;
};

