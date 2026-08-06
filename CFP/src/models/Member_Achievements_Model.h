#pragma once

#include <unordered_set>
#include <unordered_map>

#include "Model.h"

using namespace OpenXLSX;

class Member_Achievements_Model : public Model
{
	std::unordered_map<std::string, unsigned short> members;
	std::unordered_map<unsigned short, std::unordered_set<unsigned short>> members_achivments;

	void sync_table() override;
public:

	bool add_member(const std::string& member_name);
	unsigned short get_member(const std::string& member_name);
	void give_achivment(unsigned short const& achiment,const std::string& member_name);

	const std::unordered_set<unsigned short>& get_member_achivments(const std::string& member_name);
	bool is_member_exits(const std::string& member_name);

	Member_Achievements_Model();
	~Member_Achievements_Model() = default;
	
};

