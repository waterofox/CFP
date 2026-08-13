#pragma once

#include "DB_Model.h"

class Member_Model : public DB_Model
{
	struct member_info
	{
		std::unordered_set<unsigned int> tasks;
		std::unordered_set<unsigned int> contests;
		std::unordered_set<unsigned int> achivments;
	};

	std::unordered_map<unsigned int, member_info> members;
	void load_members_info();

public:
	Member_Model();
	~Member_Model() = default;
};

