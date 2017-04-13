#pragma once
#include "common.h"
#include "Conditions.h"
class ConversationLogObj
{
private:
	int who;
	ConversationPoint* conv_point;
	std::pair<int, Memory*> topic;
	int number_of_times_said;

public:
	ConversationLogObj();
	~ConversationLogObj();

	int get_who();
	ConversationPoint* get_conv_point();
	std::pair<int, Memory*> get_topic();
	int get_number_of_times_said();

	void set_who(int val);
	void set_conv_point(ConversationPoint* con_point);
	void set_topic(int person, Memory* mem);
	void update_number_of_times_said();


};

