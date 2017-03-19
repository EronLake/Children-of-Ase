#pragma once
#include "common.h"
#include "ConversationPoint.h"
class Tag
{
public:
	Tag();
	Tag(std::vector<std::string> topicVec, std::string _name);
	~Tag();
	//std::vector<ConversationPoint*> tagPointer;
	Relationship* multipliers;
	void set_tags_helper(ConversationPoint* conPoint);
	std::string get_name();
	void set_name(std::string val);
private:
	std::vector<ConversationPoint*> pointVec;
	std::string name;
};

