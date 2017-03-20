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
bool init_conv = false;
bool DialogueController::prompted_quest = false;
bool DialogueController::accepted_quest = false;
Action* DialogueController::quest = nullptr;
AIController* DialogueController::ai = nullptr;

DialogueController::DialogueController()
{

}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	options = dialogue.get_possible_conv_pts();
	//replyOptions = dialogue.get_possible_reply_pts();
	state = 1;
	if(!init_conv)
	    optionsIndex = 0; //had at 3 for testing at one point
	else
		optionsIndex = 3;
	//PlayerConversationPoint();
	//give option to Alex
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
	//std::////cout << "Shango Conversation Options:" << std::endl;
	for (int i = 0; i < print.size(); i++) {
		//std::////cout << print[i] << std::endl;
	}
	//std::////cout <<"Select: "<< select << endl;
	dialogue_point choice = options[optionsIndex][select];
	std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);
	message += player->getName() + ": " + conversation_pt_sentence;
	//std::////cout << "PLAYER COONVERSATION POINT////////////////////////////////////" << std::endl;
	//std::////cout << "Shango: " << conversation_pt_sentence << std::endl;
	otherResponse(choice[0]);
}

void DialogueController::PlayerResponse()
{
	//std::////cout << "Select: " << select << endl;
	dialogue_point choice = replyOptions[select];

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
	//std::////cout << "PLAYER RESPONSE////////////////////////////////////" << std::endl;
	//std::////cout << "Shango: " << getMessage() << std::endl;
	init_conv = true;
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point line)
{

	dialogue_point point = dialogue.choose_conv_pt(line, optionsIndex);
	replyString = point[0];

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

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);
	//std::////cout << "------------REPLY:"<<reply_pt_sentence << std::endl;
	//give options to Alex
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	//std::////cout << "HERO REPLY/COONVERSATION POINT////////////////////////////////////" << std::endl;
	//std::////cout << other->getName() << ": "<< message << std::endl;
	replyOptions = dialogue.get_possible_reply_pts(point[0]);
	vector<std::string> print = getReplyOptions();
	for (int i = 0; i < print.size(); i++) {
		//std::////cout << print[i] << std::endl;
	}
	select = 0;
	state = 2; //had at 0 for testing a time
	//optionsIndex = 3;
	//getOptions();
	//give info to Alex
	//PlayerResponse();
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
		tmp.push_back(options[optionsIndex][i][0]);
	}

	return tmp;
	//give tmp to Alex
}

vector<std::string> DialogueController::getReplyOptions()
{
	vector<std::string> tmp;

	for (int i = 0; i < replyOptions.size(); i++)
	{
		/*if (replyOptions[optionsIndex][i][0].compare(replyString)==0 ||
			replyOptions[optionsIndex][i][0].compare("denied")==0)
		{*/
			tmp.push_back(replyOptions[i][1]);
		
	}

	return tmp;
	//give tmp to Alex
}

void DialogueController::setPlayer(Player* p)
{
	player = p;
	state = 0;
}

void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	//std::////cout << player->getName() << " talked with " << n->getName() << std::endl;
	other = n;
	message = "You started talking to ";
	message += n->getName();
	if (playerTalk) {
		PlayerChoose();
	}
	else {
		state = 3;
		otherConversationPoint({"greeting","greeting" });
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
	if (optionsIndex == 3)
		init_conv = true;
	else
	    init_conv = false;
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
//bool init_conv = false;

DialogueController::DialogueController()
{

}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	//if (optionsIndex > 3 || optionsIndex < 0)
		//optionsIndex = 0;
	//if(optionsIndex == 0)
	  //  options = dialogue.get_strength_conv_pts(); //get_possible
	//else if (optionsIndex == 1) {
		//options = dialogue.get_affinity_conv_pts();
	//}
	//else if(optionsIndex == 2){
		//options = dialogue.get_notoriety_conv_pts();
	//}
	//else
	options = dialogue.get_possible_conv_pts();
	//replyOptions = dialogue.get_possible_reply_pts();
	state = 1;
	//optionsIndex = 0;
	//if(!init_conv)
	   // optionsIndex = 0; //had at 3 for testing at one point
	//else
		//optionsIndex = 3;
	//PlayerConversationPoint();
	//give option to Alex
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
	//std::////cout << "Shango Conversation Options:" << std::endl;
	for (int i = 0; i < print.size(); i++) {
		//std::////cout << print[i] << std::endl;
	}
	//std::////cout <<"Select: "<< select << endl;
	dialogue_point choice = options[optionsIndex][select];
	std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);
	message += player->getName() + ": " + conversation_pt_sentence;
	//std::////cout << "PLAYER COONVERSATION POINT////////////////////////////////////" << std::endl;
	//std::////cout << "Shango: " << conversation_pt_sentence << std::endl;
	otherResponse(choice[0]);
}

