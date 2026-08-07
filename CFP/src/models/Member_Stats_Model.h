#pragma once

#include "Member_Achievements_Model.h"

using namespace OpenXLSX;

class Member_Stats_Model : public Model
{

	std::unordered_map<std::string, unsigned short> members;
	std::unordered_map<std::string, unsigned short> stats;
	std::unordered_map<unsigned short, std::unordered_map<unsigned short, unsigned int>> members_stats;

	void sync_table() override;

public:

	bool add_member(const std::string& member_name);
	
	bool is_member_exsits(const std::string& member_name);

	int unsigned& get_value(const std::string& member_name, const std::string stat_name);
	void set_value(const std::string& member_name, const std::string stat_name, int unsigned const& value);

	Member_Stats_Model();
	~Member_Stats_Model() = default;
};

