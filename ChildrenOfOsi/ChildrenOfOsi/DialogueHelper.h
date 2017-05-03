#pragma once
#include "common.h"
#include "Hero.h"
#include "json.h"
#include "ConversationPoint.h"
#include "ConversationLogObj.h"
#include "Personality.h"
#include "CheckClass.h"


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
	dialogue_point choose_conv_pt(std::vector<ConversationLogObj*> curr_conversation_log, Hero* other, Player* player);
	dialogue_point choose_reply_pt(std::string point,int optn_inx, std::vector<ConversationLogObj*> curr_conversation_log,Hero* other);

	std::vector<std::vector<dialogue_point>> get_possible_conv_pts();
	std::vector<dialogue_point> get_possible_reply_pts(std::string point, int opts_inx);
	std::vector<std::vector<dialogue_point>>& get_possible_conv_pts_ref();
	std::string gen_dialog(dialogue_point diog_pt, Hero* hero);
	std::string gen_reply(dialogue_point diog_pt, Hero* hero, int relationship_int, int relationship_int_shango);

	dialogue_template get_template(dialogue_point diog_pt);
	dialogue_point get_dialog(std::string name, dialogue_point diog_pt, Hero* hero);
	std::string DialogueHelper::gen_dialog_negative(dialogue_point diog_pt, Hero* hero);
	dialogue_point get_dialog_negative(std::string name, dialogue_point diog_pt, Hero* hero);
	std::string convert_to_sentence(dialogue_point dialog_pt);
	void fill_conversations();
	bool give_quest();
	int personality_appeal(ConversationPoint* point, Personality* personality);
	int hero_name_to_int(std::string hero);
	int calc_text_choice_from_relationship(Hero* hero, std::pair<int, Memory*> topic);
	std::string int_to_hero_name(int hero);

	static bool prompted_quest;
	static bool accepted_quest;

	static Action* quest;
};


