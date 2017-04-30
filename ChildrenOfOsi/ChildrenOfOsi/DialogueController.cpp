#include "stdafx.h"
#include "DialogueController.h"
#include "CheckClass.h"
#include "ConversationPoint.h"
#include "Tag.h"
#include "ConversationLogObj.h"

Player* DialogueController::player;
WorldObj* DialogueController::other; //the npc speaking with the player
int DialogueController::state = 0;

/*Used in an attempt to lessen the use of the
hard coded indices for dialogue points as suggested
at the dialog code review*/
constexpr int NoTopic = -1;
constexpr int ConvPointName = 1;
constexpr int CorrespondingConvPt = 2;
constexpr int Topic = 3;

/*Used in an attempt to clarify what indices of the
possible reply and conversation point vectors represent
which GUI icons*/
constexpr int StrengthIcon = 0;
constexpr int AffinityIcon = 1;
constexpr int NotorietyIcon = 2;
constexpr int QuestionMarkIcon = 3;

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

//used for hero actions
bool DialogueController::accepted_action = false;

//used to decide index to begin iterating at for displaying dialog options
int DialogueController::scroll_control = 0;

/*conversation log that holds pointers to different entries for the
current conversation only*/
std::vector<ConversationLogObj*> curr_conversation_log;

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

bool DialogueController::quest_declined = false;

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
		/*add "Ask_About" and "Advise_To" conversation points to player's
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
		at choice[Topic()] will be one of these depending on the conversation
		point option selected.*/
		replace_all(conversation_pt_sentence,"HERO",choice[Topic]);

		message = player->getName() + ": " + conversation_pt_sentence;

		/*stores the player's conversation point(choice[ConvPointName()]) in a log entry
		and that entry gets stored in the log for the current conversation. 
		We use index 1 of choice because that is where the name of the 
		conversation point is kept.*/
		ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;

		conv_log_obj->set_who(1);
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[ConvPointName]]);
		conv_log_obj->update_number_of_times_said();

		/*set the topic for the log entry of the player's selection.
		If player's selection has no topic, the topic is set to a value
		that indicates that there is no topic asscoiated with their
		conversation point.*/
		if (choice[ConvPointName].find("Advise To") != string::npos || choice[ConvPointName].find("Ask About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[Topic]), mem);
			curr_hero_topic = choice[Topic];
		}
		else
			conv_log_obj->set_topic(NoTopic, mem);

		curr_conversation_log.push_back(conv_log_obj);//add entry to log
		
		player_conv_point_choice = choice[ConvPointName];

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

	/*handles applying of post conditions for relationship related conversation
	points. I also thought to incorporate checks for if a player completed an action
	by doing any of these here, but this is probably not a good place.*/
		if (player_conv_point_choice == "Bribe") {
			Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);

			if (planner->quests_given.size() > 0) {
				planner->quests_given.push_back(planner->get_current_action());
				Hero* shango = dynamic_cast<Hero*>(player);
				int time_limit = 3600;                 //1 minute limit to complete quest for now
				shango->add_quest(planner->get_current_action(), time_limit);
			}
			for (int i = 0; i < planner->quests_given.size(); ++i) {
				if (planner->quests_given[i]->getDoer()->name == SHANGO &&
					planner->get_current_action()->name.find("Bribe", 0) != string::npos) {
					//set quest to complete here if it was a bribe one
					planner->quests_given[i]->executed = false;
				}

			}
			Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
		}
		else if (player_conv_point_choice == "Compliment") {

			Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
		}
		else if (player_conv_point_choice == "Grovel") {

			Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
		}

		else if (player_conv_point_choice == "Insult") {
			Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
		}

		else if (player_conv_point_choice == "Boast") {

			Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
		}
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
	if (state != 6) {
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
		/*pushes quest onto npc's quests_given vector if the player accepts
		their quest and sets player's current action to that quest*/
		Hero* temp_hero;
		if (temp_hero = CheckClass::isHero(other)) {
			Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
			if (choice[ConvPointName] == "Accept_Quest") {
				//DialogueController::quest = planner->get_current_action();
				quest->setDoer(player);
				//quest->executed = true;
				//player->quest = quest;
				int time_limit = 3600;
				player->add_quest(quest, time_limit);
				planner->quests_given.push_back(quest); //gives npc record of what they gave player
				//player->cur_action = quest; //gives player record of what they are doing
			}
			if (choice[ConvPointName] == "Decline_Quest") {
				quest_declined = true;
				state = 10;
			}

		}

		//get a sentence to say based on player's reply option selection
		std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);

		/*Creates log entry for player's reply point selection(choice[ConvPointName()])
		and stores entry in log for current conversation.*/
		ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;

		conv_log_obj->set_who(1);
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[ConvPointName]]);
		conv_log_obj->update_number_of_times_said();

		/*set topic to appropriate hero if player is replying to hero-related
		conversation point.*/
		if (choice[ConvPointName].find("Take Advice") != string::npos || choice[ConvPointName].find("Tell About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[Topic]), mem);
		}
		else
			conv_log_obj->set_topic(NoTopic, mem);

		curr_conversation_log.push_back(conv_log_obj);

		/*insert the topic at the beginning of the player's reply point sentence
		if they are replying to a hero-related conversation point*/
		if (conv_log_obj->get_topic().first != NoTopic && (choice[ConvPointName].find("Take Advice") != string::npos || choice[ConvPointName].find("Tell About") != string::npos))
			replace_all(reply_pt_sentence,"HERO", choice[Topic]);

		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		/*If player replies accepting an alliance, duel or spar, enter
		farewell state to force player to exit dialogue.*/
		if (choice[ConvPointName] == "Accept Alliance Offer" || choice[ConvPointName] == "Accept Duel" || choice[ConvPointName] == "Accept Spar Request") {
			player_conv_point_choice = choice[ConvPointName];
			state = 6;
		}
		else if(state != 10)//move to exit dialogue if player declined a quest
		    PlayerChoose();//start all over from player conversation point again
	}
	else {
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

		if (player_conv_point_choice == "Accept Alliance Offer") {
			dialogue_point diog_pt = {"Confirm Alliance","Confirm Alliance"};
			std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
			message = other->getName() + ": " + reply_pt_sentence + "\n\n";
		}
		else if (player_conv_point_choice == "Accept Duel") {
			dialogue_point diog_pt = { "Confirm Duel","Confirm Duel"};
			std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
			message = other->getName() + ": " + reply_pt_sentence + "\n\n";
		}
		else if (player_conv_point_choice == "Accept Spar Request") {
			dialogue_point diog_pt = {"Confirm Spar","Confirm Spar" };
			std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
			message = other->getName() + ": " + reply_pt_sentence + "\n\n";
		}
		state = 7;
	}
}

