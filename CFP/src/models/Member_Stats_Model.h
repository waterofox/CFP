#pragma once

#include "Model.h"

using namespace OpenXLSX;

class Member_Stats_Model : public Model
{

	//std::unordered_map<std::string, unsigned short> members;
	std::unordered_map<std::string, unsigned short> stats;
	std::unordered_map<unsigned int, std::unordered_map<unsigned short, unsigned int>> members_stats;

	void sync_table() override;
	void push_table() override;

public:

	void add_member(unsigned int const& member_id,const std::string& name);
	
	bool is_member_exsits(unsigned int const& member_id);

	int unsigned& get_value(unsigned int const& member_id, const std::string& stat_name);
	void set_value(unsigned int const& member_id, const std::string& stat_name, unsigned int const& value);

	void copy_table();

	Member_Stats_Model();
	~Member_Stats_Model() = default;
};

