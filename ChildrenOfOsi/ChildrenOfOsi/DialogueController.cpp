#include "stdafx.h"
#include "DialogueController.h"
#include "CheckClass.h"
#include "ConversationPoint.h"
#include "Tag.h"
#include "ConversationLogObj.h"

Player* DialogueController::player;
WorldObj* DialogueController::other;
int DialogueController::state = 0;
//States:
//0 is no conversation
//1 is waiting for player input
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response

/*state 5 is used to show the player's conversation point and 
to allow the player to choose when to allow the npc to reply*/
//5 is waiting for player to select "Next" option

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
std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec;
std::string player_conv_point_choice = "";

//Hero to int associations
// SHANGO 1
// YEMOJA 2
// OYA 3
// OSHOSI 4
// OGUN 5

//Dummy vectors for Yemoja's and Shango's relationships and personalities

/*index 0 = Affinity, index 1 = notoriety, index 2 = strength, index 3 = AffEstimate
index 4 = NotorEstimate, index 5 = StrEstimate*/
std::vector<int> yemoja_relationship_with_shango = {60, 50, 50, 50, 50, 50};
std::vector<int> yemoja_relationship_with_oya = {70, 40, 80, 70, 40, 80 };
std::vector<int> shango_relationship_with_yemoja = { 50, 50, 60, 50, 50, 60 };
std::vector<int> shango_relationship_with_oya = { 50, 50, 60, 50, 50, 60 };

