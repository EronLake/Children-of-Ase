#include "stdafx.h"
#include "DialogueController.h"
#include "CheckClass.h"
#include "ConversationPoint.h"
#include "Tag.h"
#include "ConversationLogObj.h"

Player* DialogueController::player;
WorldObj* DialogueController::other; //the npc speaking with the player
int DialogueController::state = 0;

constexpr int NoTopic() { return -1; }
//States:
//0 is no conversation
//1 is waiting for player conversation point
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response
//5 is waiting for player to press "Enter" key to select "Next" option

/*state 5 is used to show the player's conversation point and 
to force the GUI to wait for more player input before showing
the npc's reply and or conversation points*/


DialogueHelper DialogueController::dialogue;

/*holds the dialog options for the player's conversation and reply points
that are displayed as text on the lower GUI window*/
std::vector<std::vector<dialogue_point>> DialogueController::options;
std::vector<dialogue_point> DialogueController::replyOptions;

std::string DialogueController::message;   //text displayed on upper window of GUI
std::string DialogueController::replyString;

int DialogueController::optionsIndex=0;    //indicates icon the player has selected
int DialogueController::select = 0;        //indicates the position of the option selected by the player

bool DialogueController::accepted_quest = false;
bool DialogueController::prompted_quest = false;
Action* DialogueController::quest = nullptr;

//used to decide index to begin iterating at for displaying dialog options
int DialogueController::scroll_control = 0;

/*conversation log that holds pointers to different entries for
current conversation only*/
std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec;

/*used for passing player's conversation point selection to 
otherResponse() function when state is no longer 5 in 
PlayerConversationPoint() function*/
std::string player_conv_point_choice = ""; 

//keeps track of the topic of the current conversation cycle
std::string curr_hero_topic = "";

//keep track of what heroes the player knows(2=Yemoja and 3=Oya)
std::vector<int> DialogueController::heroes_player_knows = {2,3}; 

//keep add_hero_conv_points() function to one call per conversation
bool first_call = true;

DialogueController::DialogueController()
{
	
}


DialogueController::~DialogueController()
{
}

/*Gets all of the player's conversation point dialog options and sets
the conversation state to wait for the player to select a conversation
point*/
void DialogueController::PlayerChoose()
{
	options = dialogue.get_possible_conv_pts();
	if(first_call)
		/*add "Ask_About" and "Move_To" conversation points to player's
		dialog options*/
	    add_hero_related_conv_points();
	first_call = false;
	state = 1;
}

/*Identifies the player's conversation point selection, stores
it in the log for the current conversation, sets the conversation state to 5
to make GUI wait for player to press "Enter" to see npc's reply and 
conversation points, sets state to 4 after player presses "Enter", which
shifts the conversation to see the npc reply. Calls otherResponse() function
to generate npc's reply point.*/
void DialogueController::PlayerConversationPoint()
{
	dialogue_point choice;

	/*prevents the player's selection of the "Next" option from being stored
	in the log for the current conversation. Uses the fact that we know
	that the player's conversation point choice will not be empty if
	they have reached the state with the "Next" option.*/
	if (player_conv_point_choice == "") {
		//capture player's selection
	    choice = options[optionsIndex][select + DialogueController::scroll_control];

		//get a sentence to say based on their option selection
		std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);

		/*adds the hero's name to the end of the sentence if the conversation 
		point is hero-related, or adds an empty string if it is not. The value
		at choice[3] will be one of these depending on the conversation
		point option selected.*/
		conversation_pt_sentence += choice[3];

		message = player->getName() + ": " + conversation_pt_sentence;

		/*stores the player's conversation point(choice[1]) in a log entry
		and that entry gets stored in the log for the current conversation. 
		We use index 1 of choice because that is where the name of the 
		conversation point is kept.*/
		ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;

		conv_log_obj->set_who(1);
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[1]]);
		conv_log_obj->update_number_of_times_said();

		/*set the topic for the log entry of the player's selection.
		If player's selection has no topic, the topic is set to a value
		that indicates that there is no topic asscoiated with their
		conversation point.*/
		if (choice[1].find("Move_To") != string::npos || choice[1].find("Ask_About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[3]), mem);
			curr_hero_topic = choice[3];
		}
		else
			conv_log_obj->set_topic(NoTopic(), mem);

		conversation_log_obj_pointer_vec.push_back(conv_log_obj);//add entry to log
		
		player_conv_point_choice = choice[1];
		state = 5;
	}
	else {
		state = 4;
		otherResponse(player_conv_point_choice, curr_hero_topic);
		player_conv_point_choice = "";
	}
}

