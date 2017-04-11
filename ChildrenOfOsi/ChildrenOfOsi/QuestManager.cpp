#include "stdafx.h"
#include "QuestManager.h"


QuestManager::QuestManager()
{
	fpm = 3600;
	frame_count = 0;
}


QuestManager::~QuestManager()
{
}

void QuestManager::update() {
	frame_count++;
	if (frame_count%fpm==0) {
		for (auto it = heros.begin(); it != heros.end(); ++it) {
			(*it)->decrement_quest_time();
		}
		frame_count = 0;
	}
}