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
	void load_members_info();
	void push_members_info();

	void push_table() override;
	void sync_table() override;
public:
	std::unordered_map<unsigned int, member_info> members;
	void add_member(const std::string& member);

	Member_Model();
	~Member_Model() = default;
};