/*Identifies the player's reply point selection, stores it in the log for
the current conversation, creates a sentence that the player will say based
on their reply option selection.*/
void DialogueController::PlayerResponse()
{
	dialogue_point choice = replyOptions[select + DialogueController::scroll_control];

	/*quest dialog code that was done by Justin and Alessio. Is placeholder
	and will be removed at some point.*/
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
	
	//get a sentence to say based on player's reply option selection
	std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);

	/*Creates log entry for player's reply point selection(choice[1])
	and stores entry in log for current conversation.*/
	ConversationLogObj* conv_log_obj = new ConversationLogObj();
	Memory* mem = nullptr;

	conv_log_obj->set_who(1);
	conv_log_obj->set_conv_point(Containers::conv_point_table[choice[1]]);
	conv_log_obj->update_number_of_times_said();

	/*set topic to appropriate hero if player is replying to hero-related
	conversation point.*/
	if (choice[1].find("Move_To") != string::npos || choice[1].find("Ask_About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[3]), mem);
	}
	else
		conv_log_obj->set_topic(NoTopic(), mem);

	conversation_log_obj_pointer_vec.push_back(conv_log_obj);
	
	/*insert the topic at the beginning of the player's reply point sentence
	if they are replying to a hero-related conversation point*/
	if (conv_log_obj->get_topic().first != NoTopic() && (choice[1].find("Move_To") != string::npos || choice[1].find("Ask_About") != string::npos))
		reply_pt_sentence.insert(0, choice[3]);

	message = player->getName()+": "+reply_pt_sentence +"\n\n";
	PlayerChoose();//start all over from player conversation point again
}

/*Calls functions from the DialogueHelper to handle generating the npc's
conversation point and reply point. Creates log entries for the npc's
conversation and reply points and stores the entries in the log
for the current conversation.*/
void DialogueController::otherConversationPoint(dialogue_point line)
{
	dialogue_point point = dialogue.choose_conv_pt(conversation_log_obj_pointer_vec);

	/*Only sets the topic of the npc's conversation point if it is not
	a special case. Special case dialogue points are typically only
	of size 2.*/
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

	/*Stores the npc's conversation and reply points as entries in the
	log for the current conversation. The reply point is line[1] and the
	conversation point is point[1].*/
    if(line[1] != "Already_Asked"){
	    ConversationLogObj* conv_log_obj = new ConversationLogObj();
	    Memory* mem = nullptr;

	    //initialization of conversation log entry for reply point
	    conv_log_obj->set_who(dialogue.hero_name_to_int(other->getName()));
	    conv_log_obj->set_conv_point(Containers::conv_point_table[line[1]]);
	    conv_log_obj->update_number_of_times_said();

		/*insert the topic at the beginning of the npc's reply point sentence
		if they are replying to a hero-related conversation point.*/
	    if (line[1].find("Move_To") != string::npos || line[1].find("Ask_About") != string::npos) {
		    conv_log_obj->set_topic(dialogue.hero_name_to_int(line[3]), mem); //make the topic Oya if the player selected a move to action
		    reply_pt_sentence.insert(0, line[3]);
	    }
	    else
		    conv_log_obj->set_topic(NoTopic(), mem);

	    conversation_log_obj_pointer_vec.push_back(conv_log_obj);

	//initialization of conversation log entry for conversation point
		ConversationLogObj* conv_log_obj2 = new ConversationLogObj();
		Memory* mem2 = nullptr;

		conv_log_obj2->set_who(dialogue.hero_name_to_int(other->getName()));
		conv_log_obj2->set_conv_point(Containers::conv_point_table[point[1]]);
		conv_log_obj2->update_number_of_times_said();

		/*insert the topic at the end of the npc's conversation point sentence
		if they are saying a hero-related conversation point.*/
	    if (point[1].find("Move_To") != string::npos || point[1].find("Ask_About") != string::npos){
			conv_log_obj2->set_topic(dialogue.hero_name_to_int(point[3]), mem2);
		    con_pt_sentence.append(point[3]);
	    }
	    else
			conv_log_obj2->set_topic(NoTopic(), mem2);

	    conversation_log_obj_pointer_vec.push_back(conv_log_obj2);
    }
	
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[1], optionsIndex);
	
	select = 0;

	/*skips the player's reply point if the npc does not say a conversation 
	point, if the npc tells the player that they already asked them something,
	or if an npc runs out of relevant conversation points to say.
	*/
	if (point[1] != "No_More_Phrases" && point[1] != "Already_Asked" && point[1] != "")
		state = 2;
	else
		state = 1;//skip player reply if npc cannot give a conversation point

	DialogueController::scroll_control = 0;
}

/*Handles the generation of the npc's reply point by calling functions from 
DialogueHelper. Calls otherConversationPoint() function to generate the
npc's conversation point and to display the npc's reply and conversation
points.*/
void DialogueController::otherResponse(std::string info, std::string hero_topic)
{
	dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex,conversation_log_obj_pointer_vec);

	/*avoids setting a topic when npc replies with "You already asked me that"
	 or if npc says any other special case reply. Special case replies are
	 typically vectors with a size of only 2.*/
	if(line.size() >= 4)
	    line[3] = hero_topic;

	state = 3;
	otherConversationPoint(line);
}

