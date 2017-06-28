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
	std::vector<Tag*> tag;

	vector<std::shared_ptr<Preconditions>> req_preconds;
	vector<vector<std::shared_ptr<Preconditions>>> op_preconds;

	vector<std::shared_ptr<Postcondition>> doer_succ_postconds;
	vector<std::shared_ptr<Postcondition>> doer_fail_postconds;

	vector<std::shared_ptr<Postcondition>> receiver_succ_postconds;
	vector<std::shared_ptr<Postcondition>> receiver_fail_postconds;

	void apply_postconditions(bool ifsucc, Hero* doer, Hero* receiver);

	std::string get_icon();
	std::string get_temp();
	std::string get_name();
	std::string get_topic();
	std::string get_is_selectable();
	Action* get_action();
	void set_icon(std::string val);
	void set_temp(std::string val);
	void set_name(std::string val);
	void set_topic(std::string val);
	void set_is_selectable(std::string val);
	void set_action(Action* act);
private:
	std::string icon;
	std::string temp;
	std::string my_name;
	std::string topic;
	std::string is_selectable;
	Action* act;
	
};

