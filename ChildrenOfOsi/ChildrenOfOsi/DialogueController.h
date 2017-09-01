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
	static void DialogueController::add_to_perm_storage(ConversationLogObj* log_entry, Hero* temp_hero);
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

	//functions added during Summer 2017 for refactoring purposes
	static ConversationLogObj* DialogueController::create_conv_log_entry(dialogue_point dp, int person, ConversationPoint* conv_point);
	static void DialogueController::limit_log_size();
	static void DialogueController::set_accepted_action(Hero* h, dialogue_point dp);
	static void DialogueController::set_accepted_teaching(Hero* temp_hero);
	static void DialogueController::add_known_hero();
	static void DialogueController::start_event();
	static void DialogueController::set_response_reaction(dialogue_point dp, Hero* temp_hero);
	static void DialogueController::accept_quest(dialogue_point dp);
	static void DialogueController::skip_player_reply(dialogue_point point, dialogue_point line, std::string reply, std::string conv, Hero* h);
	static void DialogueController::format_quest_str(ConversationLogObj* conv_log_obj2, std::string& con_pt_sentence);
	static void DialogueController::finish_alliance(Hero* temp_hero);
	static void DialogueController::finish_duel();
	static void DialogueController::finish_spar();
	static void DialogueController::finish_fight_advice(Hero* h);
	static void DialogueController::finish_conquer_advice(Hero* temp_hero);
	static void DialogueController::finish_peace_advice();
	static void DialogueController::finish_ally_advice(Hero* temp_hero);
	static void DialogueController::finish_teach(Hero* temp_hero);
	static void DialogueController::finish_recruit(Hero* temp_hero, dialogue_point dp);
	static void DialogueController::resolve_talk_back(dialogue_point dp, Hero* temp_hero);
	static void DialogueController::resolve_plea(dialogue_point dp, Hero* temp_hero);
	static void DialogueController::resolve_congratulate(dialogue_point line, Hero* temp_hero);
	static void DialogueController::resolve_thank(dialogue_point line, Hero* temp_hero);
	static void DialogueController::resolve_defend(dialogue_point line, Hero* temp_hero);
	static void DialogueController::resolve_bribe(dialogue_point line, Hero* temp_hero);
	static void DialogueController::initiate_teach(Hero* temp_hero);
	static void DialogueController::initiate_ally_advice(Hero* temp_hero);
	static void DialogueController::initiate_peace(Hero* temp_hero);
	static void DialogueController::initiate_conquer(Hero* temp_hero);
	static void DialogueController::initiate_advice_fight(Hero* temp_hero);
	static void DialogueController::initiate_spar(Hero* temp_hero);
	static void DialogueController::initiate_duel(Hero* temp_hero);
	static void DialogueController::initiate_alliance(Hero* temp_hero);
	static void DialogueController::load_divination(std::string reply_pt_sentence, std::string  name_str);
	static void DialogueController::talk_non_hero();
	static void DialogueController::init_dialogue_options(Hero* h);
	static void DialogueController::start_greeting(Hero* temp_hero);
	static void DialogueController::initiate_quest_completion(bool quest_complete, bool player_doing_quest, Hero* temp_hero, Planner* planner);
	static void DialogueController::clear_conversation_logs(Hero* temp_hero);
	static void DialogueController::exit_non_hero();
	static void DialogueController::reset_conversation_vars();
	static void DialogueController::add_question_pts();
	static void DialogueController::add_notoriety_pts();
	static void DialogueController::remove_question_pts();
	static void DialogueController::remove_notoriety_pts();
	static void DialogueController::initiate_quest_offer(Hero* h);
	static bool DialogueController::check_down_cases(Hero*  temp_hero);
	static dialogue_point DialogueController::load_yemoja_lesson();
	static dialogue_point DialogueController::load_oya_lesson();
	static dialogue_point DialogueController::load_ogun_lesson();

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
	static int feedback_timer_2;
	static int feedback_timer_3;

	static int show_advice_feedback;

};

