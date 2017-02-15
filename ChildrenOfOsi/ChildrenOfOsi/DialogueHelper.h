#pragma once
#include "common.h"

typedef std::vector<std::string> dialogue_point;

class DialogueHelper
{
private:
	std::vector<dialogue_point> possible_conv_pts;
	std::vector<dialogue_point> possible_reply_pts;



public:
	DialogueHelper();
	~DialogueHelper();

	//functions where heroes make dialogue choices
	dialogue_point choose_conv_pt(dialogue_point);
	dialogue_point choose_reply(dialogue_point);
	//std::vector<dialogue_point> get_possible_conv_pts()
};

