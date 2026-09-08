#pragma once

#include "../Model.h"

#include <unordered_set>
#include <unordered_map>

using namespace OpenXLSX;

class DB_Model : public Model
{
protected:
	std::unordered_map<std::string, unsigned int> data;
	virtual void push_table() override;
	virtual void sync_table() override;
	
public:
	
	
	unsigned int const& get_data_id(const std::string& data);
	void add_data(const std::string& new_data);
	bool is_data_exsits(const std::string& member_name);
	
	std::unordered_map<std::string, unsigned int>& get_fulldata();

	DB_Model() = default;
	~DB_Model() = default;

};

