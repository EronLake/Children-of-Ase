#include "ConversationLogObj.h"
#include "ConversationPoint.h"

#include "stdafx.h"
#include "ConversationPoint.h"


ConversationLogObj::ConversationLogObj()
{
	who = 0;
	conv_point = nullptr;
	number_of_times_said = 0;
	Memory* mem = nullptr;
	topic = std::make_pair(0, mem);
}


ConversationLogObj::~ConversationLogObj()
{

}

int ConversationLogObj::get_who() {
	return who;
}

ConversationPoint* ConversationLogObj::get_conv_point() {
	return conv_point;
}

std::pair<int, Memory*> ConversationLogObj::get_topic() {
	return topic;
}

int ConversationLogObj::get_number_of_times_said() {
	return number_of_times_said;
}

void ConversationLogObj::set_who(int person) {
	who = person;
}

void ConversationLogObj::set_conv_point(ConversationPoint* con_point) {
	conv_point = con_point;

}

void ConversationLogObj::set_topic(int person, Memory* mem) {
	//doing this instead of using push_back() function in here because
	//I initialize the topic vector in the class constructor by
	//pushing back 0 and a nullptr
	topic.first = person;
	topic.second = mem;
}

void ConversationLogObj::update_number_of_times_said() {
	++number_of_times_said;
}



