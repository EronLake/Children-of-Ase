#include "stdafx.h"
#include "DialogueController.h"
#include "CheckClass.h"

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
std::vector<std::vector<dialogue_point>> DialogueController::replyOptions;
std::string DialogueController::message;
int DialogueController::optionsIndex=0;
std::string DialogueController::replyString;


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
	optionsIndex = 0;
	PlayerConversationPoint(0);
	//give option to Alex
}

void DialogueController::PlayerConversationPoint(int info)
{
	state = 4;
	while (options[optionsIndex].size() == 0) {
		optionsIndex++;
		if (optionsIndex >= options.size()) {
			perror("no options");
			break;
		}
	}
	vector<std::string> print = getOptions();
	std::cout << "Shango Conversation Options:" << std::endl;
	for (int i = 0; i < print.size(); i++) {
		std::cout << print[i] << std::endl;
	}
	dialogue_point choice = options[optionsIndex][info];
	std::cout << player->name<< endl;
	std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);
	std::cout << "Shango: " << conversation_pt_sentence << std::endl;
	otherResponse(choice[0]);
}

void DialogueController::PlayerResponse(int info)
{
	state = 1;
	dialogue_point choice = replyOptions[optionsIndex][info];

	std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);
	//draws reply
	message = reply_pt_sentence;
	std::cout << "Shango: " << getMessage() << std::endl;
	
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point line)
{

	dialogue_point point = dialogue.choose_conv_pt(line, optionsIndex);
	replyString = point[0];

	Hero* temp_hero = CheckClass::isHero(other);
	if (!temp_hero)
	{
		perror("you cannot talk to this type of object");
	}

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);
	
	//return sentence 

	state=2;
	//vector<dialogue_point> options = dialogue.get_possible_conv_pts();
	//give options to Alex

	//dialogue_point line = dialogue.choose_reply_pt();
	message = reply_pt_sentence + "\n\n" + con_pt_sentence;
	std::cout << other->getName() << ": "<< message << std::endl;
	replyOptions = dialogue.get_possible_reply_pts();
	vector<std::string> print = getReplyOptions();
	for (int i = 0; i < print.size(); i++) {
		std::cout << print[i] << std::endl;
	}
	state = 2;
	optionsIndex = 0;
	//getOptions();
	//give info to Alex
	PlayerResponse(0);
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

	for (int i = 0; i < replyOptions[optionsIndex].size(); i++)
	{
		if (replyOptions[optionsIndex][i][0] == replyString ||
			replyOptions[optionsIndex][i][0] == "denied")
		{
			tmp.push_back(replyOptions[optionsIndex][i][1]);
		}
		
	}

	return tmp;
	//give tmp to Alex
}

void DialogueController::setPlayer(Player* p)
{
	for (int i = 0; i < 100; i++) {
		cout << "NAME in controller " << p->name << endl;
	}
	player = p;
	state = 0;
}

void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	std::cout << player->getName() << " talked with " << n->getName() << std::endl;
	other = n;
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
}