/*index 0 = honor, index 1 = pride, index 2 = aggression, index 3 = kindness
index 4 = greed, index 5 = recklessness, index 6 = extroversion*/
std::vector<int> yemoja_personality = {30, 70, 80, 60, 30, 30, 50};
std::vector<int> shango_personality = {50, 50, 60, 60, 50, 60, 20};

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
	dialogue_point choice;
	if (player_conv_point_choice == "") {
		while (options[optionsIndex].size() == 0) {
			optionsIndex++;
			if (optionsIndex >= options.size()) {
				optionsIndex = 0;
			}
		}
		vector<std::string> print = getOptions();
		choice = options[optionsIndex][select + DialogueController::scroll_control];
		std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player, 1, 1);
		message = player->getName() + ": " + conversation_pt_sentence;
		//////store player conversation point choice[1] here//////
		ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;
		conv_log_obj->set_who(1);
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[1]]);
		conv_log_obj->update_number_of_times_said();
		if (choice[1].at(0) == 'M')
			conv_log_obj->set_topic(3, mem); //make the topic Oya if the player selected a move to action
		else
			conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
		conversation_log_obj_pointer_vec.push_back(conv_log_obj);
		///////////////////////////////////////////////////////////
		player_conv_point_choice = choice[1];
		state = 5;
	}
	else {
		state = 4;
		otherResponse(player_conv_point_choice);
		player_conv_point_choice = "";
	}
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
			//planner->get_current_action()->executed = true;
			prompted_quest = false;
			accepted_quest = true;
		}
		else             // Player is denying the quest
		{

		}

	}
	//calculation for shango's phrase selection based on relationship
	int shango_relationship_phrase_picker = 1;
	if (shango_relationship_with_yemoja[0] <= 20) {
		shango_relationship_phrase_picker = 1;
	}
	else if (shango_relationship_with_yemoja[0] > 20 && shango_relationship_with_yemoja[0] < 40) {
		shango_relationship_phrase_picker = 2;
	}
	else if (shango_relationship_with_yemoja[0] >= 40 && shango_relationship_with_yemoja[0] < 60) {
		shango_relationship_phrase_picker = 3;
	}
	else if (shango_relationship_with_yemoja[0] >= 60 && shango_relationship_with_yemoja[0] < 80) {
		shango_relationship_phrase_picker = 4;
	}
	else if (shango_relationship_with_yemoja[0] >= 80) {
		shango_relationship_phrase_picker = 5;
	}
	std::string reply_pt_sentence = dialogue.gen_dialog(choice, player,1, shango_relationship_phrase_picker);
	//////store player reply choice[1] here//////
	ConversationLogObj* conv_log_obj = new ConversationLogObj();
	Memory* mem = nullptr;
	conv_log_obj->set_who(1);
	conv_log_obj->set_conv_point(Containers::conv_point_table[choice[1]]);
	conv_log_obj->update_number_of_times_said();
	if (choice[1].size() > 12) {
		if (choice[1].at(12) == 'M')
			conv_log_obj->set_topic(3, mem); //make the topic Oya if the player selected a move to action
	}
	else
		conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
	/////////////////////////////////////////////
	//draws reply
	if (conv_log_obj->get_topic().first == 3)
		reply_pt_sentence.insert(0, "Oya");
	message = player->getName()+": "+reply_pt_sentence +"\n\n";
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point line)
{
	dialogue_point point = dialogue.choose_conv_pt(conversation_log_obj_pointer_vec, yemoja_personality, yemoja_relationship_with_shango);
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

	//calculation for yemoja's phrase selection based on relationship
	int relationship_phrase_picker = 1;
	if (yemoja_relationship_with_shango[0] <= 20) {
		relationship_phrase_picker = 1;
	}
	else if (yemoja_relationship_with_shango[0] > 20 && yemoja_relationship_with_shango[0] < 40) {
		relationship_phrase_picker = 2;
	}
	else if (yemoja_relationship_with_shango[0] >= 40 && yemoja_relationship_with_shango[0] < 60) {
		relationship_phrase_picker = 3;
	}
	else if (yemoja_relationship_with_shango[0] >= 60 && yemoja_relationship_with_shango[0] < 80) {
		relationship_phrase_picker = 4;
	}
	else if (yemoja_relationship_with_shango[0] >= 80) {
		relationship_phrase_picker = 5;
	}

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero, relationship_phrase_picker, 1);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero, relationship_phrase_picker, 1);
	//////store NPC reply point(line[1]) and conversation point here(point[1])//////
	ConversationLogObj* conv_log_obj = new ConversationLogObj();
	Memory* mem = nullptr;
	std::string hero_name_str = other->getName();
	int who_arg = 1;
	if (hero_name_str == "Shango")
	{
		who_arg = 1;
	}
	else if (hero_name_str == "Yemoja")
	{
		who_arg = 2;
	}
	else if (hero_name_str == "Oshosi")
	{
		who_arg = 4;
	}
	else if (hero_name_str == "Oya")
	{
		who_arg = 3;
	}
	else if (hero_name_str == "Ogun")
	{
		who_arg = 5;
	}
	    //initialization of conversation log object for reply point
	conv_log_obj->set_who(who_arg);
	conv_log_obj->set_conv_point(Containers::conv_point_table[line[1]]);
	conv_log_obj->update_number_of_times_said();
	if (line[1].size() > 12) {
		if (line[1].at(12) == 'M') {
			conv_log_obj->set_topic(3, mem); //make the topic Oya if the player selected a move to action
			reply_pt_sentence.insert(0, "Oya");
		}
		else if (line[1].size() > 20) {
			if ((line[1].at(19) == 'S' || line[1].at(19) == 'A' || line[1].at(19) == 'N') && (line[1].at(13) != 'S')) {
				conv_log_obj->set_topic(3, mem); //make the topic Oya if the player selected a move to action
				reply_pt_sentence.insert(0, "Oya");
			}
		}
	}
	else
		conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
	    //initialization of conversation log object for conversation point
	conv_log_obj->set_who(who_arg);
	conv_log_obj->set_conv_point(Containers::conv_point_table[point[1]]);
	conv_log_obj->update_number_of_times_said();
	if (point[1].at(0) == 'M') {
		conv_log_obj->set_topic(3, mem); //make the topic Oya if the player selected a move to action
		con_pt_sentence.append(" Oya");
	}
	else if (point[1].size() > 12) {
		if (point[1].at(10) == 'S' || point[1].at(10) == 'A' || point[1].at(10) == 'N') {
			conv_log_obj->set_topic(3, mem); //make the topic Oya if the player selected a move to action
			con_pt_sentence.append(" Oya");
		}
	}
	else
		conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
	///////////////////////////////////////////////////////////////////////////////
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[1], optionsIndex);
	vector<std::string> print = getReplyOptions();

	select = 0;
	state = 2; //had at 0 for testing one time
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
	//prints to file to check for proper tag and conversation point associations
	/*std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	for (auto itor = Containers::tag_table.begin(); itor != Containers::tag_table.end(); itor++) {
		for (int i = 0; i < itor->second->get_conversation_pointer_vec().size(); i++) {
			ofs << "Tag Name: " << itor->first << " Conversation Point Name: " << itor->second->conversation_point_pointer_vec[i]->get_name() << std::endl;
		}
	}
	for (auto it = Containers::conv_point_table.begin(); it != Containers::conv_point_table.end(); it++) {
		for (int i = 0; i < it->second->tag_pointer_vec.size(); i++) {
			ofs << "Conversation Point Name: " << it->first << " Tag Name: " << it->second->tag_pointer_vec[i]->get_name() << std::endl;
		}
	}
	ofs.close();*/
	other = n;
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
	//////code to clear conversation vector goes here//////
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	
	for (int i = 0; i < conversation_log_obj_pointer_vec.size(); i++) {
		//ofs <<" conversation point name: " << conversation_log_obj_pointer_vec[i]->get_conv_point()->get_name() << " who: "<< conversation_log_obj_pointer_vec[i]->get_who()<< " topic: " << conversation_log_obj_pointer_vec[i]->get_topic()<< " Number of times said: " << conversation_log_obj_pointer_vec[i]->get_number_of_times_said() <<std::endl;
		//delete memory allocated for instance of Memory class
		//std::pair<int, Memory*> tmp_top;
		//tmp_top = conversation_log_obj_pointer_vec[i]->get_topic();
		//delete tmp_top.second;
		//delete memory allocated for conversation log object
		//delete conversation_log_obj_pointer_vec[i];
	}
	conversation_log_obj_pointer_vec.clear();
	//ofs.close();
	///////////////////////////////////////////////////////
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

	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero, 1, 1);
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
	return_val_vec = DialogueController::getDialogueHelper()->get_dialog("Shango", dp,1,1);
	return return_val_vec[0];
}