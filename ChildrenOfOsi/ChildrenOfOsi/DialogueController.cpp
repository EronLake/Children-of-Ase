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
//5 is waiting for player to select "Next" option

/*state 5 is used to show the player's conversation point and 
to allow the player to choose when to allow the npc to reply*/


DialogueHelper DialogueController::dialogue;
std::vector<std::vector<dialogue_point>> DialogueController::options;
std::vector<dialogue_point> DialogueController::replyOptions;
std::string DialogueController::message;
int DialogueController::optionsIndex=0;
int DialogueController::select = 0;
std::string DialogueController::replyString;
bool DialogueController::accepted_quest = false;
bool DialogueController::prompted_quest = false;
//AIController* DialogueController::ai = nullptr;
Action* DialogueController::quest = nullptr;

int DialogueController::scroll_control = 0;
std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec;
std::string player_conv_point_choice = "";
std::string curr_hero_topic = "";
std::vector<int> DialogueController::heroes_player_knows = {2,3}; //dummy vector to keep track of what heroes the player knows(Yemoja and Oya)
bool first_call = true;

DialogueController::DialogueController()
{
	
}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	options = dialogue.get_possible_conv_pts();
	//check what heroes the player knows right here and push_back
	//"Ask_About" and "Move_To" conversation points for each one the player knows
	//Do not push back ones for the hero that the player is talking to,however
	if(first_call)
	    add_hero_related_conv_points();
	first_call = false;
	state = 1;
	//curr_hero_topic = "";
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
		vector<std::vector<std::string>> print = getOptions();
		choice = options[optionsIndex][select + DialogueController::scroll_control];
		std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);
		conversation_pt_sentence += choice[3];
		message = player->getName() + ": " + conversation_pt_sentence;
		//////store player conversation point choice[1] here//////
		ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;
		conv_log_obj->set_who(1);//"who" is always Shango(1) in this function
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[1]]);
		conv_log_obj->update_number_of_times_said();
		if (choice[1].find("Move_To") != string::npos || choice[1].find("Ask_About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[3]), mem); //make the topic Oya if the player selected a move to action
			curr_hero_topic = choice[3];
		}
		else
			conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
		conversation_log_obj_pointer_vec.push_back(conv_log_obj);
		///////////////////////////////////////////////////////////
		player_conv_point_choice = choice[1];
		state = 5;
	}
	else {
		state = 4;
		otherResponse(player_conv_point_choice, curr_hero_topic);
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
			Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
			//planner->get_current_action()->executed = true;
			prompted_quest = false;
			accepted_quest = true;
			player->add_quest(planner->get_current_action(), 2);
		}
		else             // Player is denying the quest
		{

		}

	}
	
	std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);
	//////store player reply choice[1] here//////
	ConversationLogObj* conv_log_obj = new ConversationLogObj();
	Memory* mem = nullptr;
	conv_log_obj->set_who(1);
	conv_log_obj->set_conv_point(Containers::conv_point_table[choice[1]]);
	conv_log_obj->update_number_of_times_said();
	if (choice[1].find("Move_To") != string::npos || choice[1].find("Ask_About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[3]), mem); //make the topic Oya if the player selected a move to action
	}
	else
		conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
	/////////////////////////////////////////////
	//draws reply
	if (conv_log_obj->get_topic().first != 1 && (choice[1].find("Move_To") != string::npos || choice[1].find("Ask_About") != string::npos))
		reply_pt_sentence.insert(0, choice[3]);
	message = player->getName()+": "+reply_pt_sentence +"\n\n";
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point line)
{
	dialogue_point point = dialogue.choose_conv_pt(conversation_log_obj_pointer_vec);
	if (point[0] != "No_More_Phrases" && point[0] != "Already_Asked" && point.size() >= 4)
		point[3] = curr_hero_topic;
	replyString = point[1];

	Hero* temp_hero = nullptr;
	if (other->getType() >= WorldObj::TYPE_NPC) {
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

	//////store NPC reply point(line[1]) and conversation point here(point[1])//////
 if(line[1] != "Already_Asked"){
	ConversationLogObj* conv_log_obj = new ConversationLogObj();
	Memory* mem = nullptr;

	//initialization of conversation log object for reply point
	conv_log_obj->set_who(dialogue.hero_name_to_int(other->getName()));
	conv_log_obj->set_conv_point(Containers::conv_point_table[line[1]]);
	conv_log_obj->update_number_of_times_said();
	if (line[1].find("Move_To") != string::npos || line[1].find("Ask_About") != string::npos) {
		conv_log_obj->set_topic(dialogue.hero_name_to_int(line[3]), mem); //make the topic Oya if the player selected a move to action
		reply_pt_sentence.insert(0, line[3]);
	}
	else
		conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
	//initialization of conversation log object for conversation point
	conv_log_obj->set_who(dialogue.hero_name_to_int(other->getName()));
	conv_log_obj->set_conv_point(Containers::conv_point_table[point[1]]);
	conv_log_obj->update_number_of_times_said();
	if (point[1].find("Move_To") != string::npos || point[1].find("Ask_About") != string::npos) {
		conv_log_obj->set_topic(dialogue.hero_name_to_int(point[3]), mem); //make the topic Oya if the player selected a move to action
		con_pt_sentence.append(point[3]);
	}
	else
		conv_log_obj->set_topic(1, mem);//otherwise make the topic Shango
	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
  }
	///////////////////////////////////////////////////////////////////////////////
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[1], optionsIndex);
	vector<std::vector<std::string>> print = getReplyOptions();
	
	select = 0;
	if (point[1] != "No_More_Phrases" && point[1] != "Already_Asked" && point[1] != "")
		state = 2; //had at 0 for testing one time
	else
		state = 1; //skip player reply if npc cannot give a conversation point
	DialogueController::scroll_control = 0;
}