void DialogueController::PlayerResponse()
{
	//std::////cout << "Select: " << select << endl;
	dialogue_point choice = replyOptions[select];

	std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);
	//draws reply
	message = player->getName()+": "+reply_pt_sentence +"\n\n";
	//std::////cout << "PLAYER RESPONSE////////////////////////////////////" << std::endl;
	//std::////cout << "Shango: " << getMessage() << std::endl;
	//init_conv = true;
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point line)
{
	dialogue_point point = dialogue.choose_conv_pt(line, optionsIndex);
	replyString = point[0];

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
	//std::////cout << "------------REPLY:"<<reply_pt_sentence << std::endl;
	//give options to Alex
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	//std::////cout << "HERO REPLY/COONVERSATION POINT////////////////////////////////////" << std::endl;
	//std::////cout << other->getName() << ": "<< message << std::endl;
	/*if(optionsIndex == 0)
	    replyOptions = dialogue.get_strength_reply_pts(point[0]);
	else if (optionsIndex == 1)
		replyOptions = dialogue.get_affinity_reply_pts(point[0]);
	else if (optionsIndex == 2)
		replyOptions = dialogue.get_notoriety_reply_pts(point[0]);
	else*/
		replyOptions = dialogue.get_possible_reply_pts(point[0], optionsIndex);
	vector<std::string> print = getReplyOptions();
	for (int i = 0; i < print.size(); i++) {
		//std::////cout << print[i] << std::endl;
	}
	select = 0;
	state = 2; //had at 0 for testing a time
	//optionsIndex = 3;
	//getOptions();
	//give info to Alex
	//PlayerResponse();
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
		tmp.push_back(options[optionsIndex][i][0]);
	}

	return tmp;
	//give tmp to Alex
}

vector<std::string> DialogueController::getReplyOptions()
{
	vector<std::string> tmp;

	for (int i = 0; i < replyOptions.size(); i++)
	{
		/*if (replyOptions[optionsIndex][i][0].compare(replyString)==0 ||
			replyOptions[optionsIndex][i][0].compare("denied")==0)
		{*/
			tmp.push_back(replyOptions[i][1]);
		
	}

	return tmp;
	//give tmp to Alex
}

void DialogueController::setPlayer(Player* p)
{
	player = p;
	state = 0;
}

void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	//std::////cout << player->getName() << " talked with " << n->getName() << std::endl;
	other = n;
	message = "You started talking to ";
	message += n->getName();
	if (playerTalk) {
		PlayerChoose();
	}
	else {
		state = 3;
		otherConversationPoint({"greeting","greeting" });
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
	//if (optionsIndex == 3)
		//init_conv = true;
	//else
	    //init_conv = false;
}

DialogueHelper* DialogueController::getDialogueHelper()
{
	return &dialogue;
}

void DialogueController::offerQuest_hack_() {
	dialogue_point line;
	//line.push_back({ {}, {} });
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
	// dialogue.get_possible_reply_pts(point[0]);
	//vector<std::string> print = getReplyOptions();
	select = 0;
	state = 2; 
	//PlayerResponse();
}