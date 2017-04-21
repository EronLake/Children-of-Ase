#pragma once
#include "common.h"
#include "Conditions.h"
class ConversationPoint
{
public:
	ConversationPoint();
	~ConversationPoint();
	void setMultipliers(int a, int k, int h, int p, int r, int e, int g);
	Personality* multipliers;
	Relationship* rel_multipliers;
	typedef std::vector<std::string> dialogue_point;
	dialogue_point dpoint;
	std::vector<Tag*> tag_pointer_vec;
	std::unordered_map<std::string, std::shared_ptr<Postcondition>> succ_postconds;
	std::unordered_map<std::string, std::shared_ptr<Postcondition>> fail_postconds;

	std::string get_icon();
	std::string get_temp();
	std::string get_name();
	std::string get_topic();
	void set_icon(std::string val);
	void set_temp(std::string val);
	void set_name(std::string val);
	void set_topic(std::string val);
private:
	std::string icon;
	std::string temp;
	std::string my_name;
	std::string topic;
	
};

