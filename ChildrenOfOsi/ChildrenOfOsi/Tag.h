#pragma once
#include "common.h"
#include "ConversationPoint.h"
class Tag
{
public:
	std::vector<ConversationPoint*> tagPointer;
	Relationship* multipliers;
	Tag();
	~Tag();
};

