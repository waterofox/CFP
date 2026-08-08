#pragma once

#include "DB_Model.h"

using namespace OpenXLSX;

class Member_Contest_Model : public DB_Model
{
	std::unordered_map<std::string, unsigned short> contests;

public:

	void sync_table() override;
	
	void attended_contest(unsigned short const& contest, const std::string& member_name);

	bool is_contest_exsits(const std::string&);
	const std::unordered_set<unsigned short>& get_member_contets(const std::string& member_name);
	unsigned short get_contest(const std::string& task_name);
	unsigned short add_new_contest(const std::string& contest_name);

	Member_Contest_Model();
	~Member_Contest_Model() = default;
};

