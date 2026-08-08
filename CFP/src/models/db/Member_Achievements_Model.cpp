#include "Member_Achievements_Model.h"




void Member_Achievements_Model::give_achivment(unsigned short const& achiment,const std::string& member_name)
{
	if (!is_started())
	{
		printf("MODEL ERROR: fialed to give an achivment");
		return;
	}

	if (!is_member_exits(member_name))
	{
		if (!add_member(member_name))
		{
			return;
		}
	}

	auto wbs = table.workbook().worksheet("db");
	
	wbs.cell(achiment, members[member_name]).value() = 1;
	members_data[members[member_name]].insert(achiment);
	
}

const std::unordered_set<unsigned short>& Member_Achievements_Model::get_member_achivments(const std::string& member_name)
{
	if (is_member_exits(member_name))
	{
		return members_data[members[member_name]];
	}
	printf("MODEL ERROR: member %s does not exsits", "member");
	//return std::unordered_set<unsigned short>();
}



Member_Achievements_Model::Member_Achievements_Model()
{
	table_path = "tables\\mems_achivments.xlsx";
}
