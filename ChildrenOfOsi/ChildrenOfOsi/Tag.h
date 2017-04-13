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
	Relationship* relationship_multipliers;
	void set_tags_helper(ConversationPoint* conPoint);
	std::string get_name();
	void set_name(std::string val);
	std::vector<ConversationPoint*> conversation_point_pointer_vec;
	std::vector<ConversationPoint*> get_conversation_pointer_vec();
	
private:
	std::string name;
	
};

