#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "ConversationPoint.h"
#include "ConversationLogObj.h"
#include "Personality.h"


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
	dialogue_point choose_conv_pt(std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec, std::vector<int> personality, std::vector<int> relationship);
	dialogue_point choose_reply_pt(std::string point,int optn_inx);

	std::vector<std::vector<dialogue_point>> get_possible_conv_pts();
	std::vector<dialogue_point> get_possible_reply_pts(std::string point, int opts_inx);

	std::string gen_dialog(dialogue_point diog_pt, Hero* hero, int relationship_int, int relationship_int_shango);
	std::string gen_reply(dialogue_point diog_pt, Hero* hero, int relationship_int, int relationship_int_shango);

	dialogue_template get_template(dialogue_point diog_pt);
	dialogue_point get_dialog(std::string name, dialogue_point diog_pt, int relationship_int, int shango_phrase_picker);
	std::string convert_to_sentence(dialogue_point dialog_pt);
	void fill_conversations();
	int personality_appeal(ConversationPoint* point, vector<int> personality);

};


