#include "Member_Model.h"

#include <fstream>

void Member_Model::load_members_info()
{
	std::ifstream file;

	int tasks_count;
	int contests_count;
	int achivments_count;

	int tmp;

	printf("loading members data...\n");

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

void Member_Model::push_members_info()
{
	std::ofstream file;

	printf("saving members data...\n");

	for (auto& mem : data)
	{
		auto& member = members[mem.second];

		file.open("data\\" + mem.first + ".txt",std::ios_base::out);

		file << member.tasks.size() << ' ';
		for (auto& el : member.tasks)
		{
			file << el << ' ';
		}
		file << '\n';

		file << member.contests.size() << ' ';
		for (auto& el : member.contests)
		{
			file << el << ' ';
		}
		file << '\n';

		file << member.achivments.size() << ' ';
		for (auto& el : member.achivments)
		{
			file << el << ' ';
		}
		file << '\n';


		file.close();
	}
}

void Member_Model::push_table()
{
	DB_Model::push_table();
	push_members_info();

}

void Member_Model::sync_table()
{
	DB_Model::sync_table();
	load_members_info();
}

void Member_Model::add_member(const std::string& member)
{
	this->add_data(member);
	std::ofstream("data\\" + member + ".txt") << "0\n0\n0";
}

Member_Model::Member_Model()
{
	table_path = "tables\\mems.xlsx";
}
