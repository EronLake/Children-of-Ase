#include "stdafx.h"
#include "ConversationPoint.h"


ConversationPoint::ConversationPoint()
{
}


ConversationPoint::~ConversationPoint()
{
	delete multipliers;
	delete rel_multipliers;
}

void ConversationPoint::setMultipliers(int a, int k, int h, int p, int r, int e, int g) {
	multipliers = new Personality();
	multipliers->setAggression(a);
	multipliers->setKindness(k);
	multipliers->setHonor(h);
	multipliers->setPride(p);
	multipliers->setRecklessness(r);
	multipliers->setExtroversion(e);
	multipliers->setGreed(g);
};

std::string ConversationPoint::get_icon() {
	return icon;
}

std::string ConversationPoint::get_temp() {
	return temp;
}

std::string ConversationPoint::get_name() {
	return my_name;
}

std::string ConversationPoint::get_topic() {
	return topic;
}

void ConversationPoint::set_icon(std::string val) {
	icon = val;
}

void ConversationPoint::set_temp(std::string val) {
	temp = val;
}

void ConversationPoint::set_name(std::string val) {
	my_name = val;
}

void ConversationPoint::set_topic(std::string val) {
	topic = val;
}