void DialogueController::otherResponse(std::string info, std::string hero_topic)
{
	dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex,conversation_log_obj_pointer_vec);
	if(line.size() >= 4)
	    line[3] = hero_topic;
	state = 3;
	otherConversationPoint(line);
}

vector<std::vector<std::string>> DialogueController::getOptions()
{
	vector<std::vector<std::string>> tmp;
	
	for (int i = 0; i < options[optionsIndex].size(); i++) 
	{
		tmp.push_back(options[optionsIndex][i]);
	}
	return tmp;
}

vector<std::vector<std::string>> DialogueController::getReplyOptions()
{
	vector<std::vector<std::string>> tmp;
	for (int i = 0; i < replyOptions.size(); i++)
	{
		    replyOptions[i][3] = curr_hero_topic;
			tmp.push_back(replyOptions[i]);
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
	//message = "You started talking to ";
	//message += n->getName();
	Hero* temp_hero = CheckClass::isHero(other);
	message = n->getName() + ": " + dialogue.gen_dialog({ "Greeting","Greeting"},temp_hero);
	
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
	remove_hero_related_conv_points();
	first_call = true;
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
	if (other->getType() >= WorldObj::TYPE_NPC) {
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

/*
std::string DialogueController::convert_option_to_phrase(std::string opt, Hero* hero) {
	dialogue_point dp;
	dialogue_point return_val_vec;
	dp.push_back("");
	dp.push_back(opt);
	return_val_vec = DialogueController::getDialogueHelper()->get_dialog("Shango", dp, hero);
	return return_val_vec[0];
}*/

void DialogueController::add_hero_related_conv_points() {
	options = dialogue.get_possible_conv_pts();
	dialogue_point tmp_dpoint;
	int loop_condition = options[3].size();
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
		for (int j = 0; j < heroes_player_knows.size(); ++j) {
			if (heroes_player_knows[j] != dialogue.hero_name_to_int(other->getName())) {
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Move_To",0) == string::npos && itor->second->dpoint[2] == "") {
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[3] = dialogue.int_to_hero_name(heroes_player_knows[j]);
					options[3].push_back(tmp_dpoint);
					dialogue.get_possible_conv_pts_ref()[3].push_back(tmp_dpoint);
				}
			}
		}
	}
	tmp_dpoint.clear();
	loop_condition = options[2].size();
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
		for (int j = 0; j < heroes_player_knows.size(); ++j) {
			if (heroes_player_knows[j] != dialogue.hero_name_to_int(other->getName())) {
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Ask_About", 0) == string::npos && itor->second->dpoint[2] == "") {
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[3] = dialogue.int_to_hero_name(heroes_player_knows[j]);
					options[2].push_back(tmp_dpoint);
					dialogue.get_possible_conv_pts_ref()[2].push_back(tmp_dpoint);
				}
			}
		}
	}
}

void DialogueController::remove_hero_related_conv_points() {
	for (int i = 0; i < options[3].size();) {
		if (options[3][i][1].find("Move_To", 0) != string::npos || options[3][i][1].find("Ask_About", 0) != string::npos) {
			options[3].erase(options[3].begin() + i);
		}
		else
			++i;
		//options[3][i].push_back(tmp_dpoint);
		//dialogue.get_possible_conv_pts_ref()[3].push_back(tmp_dpoint);
		//options[2].push_back(tmp_dpoint);
		//dialogue.get_possible_conv_pts_ref()[2].push_back(tmp_dpoint);
	}

	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[3].size();) {
		if (dialogue.get_possible_conv_pts_ref()[3][i][1].find("Move_To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[3][i][1].find("Ask_About", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[3].erase(dialogue.get_possible_conv_pts_ref()[3].begin() + i);
		}
		else
			++i;
	}

	for (int i = 0; i < options[2].size();) {
		if (options[2][i][1].find("Move_To", 0) != string::npos || options[2][i][1].find("Ask_About", 0) != string::npos) {
			options[2].erase(options[2].begin() + i);
		}
		else
			++i;
	}

	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[2].size();) {
		if (dialogue.get_possible_conv_pts_ref()[2][i][1].find("Move_To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[2][i][1].find("Ask_About", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[2].erase(dialogue.get_possible_conv_pts_ref()[2].begin() + i);
		}
		else
			++i;
	}
}