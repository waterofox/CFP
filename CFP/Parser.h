#pragma once

#include "src/models/db/Member_Achievements_Model.h"
#include "src/models/Member_Stats_Model.h";

class Parser
{
	//MODELS
	Member_Achievements_Model member_achivments;
	Member_Stats_Model	      member_stats;

public:
	void start();

	Parser() = default;
	~Parser() = default;
};

