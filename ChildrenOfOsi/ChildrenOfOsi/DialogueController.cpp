#include "stdafx.h"
#include "DialogueController.h"
#include "CheckClass.h"
#include "ConversationPoint.h"

Player* DialogueController::player;
WorldObj* DialogueController::other;
int DialogueController::state = 0;
//States:
//0 is no conversation
//1 is waiting for player input
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response
DialogueHelper DialogueController::dialogue;
std::vector<std::vector<dialogue_point>> DialogueController::options;
std::vector<dialogue_point> DialogueController::replyOptions;
std::string DialogueController::message;
int DialogueController::optionsIndex=0;
int DialogueController::select = 0;
std::string DialogueController::replyString;
bool DialogueController::accepted_quest = false;
bool DialogueController::prompted_quest = false;
AIController* DialogueController::ai = nullptr;
Action* DialogueController::quest = nullptr;

int DialogueController::scroll_control = 0;

DialogueController::DialogueController()
{
	
}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	options = dialogue.get_possible_conv_pts();
	state = 1;
}

void DialogueController::PlayerConversationPoint()
{
	state = 4;
	while (options[optionsIndex].size() == 0) {
		optionsIndex++;
		if (optionsIndex >= options.size()) {
			optionsIndex = 0;
		}
	}
	vector<std::string> print = getOptions();
	dialogue_point choice = options[optionsIndex][select + DialogueController::scroll_control];
	std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);
	message += player->getName() + ": " + conversation_pt_sentence;
	otherResponse(choice[1]);
}

void DialogueController::PlayerResponse()
{
	//DialogueController::scroll_control = 0;
	dialogue_point choice = replyOptions[select + DialogueController::scroll_control];
	if (prompted_quest)
	{
		if (select == 0)   // Player is accepting the quest
		{
			player->quest = quest;
			Planner* planner = ai->hero_planners[CheckClass::isHero(other)->name];
			planner->get_current_action()->executed = true;
			prompted_quest = false;
			accepted_quest = true;
		}
		else             // Player is denying the quest
		{

		}

	}
	std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);
	//draws reply
	message = player->getName()+": "+reply_pt_sentence +"\n\n";
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point line)
{
	dialogue_point point = dialogue.choose_conv_pt(line, optionsIndex);
	replyString = point[1];

	Hero* temp_hero = nullptr;
	if (other->getType() >= 2) {
		if (temp_hero = CheckClass::isHero(other))//added another equals was single equals before
		{
			perror("you cannot talk to this type of object");
		}
	}
	else {
		return;
	}

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[1], optionsIndex);
	vector<std::string> print = getReplyOptions();

	select = 0;
	state = 2; //had at 0 for testing a time
	DialogueController::scroll_control = 0;
}

void DialogueController::otherResponse(std::string info)
{
	dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex);

	state = 3;
	otherConversationPoint(line);
}

vector<std::string> DialogueController::getOptions()
{
	vector<std::string> tmp;
	
	for (int i = 0; i < options[optionsIndex].size(); i++) 
	{
		tmp.push_back(options[optionsIndex][i][1]);
	}
	return tmp;
}

vector<std::string> DialogueController::getReplyOptions()
{
	vector<std::string> tmp;
	for (int i = 0; i < replyOptions.size(); i++)
	{
			tmp.push_back(replyOptions[i][1]);
	}
	return tmp;
}

void DialogueController::setPlayer(Player* p)
{
	player = p;
	state = 0;
}

void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	other = n;
	if (n->getName() != "Yemoja")
		return;
	message = "You started talking to ";
	message += n->getName();
	if (playerTalk) {
		PlayerChoose();
	}
	else {
		state = 3;
		otherConversationPoint({"Greeting","Greeting" });
	}
}

WorldObj* DialogueController::getOther()
{
	return other;
}

int DialogueController::getState()
{
	return state;
}

void DialogueController::exitDialogue()
{
	other = nullptr;
	state=0;
	DialogueController::set_scroll_control(0);
}

DialogueHelper* DialogueController::getDialogueHelper()
{
	return &dialogue;
}

void DialogueController::offerQuest_hack_() {
	dialogue_point line;
	line = { {} ,{ "give_quest_hack" } };
	dialogue_point point = {  "", "give_quest_hack"  }; // = dialogue.choose_conv_pt(line, optionsIndex);
	replyString = "You Suck";

	point[1]="give_quest_hack";
	point[0] = "quest";

	Hero* temp_hero;
	if (other->getType() >= 2) {
		if (temp_hero = CheckClass::isHero(other))
		{
			perror("you cannot talk to this type of object");
		}
	}
	else {
		return;
	}

	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);
	message = other->getName() + ": " + con_pt_sentence;
	replyOptions = { {"quest_accept","quest_accept"},{"quest_deny","quest_deny"} };
	select = 0;
	state = 2; 
}

void DialogueController::set_scroll_control(int scroll_int) {
	scroll_control = scroll_int;
}

std::string DialogueController::convert_option_to_phrase(std::string opt) {
	dialogue_point dp;
	dialogue_point return_val_vec;
	dp.push_back("");
	dp.push_back(opt);
	return_val_vec = DialogueController::getDialogueHelper()->get_dialog("Shango", dp);
	return return_val_vec[0];
}