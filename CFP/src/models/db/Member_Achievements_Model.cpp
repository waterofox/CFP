#include "Member_Achievements_Model.h"

std::string Member_Achievements_Model::get_name(const int& id)
{
	return table.workbook().worksheet("db").cell(id, 1).value().getString();
}

std::string Member_Achievements_Model::get_condition(const int& id)
{
	return table.workbook().worksheet("db").cell(id, 2).value().getString();
}

sf::Color Member_Achievements_Model::get_color(const int& id)
{
	int r, g, b;
	auto wbs = table.workbook().worksheet("db");
	r = wbs.cell(id, 3).value().get<int>();
	g = wbs.cell(id, 4).value().get<int>();
	b = wbs.cell(id, 5).value().get<int>();

	return sf::Color(r,g,b);
}

Member_Achievements_Model::Member_Achievements_Model()
{
	table_path = "tables\\mems_achivments.xlsx";
}
