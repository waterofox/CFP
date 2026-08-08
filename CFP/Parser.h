#pragma once

#include "src/models/db/Member_Achievements_Model.h"
#include "src/models/db/Member_Contest_Model.h"
#include "src/models/db/Member_Tasks_Model.h"

#include "src/models/Member_Stats_Model.h";

class Parser
{
	//MODELS DB
	Member_Achievements_Model member_achivments_db;
	Member_Contest_Model member_contests_db;
	Member_Tasks_Model member_tasks_db;

	//MODELS
	Member_Stats_Model	      member_stats;

public:
	void start();

	Parser() = default;
	~Parser() = default;
};

