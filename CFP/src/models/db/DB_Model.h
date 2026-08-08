#pragma once

#include "../Model.h"

#include <unordered_set>
#include <unordered_map>

using namespace OpenXLSX;

class DB_Model : public Model
{
protected:
	std::unordered_map<std::string, unsigned short> members;
	std::unordered_map<unsigned short, std::unordered_set<unsigned short>> members_data;

	virtual void sync_table() override;

public:
	bool add_member(const std::string& member_name);
	unsigned short get_member(const std::string& member_name);
	
	bool is_member_exits(const std::string& member_name);

	DB_Model() = default;
	~DB_Model() = default;

};

