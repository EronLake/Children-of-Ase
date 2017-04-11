#pragma once
#include "common.h"
#include "Player.h"

class QuestManager
{
public:
	QuestManager();
	~QuestManager();
	vector<Hero*> heros;
	void set_fpm(int f) { fpm = f; };

	void update();
private:
	int fpm;
	int frame_count;
};

