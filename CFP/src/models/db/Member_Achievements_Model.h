#pragma once

#include <unordered_set>
#include <unordered_map>

#include "DB_Model.h"

using namespace OpenXLSX;

class Member_Achievements_Model : public DB_Model
{
	std::unordered_map<unsigned short, std::unordered_set<unsigned short>> members_achivments;

	void sync_table() override;
public:

	void give_achivment(unsigned short const& achiment,const std::string& member_name);

	const std::unordered_set<unsigned short>& get_member_achivments(const std::string& member_name);

	Member_Achievements_Model();
	~Member_Achievements_Model() = default;
	
};