/*Calls functions from the DialogueHelper to handle generating the npc's
conversation point and reply point. Creates log entries for the npc's
conversation and reply points and stores the entries in the log
for the current conversation.*/
void DialogueController::otherConversationPoint(dialogue_point line)
{
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

	dialogue_point point = dialogue.choose_conv_pt(curr_conversation_log, temp_hero,player);

	/*Only sets the topic of the npc's conversation point if it is not
	a special case. Special case dialogue points are typically only
	of size 2.*/
	if (point[0] != "No_More_Phrases" && point[0] != "Already_Asked" && point.size() >= 4)
		point[Topic] = curr_hero_topic;

	/*handles special case of quest conversation point by making
	sure it's dialogue point will be the same size as the basic
	conversation points like "Ask_Name" etc.*/
	if (point[ConvPointName].find("Quest") != string::npos) {
		point.push_back("");
		point.push_back("");
	}
	    
	replyString = point[ConvPointName];

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);

	/*Stores the npc's conversation and reply points as entries in the
	log for the current conversation. The reply point is line[ConvPointName()] and the
	conversation point is point[ConvPointName()].*/
    if(line[ConvPointName] != "Already_Asked"){
	    ConversationLogObj* conv_log_obj = new ConversationLogObj();
	    Memory* mem = nullptr;

	    //initialization of conversation log entry for reply point
	    conv_log_obj->set_who(dialogue.hero_name_to_int(other->getName()));
	    conv_log_obj->set_conv_point(Containers::conv_point_table[line[ConvPointName]]);
	    conv_log_obj->update_number_of_times_said();

		/*insert the topic at the beginning of the npc's reply point sentence
		if they are replying to a hero-related conversation point.*/
	    if (line[ConvPointName].find("Take Advice") != string::npos || line[ConvPointName].find("Tell About") != string::npos) {
		    conv_log_obj->set_topic(dialogue.hero_name_to_int(line[Topic]), mem); //make the topic Oya if the player selected a move to action
		    replace_all(reply_pt_sentence,"HERO",line[Topic]);
	    }
	    else
		    conv_log_obj->set_topic(NoTopic, mem);

	    curr_conversation_log.push_back(conv_log_obj);

	//initialization of conversation log entry for conversation point
		ConversationLogObj* conv_log_obj2 = new ConversationLogObj();
		Memory* mem2 = nullptr;

		conv_log_obj2->set_who(dialogue.hero_name_to_int(other->getName()));
		conv_log_obj2->set_conv_point(Containers::conv_point_table[point[ConvPointName]]);
		conv_log_obj2->update_number_of_times_said();

		/*insert the topic at the end of the npc's conversation point sentence
		if they are saying a hero-related conversation point.*/
	    if (point[ConvPointName].find("Advise To") != string::npos || point[ConvPointName].find("Ask About") != string::npos){
			conv_log_obj2->set_topic(dialogue.hero_name_to_int(point[Topic]), mem2);
		    replace_all(con_pt_sentence,"HERO",point[Topic]);
	    }
		else if (point[ConvPointName].find("Offer_Quest") != string::npos) {
			Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
			DialogueController::quest = planner->get_current_action();
			conv_log_obj2->set_topic(quest->getDoer()->name, mem2);
			replace_all(con_pt_sentence, "HERO", dialogue.int_to_hero_name(quest->getReceiver()->name));//receiver or doer here? ask Justin

			//these two lines strip the number off the end of the name 
			std::string::size_type name_end = quest->name.find_last_of('_');
			std::string act_name = quest->name.substr(0, name_end);

			replace_all(con_pt_sentence, "ACTION", act_name);
		}
	    else
			conv_log_obj2->set_topic(NoTopic, mem2);

	    curr_conversation_log.push_back(conv_log_obj2);
    }
	
	message = other->getName() + ": " + reply_pt_sentence + "\n" +con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[ConvPointName], optionsIndex);
	
	select = 0;

	/*skips the player's reply point if the npc does not say a conversation 
	point, if the npc tells the player that they already asked them something,
	or if an npc runs out of relevant conversation points to say.
	*/
	if (point[ConvPointName] != "No_More_Phrases" && point[ConvPointName] != "Already_Asked" && point[ConvPointName] != "" && point[ConvPointName] != "No Quest")
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
	Hero* temp_hero = nullptr;
	if (other->getType() >= WorldObj::TYPE_NPC) {
		if (temp_hero = CheckClass::isHero(other))
		{
			perror("you cannot talk to this type of object");
		}
	}
	else {
		return;
	}

	if (state != 8) {
		dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log);
		replyString = line[ConvPointName];

		/*avoids setting a topic when npc replies with "You already asked me that"
		 or if npc says any other special case reply. Special case replies are
		 typically vectors with a size of only 2.*/
		if (line.size() >= 4)
			line[Topic] = hero_topic;


		if (replyString == "Accept Alliance Offer") {
			//calls action start if the question is asked at all
			PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);

			//check if I want to accept (seeting to fail for testing)
			accepted_action = true; //should call a function

			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			} else{
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			
			state = 8;
		}
		else if (replyString == "Accept Duel") {
			//calls action start if the question is asked at all
			PlayerActExecFunctions::execute_start("Duel", temp_hero);

			//check if I want to accept (seeting to fail for testing)
			accepted_action = true; //should call a function

			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Duel","Accept Duel" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Duel","Accept Duel" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}

			state = 8;
		}
		else if (replyString == "Accept Spar Request") {
			//calls action start if the question is asked at all
			PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept (seeting to fail for testing)
			accepted_action = true; //should call a function

			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Spar Request","Accept Spar Request" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Spar Request","Accept Spar Request" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			state = 8;
		}
		else {
			state = 3;
			otherConversationPoint(line);
		}
	}
	else {
		if (replyString == "Accept Alliance Offer") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Alliance","Confirm Alliance" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				PlayerActExecFunctions::execute_end(false);
			}
		}
		else if (replyString == "Accept Duel") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Duel","Confirm Duel" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Duel","Confirm Duel" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				PlayerActExecFunctions::execute_end(false);
			}
		}
		else if (replyString == "Accept Spar Request") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Spar","Confirm Spar" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Spar","Confirm Spar" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				PlayerActExecFunctions::execute_end(false);
			}
		}
		state = 9;
	}
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
		    replyOptions[i][Topic] = curr_hero_topic;//sets the topic for reply
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
	std::string start_message = "";

	
	//if(quest_in_progress)
		//message = n->getName() + ": " + dialogue.gen_dialog({ "Quest_In_Progress","Quest_In_Progress" }, temp_hero);
	//else if(quest_complete)
	    //message = n->getName() + ": " + dialogue.gen_dialog({ "Quest_Complete","Quest_Complete"},temp_hero);
	//else

	/*handles what the greeting phrase should be based on whether or not the player
	has taken or completed a quest from the npc*/
	if (temp_hero = CheckClass::isHero(other)) {
		Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
		if (planner->quests_given.size() == 1)//Bad! Check boolean in Action object instead.
			message = n->getName() + ": " + dialogue.gen_dialog({ "Quest_In_Progress","Quest_In_Progress" }, temp_hero);
		else if (planner->quests_given.size() > 1)
			message = n->getName() + ": " + dialogue.gen_dialog({ "Quest_Complete","Quest_Complete" }, temp_hero);
		else
			message = n->getName() + ": " + dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero);
	}
	else
		message = n->getName() + ": " + dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero);
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

	/*does normal exitDialogue stuff if "other" is not a hero*/
	if (state == 7 || state == 9) {
		other = nullptr;
		state = 0;
		DialogueController::scroll_control = 0;
		DialogueController::quest_declined = false;

		for (int i = 0; i < curr_conversation_log.size(); i++) {

			//delete memory allocated for instance of Memory class here
			//delete tmp_top.second;
			//delete memory allocated for conversation log object here
			if (curr_conversation_log[i] != nullptr)
				delete curr_conversation_log[i];
		}

		curr_conversation_log.clear();

		remove_hero_related_conv_points();
		first_call = true;
	}
	else {
		Hero* temp_hero;
		if (temp_hero = CheckClass::isHero(other)) {//check if "other" is a hero before seeing if they can offer you a quest
			if (offer_quest_on_exit(temp_hero) == false || quest_declined == true) {
				/*does normal exitDialogue stuff if quest is not given or if player has denied quest offer*/
				state = 7;
			}

		}
	}
	
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

	point[ConvPointName]="give_quest_hack";
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
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Ask About",0) != string::npos && itor->second->dpoint[CorrespondingConvPt] == "") {
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[Topic] = dialogue.int_to_hero_name(heroes_player_knows[j]);
					options[QuestionMarkIcon].push_back(tmp_dpoint);
					dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].push_back(tmp_dpoint);
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
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Advise To", 0) != string::npos && itor->second->dpoint[CorrespondingConvPt] == "") {
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[Topic] = dialogue.int_to_hero_name(heroes_player_knows[j]);
					options[NotorietyIcon].push_back(tmp_dpoint);
					dialogue.get_possible_conv_pts_ref()[NotorietyIcon].push_back(tmp_dpoint);
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
	for (int i = 0; i < options[QuestionMarkIcon].size();) {
		if (options[QuestionMarkIcon][i][ConvPointName].find("Advise To", 0) != string::npos || options[QuestionMarkIcon][i][ConvPointName].find("Ask About", 0) != string::npos) {
			options[QuestionMarkIcon].erase(options[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible
	conversation points that are associated with the question mark icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].size();) {
		if (dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Advise To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Ask About", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].erase(dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points that are associated with the 
	notoriety icon from player's dialog options vector */
	for (int i = 0; i < options[NotorietyIcon].size();) {
		if (options[NotorietyIcon][i][ConvPointName].find("Advise To", 0) != string::npos || options[NotorietyIcon][i][ConvPointName].find("Ask About", 0) != string::npos) {
			options[NotorietyIcon].erase(options[NotorietyIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible 
	conversation points that are associated with the notoriety icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[NotorietyIcon].size();) {
		if (dialogue.get_possible_conv_pts_ref()[NotorietyIcon][i][ConvPointName].find("Advise To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[NotorietyIcon][i][ConvPointName].find("Ask About", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[NotorietyIcon].erase(dialogue.get_possible_conv_pts_ref()[NotorietyIcon].begin() + i);
		}
		else
			++i;
	}
}

/*Updates the number_of_times_said field for the ConversationLogObj arg
that is passed in and updates the number_of_times_said field for any
ConversationLogObj in the conversation log vector that has a pointer
to the same conversation point as the arg.*/
/*void DialogueController::update_num_duplicate(ConversationLogObj* conv_log_entry) {
	for (int i = 0; i < curr_conversation_log.size() - 1; ++i) {
		if ((curr_conversation_log[i]->get_conv_point() == conv_log_entry->get_conv_point())
			&& (curr_conversation_log[i]->get_topic() == conv_log_entry->get_topic())
			&& (curr_conversation_log[i]->get_who() == conv_log_entry->get_who()))
		{

		}
	}
}*/

/*Replaces all appearances of "from" in "str" with "to"*/
void DialogueController::replace_all(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

/*Called in exitDialogue() function. Returns true if the NPC offers the player
a quest when they try to exit dialogue, but returns false if an NPC decides not
to give the player a quest because they either don't want to or because the
player is already working on a quest for that NPC.*/
bool DialogueController::offer_quest_on_exit(Hero* temp_hero) {
	bool offered_quest = false;
	Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
	/////////////////////////////////////////////////////////////////////////
	/*Stand in stuff for checking if NPC wants to give player quest when player
	is about to exit conversation. Currently, NPC will always give player a quest
	when they try to exit conversation if the player has not already accepted a quest.*/
	/////////////////////////////////////////////////////////////////////////
	if (dialogue.give_quest() && AIController::quest_response(temp_hero,player)) {
		bool has_quest = false;
		for (int i = 0; i < planner->quests_given.size(); ++i) {
			if (planner->quests_given[i]->getDoer()->name == SHANGO && planner->quests_given[i]->executed == false)
				has_quest = true;
		}
		//if (planner->quests_given.size() > 0)//stand in Bad!
			//has_quest = true;//stand in Bad! dont wanna be checking the size of quest vector
		if (has_quest == false && quest_declined == false) {

			dialogue_point reply_diog_pt = { "Exit Quest","Exit Quest" };
			dialogue_point con_diog_pt = { "Offer_Quest","Offer_Quest" };
			std::string reply_pt_sentence = dialogue.gen_dialog(reply_diog_pt, temp_hero);
			std::string con_pt_sentence = dialogue.gen_dialog(con_diog_pt, temp_hero);
			Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
			DialogueController::quest = planner->get_current_action();
			replace_all(con_pt_sentence, "HERO", dialogue.int_to_hero_name(quest->getReceiver()->name));//receiver or doer here? ask Justin

																										//these two lines strip the number off the end of the name 
			std::string::size_type name_end = quest->name.find_last_of('_');
			std::string act_name = quest->name.substr(0, name_end);

			replace_all(con_pt_sentence, "ACTION", act_name);

			message = other->getName() + ": " + reply_pt_sentence + "\n" + con_pt_sentence;
			replyOptions = dialogue.get_possible_reply_pts("Offer_Quest", optionsIndex);

			select = 0;
			state = 2;
			offered_quest = true;
			//planner->quests_given.push_back(planner->get_current_action());
		}
	}
	return offered_quest;
	
}

void DialogueController::create_farewell() {
	dialogue_point diog_pt = { "Farewell","Farewell" };
	Hero* temp_hero = CheckClass::isHero(DialogueController::other);
	std::string farewell_sentence = DialogueController::getDialogueHelper()->gen_dialog(diog_pt, temp_hero);
	DialogueController::message = DialogueController::other->getName() + ": " + farewell_sentence + "\n\n";
}
