#pragma once
#include "common.h"
#include "ConversationPoint.h"
class Tag
{
public:
	std::vector<ConversationPoint*> tags;
	Relationship* multipliers;
	Tag();
	~Tag();
};

