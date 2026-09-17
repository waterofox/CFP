#pragma once

#include <SFML/Graphics/Color.hpp>

#include <unordered_set>
#include <unordered_map>

#include "DB_Model.h"

using namespace OpenXLSX;

class Member_Achievements_Model : public DB_Model
{
	
public:

	std::string get_name(const int& id);
	std::string get_condition(const int& id);
	sf::Color get_color(const int& id);

	Member_Achievements_Model();
	~Member_Achievements_Model() = default;
	
};

