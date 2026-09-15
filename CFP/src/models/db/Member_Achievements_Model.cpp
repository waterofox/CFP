#include "Member_Achievements_Model.h"

std::string Member_Achievements_Model::get_name(const int& id)
{
	return table.workbook().worksheet("db").cell(id, 1).value().getString();
}

std::string Member_Achievements_Model::get_condition(const int& id)
{
	return table.workbook().worksheet("db").cell(id, 2).value().getString();
}

Member_Achievements_Model::Member_Achievements_Model()
{
	table_path = "tables\\mems_achivments.xlsx";
}
