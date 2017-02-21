#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"


typedef std::vector<std::string> dialogue_point;
typedef std::vector<std::string> dialogue_template;

class DialogueHelper
{
private:
	std::vector<std::vector<dialogue_point>> possible_conv_pts;
	std::vector<std::vector<dialogue_point>> possible_reply_pts;


public:
	DialogueHelper();
	~DialogueHelper();

	//functions where heroes make dialogue choices
	dialogue_point choose_conv_pt(dialogue_point point, int optn_inx);
	dialogue_point choose_reply_pt(std::string point,int optn_inx);
	std::vector<std::vector<dialogue_point>> get_possible_conv_pts();
	std::vector<std::vector<dialogue_point>> get_possible_reply_pts();

	std::string gen_dialog(dialogue_point diog_pt, Hero* hero);
	std::string gen_reply(dialogue_point diog_pt, Hero* hero);

	dialogue_template get_template(dialogue_point diog_pt);
	dialogue_point get_dialog(std::string name, dialogue_point diog_pt);
	std::string convert_to_sentence(dialogue_point dialog_pt);

};

