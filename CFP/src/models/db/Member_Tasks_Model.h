#pragma once

#include "DB_Model.h"

class Member_Tasks_Model : public DB_Model
{
	
	std::unordered_map<std::string, unsigned short> tasks;

public:

	void sync_table() override;

	void complete_solution(unsigned short const& task, const std::string& member_name);

	bool is_task_exsits(const std::string&);
	const std::unordered_set<unsigned short>& get_member_tasks(const std::string& member_name);
	unsigned short get_task(const std::string& task_name);
	unsigned short add_new_task(const std::string& task_name);

	Member_Tasks_Model();
	~Member_Tasks_Model() = default;
};

