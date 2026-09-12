#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "src/models/db/Member_Achievements_Model.h"
#include "src/models/db/Member_Contest_Model.h"
#include "src/models/db/Member_Tasks_Model.h"
#include "src/models/db/Member_Model.h"

#include "src/models/Member_Stats_Model.h";

#include <foxAndDot-SDK/Core.h>
#include <foxAndDot-SDK/Tools/Scene.h>

#include "src/comps/Achivment_Card.h"

#include <ctime>
#include <fstream>



class Parser
{
	//GRAPHICS BUILDING
public:
	class Event_Handler : public Executable
	{
		std::ifstream file;
		std::string name_buffer;
		std::string achiv;
		int achivs_count = 0;
		int i = 0;

		bool ready_for_save = false;
		bool started = true;
		int skip_frames = 1;

		
		void save(const bool&)
		{
			ready_for_save = true;
			skip_frames = 1;
		}
		Slot<bool, Event_Handler> save_slot;

		void operator()() override
		{
			std::time_t now = std::time(nullptr);
			std::tm* local = std::localtime(&now);
			
			if (ready_for_save)
			{

				if (skip_frames > 0)
				{
					--skip_frames; return;
				}

				sf::Texture texture(the_core.get_window().getSize());
				texture.update(the_core.get_window());
				texture.copyToImage().saveToFile("export\\pics\\" + card.member_name->getString().toAnsiString()\
					+ "_" + std::to_string(local->tm_mday) + "." + std::to_string(local->tm_mon + 1) + "." + std::to_string(local->tm_year + 1900) + "_"\
					+ card.achivment->getString().toAnsiString() + ".png");

				ready_for_save = false;
				return;

			}

			if (close_flag)
			{
				the_core.get_window().close();
			}

			if (achivs_count - i == 0)
			{
				file >> name_buffer;

				if (name_buffer == "***")
				{
					Core::the_core->get_window().close();
					return;
				}

				file >> achivs_count;
				file >> achiv;
				card.member_name->setString(name_buffer);
				card.achivment->setString(achiv);
				card.set_resource(std::stoi(achiv));
				i = 1;

				Core::the_core->emit(&Parser::Event_Handler::save_signal);

			}
			else
			{
				file >> achiv;
				card.achivment->setString(achiv);
				card.set_resource(std::stoi(achiv));
				++i;

				Core::the_core->emit(&Parser::Event_Handler::save_signal);

			}

		}

	public:

		static inline Signal<bool> save_signal;

		Event_Handler()
		{
			file.open("export\\temp\\new_achivments.txt");
			
			save_slot.reassign(&Event_Handler::save, this);
			connect(&save_signal, &save_slot);
		}
	};
private:
	
	Event_Handler evnt_handler;
	Scene scene;

	static inline Achivment_Card card;
	
	static inline bool close_flag = false;

	

	void init_scene();
public:
	static inline Core the_core;
	void init_core();
private:
	//base for checking contests
	std::unordered_set<std::string> structs_contests = { "570478","573635","604876" };
	std::unordered_set<std::string> math_contests = { "568747","592220","596277","603194" };
	std::unordered_set<std::string> dp_contests = { "580161","582016","598187","599925" };
	std::unordered_set<std::string> base_cpp_contests = { "550879","552380","555156","557609","559129","561317" };
	std::unordered_set<std::string> graphs_contests = { "585202","586871","588471","590577","601495","606492" };
	std::unordered_set<std::string> base_algo_contests = { "563482","565018","567104","572133","574668","583445","607871" };

//---------------------------------------------------------------
	//MODELS DB
	Member_Achievements_Model member_achivments_db;
	Member_Contest_Model member_contests_db;
	Member_Tasks_Model member_tasks_db;
	Member_Model member_db;

	//MODELS
	Member_Stats_Model	      member_stats;
	
	bool start_models();
	void stop_models();
//---------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
	void update_db_models(const std::string& member, const std::string& contest, const std::string& task);
//------------------------------------------------------------------------------------------------------------
	//LOGIC

	//STATUSES
	void handle_wa_status(const int& member_id);
	void handle_ok_status(const int& member_id,const int& constest_id, const int& task_id);

	//STATS
	void handle_contests_stats(const int& member_id,const std::string& contest);
	void handle_new_day(const int& member_id,const int& day_diff);
//----------------------------------------------------------------------------------------------------------
	//ACHIVMENTS
	void give_an_achivment(Member_Model::member_info& member_inf, const int& achivment_id);

	void check_correct_by_correct(const int& member_id, Member_Model::member_info& member_inf);
	void check_wa_by_wa(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_tasks(const int& member_id, Member_Model::member_info& member_inf);
	void check_day_tasks(const int& memebr_id, Member_Model::member_info& member_inf);
	void day_by_day_check(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_base_algo(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_graphs(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_math(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_basepp(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_dp(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_struct(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_contest(const int& member_id, Member_Model::member_info& member_inf);
	void check_total_streams(const int& member_id, Member_Model::member_info& member_inf);
	void check_holydays(const int& member_id, Member_Model::member_info& member_inf);
	void check_time(const int& member_id, Member_Model::member_info& memebr_inf);

	void check_achivments_post(const int& member_id,Member_Model::member_info& member_inf);
	

	void export_achivments();
public:
	void start();

	Parser();
	~Parser() = default;
};

