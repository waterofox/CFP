#pragma once
#include <unordered_map>
#include <string>

struct Member
{

};

class Parser
{
	std::unordered_map<unsigned short, std::string> ñontests_tbl;	
	std::unordered_map<std::string, Member> members_tbl;
};

