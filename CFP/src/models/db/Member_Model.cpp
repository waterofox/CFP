#include "Member_Model.h"

#include <fstream>

void Member_Model::load_members_info()
{
	std::ifstream file;

	int tasks_count;
	int contests_count;
	int achivments_count;

	int tmp;

	for (auto& mem : data)
	{
		file.open("data\\" + mem.first + ".txt");
		if (!file.is_open())
		{
			std::ofstream("data\\" + mem.first + ".txt") << "0\n0\n0";
			file.open("data\\" + mem.first + ".txt");
		}
		
		file >> tasks_count;
		for (int i = 0; i < tasks_count; ++i)
		{
			file >> tmp;
			members[mem.second].tasks.insert(tmp);
		}

		file >> contests_count;
		for (int i = 0; i < contests_count; ++i)
		{
			file >> tmp;
			members[mem.second].contests.insert(tmp);
		}

		file >> achivments_count;
		for (int i = 0; i < achivments_count; ++i)
		{
			file >> tmp;
			members[mem.second].achivments.insert(tmp);
		}

		file.close();
	}
}

Member_Model::Member_Model()
{
	table_path = "tables\\mems.xlsx";
}