/*Returns the player's conversation point dialogue options that 
correspond to the icon that they currently have selected.*/
vector<std::vector<std::string>> DialogueController::getOptions()
{
	vector<std::vector<std::string>> tmp;
	
	for (int i = 0; i < options[optionsIndex].size(); i++) 
	{
		tmp.push_back(options[optionsIndex][i]);
	}
	return tmp;
}

/*Returns the player's reply point dialogue options.*/
vector<std::vector<std::string>> DialogueController::getReplyOptions()
{
	vector<std::vector<std::string>> tmp;
	for (int i = 0; i < replyOptions.size(); i++)
	{
		    replyOptions[i][3] = curr_hero_topic;//sets the topic for reply
			tmp.push_back(replyOptions[i]);
	}
	return tmp;
}

/*Initializes the player object and initializes the 
conversation state to 0, meaning that there is no 
conversation happening.*/
void DialogueController::setPlayer(Player* p)
{
	player = p;
	state = 0;
}

/*Initializes the npc in the conversation, calls PlayerChoose() function
to set conversation state to wait for player to select a conversation point
dialogue option. Calls DialogueHelper functions to generate npc's greeting
message.*/
void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	other = n;
	Hero* temp_hero = CheckClass::isHero(other);
	message = n->getName() + ": " + dialogue.gen_dialog({ "Greeting","Greeting"},temp_hero);
	
	if (playerTalk) {
 		PlayerChoose();
	}
}

/*Returns pointer to the npc in the conversation.*/
WorldObj* DialogueController::getOther()
{
	return other;
}

/*Returns the current conversation state*/
int DialogueController::getState()
{
	return state;
}

/*Sets the conversation state to 0, which means that there is no conversation
happening currently. Frees the memory allocated for all of the conversation
log entries for the current conversation, clears the log, and removes all
hero-related conversation points from the 3D vector of possible conversation
points and removes them from the options vector.*/
void DialogueController::exitDialogue()
{
	other = nullptr;
	state=0;
	DialogueController::scroll_control = 0;
	
	for (int i = 0; i < conversation_log_obj_pointer_vec.size(); i++) {
		
		//delete memory allocated for instance of Memory class here
		     //delete tmp_top.second;
		//delete memory allocated for conversation log object here
		    //delete conversation_log_obj_pointer_vec[i];
	}

	conversation_log_obj_pointer_vec.clear();

	remove_hero_related_conv_points();
	first_call = true;
}

/*Returns a pointer to the instance of the DialogueHelper class that
the DialogueController uses to call DialogueHelper functions.*/
DialogueHelper* DialogueController::getDialogueHelper()
{
	return &dialogue;
}

/*Code done by Justin and Alessio to force npc to offer the player a quest.
if the player attempts to exit dialogue. Will probably be removed at 
some point.*/
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

/*Adds hero-related conversation points to the 3D vector of possible
conversation points and adds them to the vector of the player's dialog
options.*/
void DialogueController::add_hero_related_conv_points() {
	options = dialogue.get_possible_conv_pts();
	dialogue_point tmp_dpoint;

	/*Adds hero-related conversation points to player's vector of dialogue options
	and to their 3D vector of possible conversation points for conversation points
	associated with the question mark icon*/
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

	/*Adds hero-related conversation points to player's vector of dialogue options
	and to their 3D vector of possible conversation points for conversation points
	associated with the notoriety icon*/
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

/*Removes hero-related conversation points from the 3D vector of possible
conversation points and removes them from the vector of the player's dialog
options.*/
void DialogueController::remove_hero_related_conv_points() {
	/*removes hero-related conversation points that are associated with the
	question mark icon from player's dialog options vector */
	for (int i = 0; i < options[3].size();) {
		if (options[3][i][1].find("Move_To", 0) != string::npos || options[3][i][1].find("Ask_About", 0) != string::npos) {
			options[3].erase(options[3].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible
	conversation points that are associated with the question mark icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[3].size();) {
		if (dialogue.get_possible_conv_pts_ref()[3][i][1].find("Move_To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[3][i][1].find("Ask_About", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[3].erase(dialogue.get_possible_conv_pts_ref()[3].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points that are associated with the 
	notoriety icon from player's dialog options vector */
	for (int i = 0; i < options[2].size();) {
		if (options[2][i][1].find("Move_To", 0) != string::npos || options[2][i][1].find("Ask_About", 0) != string::npos) {
			options[2].erase(options[2].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible 
	conversation points that are associated with the notoriety icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[2].size();) {
		if (dialogue.get_possible_conv_pts_ref()[2][i][1].find("Move_To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[2][i][1].find("Ask_About", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[2].erase(dialogue.get_possible_conv_pts_ref()[2].begin() + i);
		}
		else
			++i;
	}
}