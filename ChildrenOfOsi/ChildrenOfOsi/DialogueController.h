#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "DialogueHelper.h"
#include "AIController.h"
#include "PlayerActExecFunctions.h"
#include "Party.h"

class DialogueController
{
public:
	DialogueController();
	~DialogueController();
	static void PlayerChoose();

	static void PlayerConversationPoint();
	static void PlayerResponse();
	static void otherConversationPoint(dialogue_point line);
	static void otherResponse(std::string info, std::string hero_topic);

	static vector<std::vector<std::string>> getOptions();
	static int getOSize() { return options.size(); };
	static vector<std::vector<std::string>> getReplyOptions();

	static std::string getMessage() { return message; };
	static void setOptionsIndex(int i) { optionsIndex = i; select = 0; };
	static int getOptionsIndex() { return optionsIndex; };
	static void setSelect(int i) { select = i; };
	static int getSelect() { return select; };
	static void setPlayer(Player* p);
	static void startConversation(WorldObj* n, bool playerTalk);
	static WorldObj* getOther();
	static int getState();
	static void exitDialogue();
	

	static DialogueHelper* getDialogueHelper();
	static void add_hero_related_conv_points();
	static void remove_hero_related_conv_points();
	static void replace_all(std::string& str, const std::string& from, const std::string& to);
	static bool offer_quest_on_exit(Hero* hero);
	static void DialogueController::create_farewell();
	static void player_choose_soldier();
	static void player_choose_babalawo();
	static void shrine_interact();
	static void babalawo_interact();
	static void villager_interact();
	static void player_conversation_point_soldier();
	static void player_conversation_point_babalawo();
	static void other_response_soldier(std::string info, std::string hero_topic);
	static void other_response_babalawo(std::string info, std::string hero_topic);
	static void other_conversation_point_soldier(dialogue_point line);
	static vector<std::vector<std::string>> get_soldier_options();
	static vector<std::vector<std::string>> get_babalawo_options();
	static void DialogueController::remove_soldier_opts();
	static void DialogueController::remove_babalawo_opts();
	static void DialogueController::add_to_perm_storage(ConversationLogObj* log_entry);
	static void DialogueController::move_to_selectable_down();
	static void DialogueController::move_to_selectable_up();
	static void DialogueController::set_selectable(bool is_selectable, std::string option_name, int icon);
	static void DialogueController::add_dialog_option(std::string option_name, int icon);
	static void DialogueController::remove_dialog_option(std::string option_name, int icon);
	static bool DialogueController::check_advice_acceptance(Player* p, Hero* npc);
	static void DialogueController::load_teach_dialog();
	static void DialogueController::duel_pop_up(Action* act);
	static void DialogueController::spar_pop_up(Action* act);
	static void DialogueController::hero_act_alliance_pop_up(Action* act);
	static void DialogueController::hero_act_bribe_pop_up(Action* act);
	static void DialogueController::hero_act_compliment_pop_up(Action* act);
	static void DialogueController::hero_act_boast_pop_up(Action* act);
	static void DialogueController::hero_act_grovel_pop_up(Action* act);
	static void DialogueController::hero_act_intimidate_pop_up(Action* act);
	static std::string DialogueController::check_if_known(std::string rep_pt_str, std::string con_pt_str);
	static void DialogueController::apply_post_from_response(std::string rep_choice, Action* act);
	static bool DialogueController::check_acceptance(Player* p, Hero* npc);
	static void DialogueController::unselectable_to_bottom();


	static bool prompted_quest;
	static bool accepted_quest;
	
	//used for hero actions
	static bool accepted_action;

	static Action* quest;
	static int scroll_control;

	static Player* player;
	static WorldObj* other;
	static int state;
	static std::string replyString;
	static bool quest_declined;
	static bool react_positively;

	static ConversationLogObj* entry;
	static std::pair<bool, std::string> vis_feedback;

	//States:
	//0 is no conversation
	//1 is waiting for player input
	//2 is waiting for player response
	//3 is npc conversation point
	//4 is npc response

	static DialogueHelper dialogue;

	static std::vector<std::vector<dialogue_point>> options;
	static std::vector<std::vector<dialogue_point>> soldier_options;
	static std::vector<std::vector<dialogue_point>> babalawo_options;
	static std::vector<dialogue_point> replyOptions;
	static std::string message;
	static int optionsIndex;
	static int select;
	//static std::vector<int> heroes_player_knows;
	static std::vector<ConversationLogObj*> curr_conversation_log;
	static bool started_conv;
	static bool quited_gui;
	static bool first_q_press;
	static bool took_advice;
	static int shrine_talk_counter;
	static int teach_move_counter;
	static bool first_buff;
	static bool is_hero_act;
	static Action* hero_act_toward_player;

	//to keep you from repeatedly talking to shrines 
	static bool talked_to_shrine_o;
	static bool talked_to_shrine_j;
	static bool talked_to_shrine_m;

	//to keep you from repeatedly getting divination from babalawos
	static bool talked_to_babalawo_o;
	static bool talked_to_babalawo_j;
	static bool talked_to_babalawo_m;

	static int feedback_timer;

};

