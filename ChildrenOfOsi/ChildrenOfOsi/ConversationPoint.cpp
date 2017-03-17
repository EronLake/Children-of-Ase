#include "stdafx.h"
#include "ConversationPoint.h"


ConversationPoint::ConversationPoint()
{
}


ConversationPoint::~ConversationPoint()
{
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
