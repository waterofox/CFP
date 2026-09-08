#include "DB_Model.h"

void DB_Model::push_table()
{
	OpenXLSX::XLWorksheet wbs = table.workbook().worksheet("db");

	for (auto& element : data)
	{
		wbs.cell(element.second,1).value() = element.first;
	}
}

void DB_Model::sync_table()
{
	OpenXLSX::XLWorksheet wbs = table.workbook().worksheet("db");
	
	for (int i = 2; i <= wbs.rowCount(); ++i)
	{
		data.insert({wbs.cell(i,1).value().get<std::string>(),i});
	}
}

unsigned int const& DB_Model::get_data_id(const std::string& data)
{
	if (is_data_exsits(data))
	{
		return this->data[data];
	}
	else
	{
		std::cout << "DB MODEL WARNING: " << data << " does not exsit. 0 returned.\n";
		return 0;
	}
}

void DB_Model::add_data(const std::string& new_data)
{
	if (is_data_exsits(new_data)) { return; }
	OpenXLSX::XLWorksheet wbs = table.workbook().worksheet("db");
	data.insert({new_data,data.size()+2});
}

bool DB_Model::is_data_exsits(const std::string& member_name)
{
	if (data.find(member_name) != data.end())
	{
		return true;
	}

	return false;
}

std::unordered_map<std::string, unsigned int>& DB_Model::get_fulldata()
{
	return data;
}
