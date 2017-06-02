#include "stdafx.h"
#include "DialogueController.h"
#include "CheckClass.h"
#include "ConversationPoint.h"
#include "Tag.h"
#include "ConversationLogObj.h"
#include "ActionExecFunctions.h"
#include "Tutorial.h"



//to keep you from repeatedly talking to shrines 
bool DialogueController::talked_to_shrine_o = false;
bool DialogueController::talked_to_shrine_j = false;
bool DialogueController::talked_to_shrine_m = false;

//to keep you from repeatedly getting divination from babalawos 
bool DialogueController::talked_to_babalawo_o = false;
bool DialogueController::talked_to_babalawo_j = false;
bool DialogueController::talked_to_babalawo_m = false;

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
constexpr int IsSelectable = 4;
constexpr int IsHeroReply = 5;

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
std::vector<std::vector<dialogue_point>> DialogueController::soldier_options;
std::vector<std::vector<dialogue_point>> DialogueController::babalawo_options;
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
std::vector<ConversationLogObj*> DialogueController::curr_conversation_log;

/*used for passing player's conversation point selection to 

esponse() function when state is no longer 5 in 
PlayerConversationPoint() function*/
std::string player_conv_point_choice = ""; 

//keeps track of the topic of the current conversation cycle
std::string curr_hero_topic = "";

//keeps track of what heroes the player knows(2=Yemoja and 3=Oya)
//Is placeholder that will eventually be gotten rid of
//std::vector<int> DialogueController::heroes_player_knows = {2,3};

//keep add_hero_conv_points() function to one call per conversation
bool first_call = true;

bool DialogueController::quest_declined = false;

ConversationLogObj* DialogueController::entry = nullptr;

bool DialogueController::started_conv = false;
bool DialogueController::quited_gui = false;

bool DialogueController::first_q_press = false;
bool DialogueController::took_advice = false;

int DialogueController::shrine_talk_counter = 0;
int DialogueController::teach_move_counter = 0;

bool DialogueController::first_buff = true;

bool DialogueController::is_hero_act = false;

Action* DialogueController::hero_act_toward_player = nullptr;


DialogueController::DialogueController()
{
	srand(time(0));//seeds rand function to ensure good variety of random numbers
}


DialogueController::~DialogueController()
{
}

/*Gets all of the player's conversation point dialog options and sets
the conversation state to wait for the player to select a conversation
point*/
void DialogueController::PlayerChoose()
{
	Hero* temp_hero = CheckClass::isHero(other);
	if (temp_hero) {
		player->filter_move_to(temp_hero);
		//set_selectable(false,"Bribe",AffinityIcon);
		unselectable_to_bottom();
	}

	options = dialogue.get_possible_conv_pts();
	if (temp_hero) {
		remove_dialog_option("Ask_To_Duel",NotorietyIcon);
		remove_dialog_option("Ask_To_Spar", StrengthIcon);
		add_dialog_option("Ask_To_Duel",NotorietyIcon);
		add_dialog_option("Ask_To_Spar",StrengthIcon);

		if(temp_hero->rel[player->name]->getAffinity() <= 30 && temp_hero->rel[player->name]->getStrength() <= 60)
		    set_selectable(true, "Ask_To_Duel",NotorietyIcon);
		else
			set_selectable(false, "Ask_To_Duel", NotorietyIcon);

		if(temp_hero->rel[player->name]->getStrength() >= 50 && temp_hero->rel[player->name]->getAffinity() <= 85 && temp_hero->rel[player->name]->getNotoriety() <= 75)
			set_selectable(true, "Ask_To_Spar", StrengthIcon);
		else
			set_selectable(false, "Ask_To_Spar", StrengthIcon);

		if(temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance())
			set_selectable(true, "Recruit_For_Party", StrengthIcon);
		else
			set_selectable(false, "Recruit_For_Party", StrengthIcon);

		if (temp_hero->rel[player->name]->getAffinity() + (player->ori / 10) >= 60 &&
			temp_hero->rel[player->name]->getStrength() + (player->ori / 10) >= 50)
			set_selectable(true, "Request_Teaching", StrengthIcon);
		else
			set_selectable(false, "Request_Teaching", StrengthIcon);

		if (temp_hero->rel[player->name]->getAffinity() >= 85)
			set_selectable(true, "Ask_To_Form_Alliance", AffinityIcon);
		else
			set_selectable(false, "Ask_To_Form_Alliance", AffinityIcon);

		unselectable_to_bottom();
		options = dialogue.get_possible_conv_pts();


	}

	if (first_call) {
		/*add "Ask_About" and "Advise_To" and "Ask For Quest" conversation points to player's
		dialog options if they are speaking to a hero*/
		Hero* tmp_hero = CheckClass::isHero(other);
		if (tmp_hero != nullptr) {
			add_hero_related_conv_points();
			//add_ask_for_quest();
		}
	}
	first_call = false;
	state = 1;
}

void DialogueController::player_choose_soldier()
{
	
	Soldier* soldier;
	soldier = dynamic_cast<Soldier*>(other);

	//prevents player from entering dialog with enemy soldier
    //since they can neither be recruited for player's party
	//or be removed from the player's party
	vector<Party*> player_curr_enemies = player->getParty()->getCurrentEnemies();
	for (int i = 0; i < player_curr_enemies.size(); ++i) {
		if (player_curr_enemies[i] == soldier->getParty()) {
			state = 0;
			return;
		}
	}

	//options = dialogue.get_possible_conv_pts();
	for (int i = 0; i < Containers::conv_point_table.size(); i++)
	{
	    soldier_options.push_back({});
	}
	if(soldier->getCurrentLeader() == player)
		soldier_options[StrengthIcon].push_back({ "Remove_From_Party","Remove_From_Party","","","1"});
	else
	    soldier_options[StrengthIcon].push_back({"Recruit_For_Party","Recruit_For_Party","","","1"});
	
	state = 1;
}

void DialogueController::player_choose_babalawo()
{

	//options = dialogue.get_possible_conv_pts();
	for (int i = 0; i < Containers::conv_point_table.size(); i++)
	{
		babalawo_options.push_back({});
	}
	babalawo_options[StrengthIcon].push_back({ "Ask For Divination","Ask For Divination","","","1" });
    babalawo_options[StrengthIcon].push_back({ "Inquire About Ifa","Inquire About Ifa","","","1" });

	state = 1;
}

/*Is called instead of player_choose_soldier() and player_choose() functions if the player interacts with shrine.*/
void DialogueController::shrine_interact()
{
	if (other->getName().find("Oasis") != string::npos) 
	{
		if (DialogueController::talked_to_shrine_o) 
		{
			state = 0;
			return;
		}
	}else if (other->getName().find("Jungle") != string::npos)
	{
		if (DialogueController::talked_to_shrine_j)
		{
			state = 0;
			return;
		}
	}else if (other->getName().find("Mountain") != string::npos)
	{
		if (DialogueController::talked_to_shrine_m)
		{
			state = 0;
			return;
		}
	}

	dialogue_point dpoint;
	switch (shrine_talk_counter) {
	case 0:
		dpoint = {"Shrine Talk 1","Shrine Talk 1"};
		break;
	case 1:
		dpoint = {"Shrine Talk 2","Shrine Talk 2"};
		break;
	case 2:
		dpoint = {"Shrine Talk 3","Shrine Talk 3"};
		break;
	case 3:
		dpoint = {"Shrine Talk 4","Shrine Talk 4"};

		//give shrine blessing
		player->addHealth(300);//regenerate to full health
		player->ori+= 30;//boost ori by 30
		//Containers::hero_table["Shango"]->setAse;//regenerate to full ase

		for (auto hero : Containers::hero_table) 
		{
			if (hero.second->name != SHANGO) {
				if (other->getName().find("Oasis") != string::npos) {
					hero.second->rel[SHANGO]->addAffinity(10);
					DialogueController::talked_to_shrine_o = true;

				}
				else if ((other->getName().find("Jungle")) != string::npos) {
					hero.second->rel[SHANGO]->addNotoriety(10);
					DialogueController::talked_to_shrine_j = true;
				}
				else if ((other->getName().find("Mountain")) != string::npos) {
					hero.second->rel[SHANGO]->addStrength(10);
					DialogueController::talked_to_shrine_m = true;
					player->can_activate_ex = 1;
				}
			}	
		}
		
		break;
	}
	
	//checks if some stat is high enough to speak to this particular shrine
	if (other->getName().find("Oasis") != string::npos) {
		if (Containers::hero_table["Yemoja"]->rel[SHANGO]->getAffinity() < 70)
			dpoint = {"Shrine Not Worthy", "Shrine Not Worthy"};
	}
	else if ((other->getName().find("Jungle")) != string::npos) {
		if (Containers::hero_table["Oya"]->rel[SHANGO]->getNotoriety() < 70)
			dpoint = { "Shrine Not Worthy", "Shrine Not Worthy" };
	}
	else if ((other->getName().find("Mountain")) != string::npos) {
		if (Containers::hero_table["Ogun"]->rel[SHANGO]->getStrength() < 70)
			dpoint = { "Shrine Not Worthy", "Shrine Not Worthy" };
	}

	std::string conversation_pt_sentence = dialogue.gen_dialog_shrine(dpoint, other);
	message = other->getName() + ": " + conversation_pt_sentence;
	if (shrine_talk_counter == 3 || dpoint[ConvPointName] == "Shrine Not Worthy")
		state = 7;
	else
	    state = 11;
}


void DialogueController::villager_interact() {
	dialogue_point dpoint = { other->getName(), other->getName() };
	std::string conversation_pt_sentence = dialogue.gen_dialog_villager(dpoint, other);
	message = other->getName() + ": " + conversation_pt_sentence;
	state = 7;
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

		//add conversation point to NPC's permanent conversation log storage
		ConversationLogObj* perm_log_entry = new ConversationLogObj();
		perm_log_entry->set_who(conv_log_obj->get_who());
		perm_log_entry->set_topic(conv_log_obj->get_topic().first, conv_log_obj->get_topic().second);
		perm_log_entry->set_conv_point(conv_log_obj->get_conv_point());

		entry = perm_log_entry;
		

		//limit the number of conversation log entries for the current conversation
		//to a maximum of 8
		if (curr_conversation_log.size() > 8) {
			delete curr_conversation_log[0];
			curr_conversation_log.erase(curr_conversation_log.begin());
		}
		player_conv_point_choice = choice[ConvPointName];

		Hero* temp_hero = CheckClass::isHero(other);

		/*handles applying of post conditions for select conversation
		points and checking of whether or not an action has been completed.*/

		//Eron's Change: checks if action_accepted for  spar, bribe, and form alliance but doesn't impliment post conditions for them
		if (player_conv_point_choice == "Bribe"||player_conv_point_choice == "Compliment"|| player_conv_point_choice == "Grovel"||
			player_conv_point_choice == "Insult"|| player_conv_point_choice == "Boast" || player_conv_point_choice == "Ask_To_Spar" ||
			player_conv_point_choice == "Ask_To_Duel" || player_conv_point_choice == "Ask_To_Form_Alliance" || player_conv_point_choice == "Advise To Fight"
			|| player_conv_point_choice == "Advise To Conquer" || player_conv_point_choice == "Advise To Send Peace Offering To" || 
			player_conv_point_choice == "Advise To Ally With" || player_conv_point_choice == "Intimidate") {
	
			accepted_action = true;
			if (player_conv_point_choice == "Advise To Fight"
				|| player_conv_point_choice == "Advise To Conquer" || player_conv_point_choice == "Advise To Send Peace Offering To" ||
				player_conv_point_choice == "Advise To Ally With") {
				accepted_action = check_advice_acceptance(player, temp_hero);
				if (temp_hero->SUGG_ACT_STATUS == 1)
					accepted_action = false;
			}
			for (auto precond : Containers::conv_point_table[player_conv_point_choice]->req_preconds) {
				int temp1 = precond->get_cost(temp_hero, player);
				//the ori stuff means that the higher the ori the more likely it is for the hero to respond
				//positivly to what whatever it is you are saying
				if (precond->get_cost(temp_hero,player) - (player->ori/ 10) <= 0) {
					std::cout << "a string: " << precond->get_cost(temp_hero, player) << std::endl;
				}
				else {
					accepted_action = false;
				}
			}
			if ((player_conv_point_choice == "Advise To Fight"
				|| player_conv_point_choice == "Advise To Conquer" || player_conv_point_choice == "Advise To Send Peace Offering To" ||
				player_conv_point_choice == "Advise To Ally With")&& accepted_action) {
				Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
				planner->set_action_suggested(true);

				
			}

			if (player_conv_point_choice == "Bribe" || player_conv_point_choice == "Compliment" || player_conv_point_choice == "Grovel" ||
				player_conv_point_choice == "Insult" || player_conv_point_choice == "Boast" || player_conv_point_choice == "Advise To Fight"
				|| player_conv_point_choice == "Advise To Conquer" || player_conv_point_choice == "Advise To Send Peace Offering To" ||
				player_conv_point_choice == "Advise To Ally With" || player_conv_point_choice == "Intimidate")
			{ 
				PlayerActExecFunctions::execute_start(player_conv_point_choice, temp_hero);
				accepted_action = check_acceptance(player, temp_hero);
				if (accepted_action) {
					Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
				}
				else {
					Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(false, player, temp_hero);
				}
			}
			
		}
		if (player_conv_point_choice == "Request_Teaching") {
			//the ori variable is to increase the chance of teaching based on
			//how high the ori is 
			if (temp_hero->rel[player->name]->getAffinity() + (player->ori / 10) >= 60 && 
				temp_hero->rel[player->name]->getStrength() + (player->ori / 10) >= 60)
				accepted_action = true;
			else
				accepted_action = false;
			//handles the case where the player has already learned this hero's skill
			//add more cases for more heros later
			if (player->can_fire && temp_hero->name == YEMOJA)//case where player already learned Yemoja's move
				accepted_action = false;
			if(player->can_spin && temp_hero->name == OYA)//case where player already learned Oya's move
				accepted_action = false;
		}
		state = 5;
	}
	else {
		state = 4;
		otherResponse(player_conv_point_choice, curr_hero_topic);
		add_to_perm_storage(entry);
		//adds hero to player's vector of known heroes if player asks name
		if (player_conv_point_choice == "Ask_Name") {
			bool already_know = false;
			for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
				if (dialogue.hero_name_to_int(DialogueController::getOther()->getName())
					== player->heroes_player_knows[i])
					already_know = true;
			}
			if(!already_know)
			    player->heroes_player_knows.push_back(dialogue.hero_name_to_int(other->getName()));
		}
		player_conv_point_choice = "";
	}
}

void DialogueController::player_conversation_point_soldier()
{
	dialogue_point choice;

	/*prevents the player's selection of the "Next" option from being stored
	in the log for the current conversation. Uses the fact that we know
	that the player's conversation point choice will not be empty if
	they have reached the state with the "Next" option.*/
	if (player_conv_point_choice == "") {
		//capture player's selection
		choice = soldier_options[optionsIndex][select + DialogueController::scroll_control];

		//get a sentence to say based on their option selection
		std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);

		/*adds the hero's name to the end of the sentence if the conversation
		point is hero-related, or adds an empty string if it is not. The value
		at choice[Topic()] will be one of these depending on the conversation
		point option selected.*/
		replace_all(conversation_pt_sentence, "HERO", choice[Topic]);

		message = player->getName() + ": " + conversation_pt_sentence;

		/*stores the player's conversation point(choice[ConvPointName()]) in a log entry
		and that entry gets stored in the log for the current conversation.
		We use index 1 of choice because that is where the name of the
		conversation point is kept.*/
		/*ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;

		conv_log_obj->set_who(1);
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[ConvPointName]]);
		conv_log_obj->update_number_of_times_said();

		/*set the topic for the log entry of the player's selection.
		If player's selection has no topic, the topic is set to a value
		that indicates that there is no topic asscoiated with their
		conversation point.
		if (choice[ConvPointName].find("Advise To") != string::npos || choice[ConvPointName].find("Ask About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[Topic]), mem);
			curr_hero_topic = choice[Topic];
		}
		else
			conv_log_obj->set_topic(NoTopic, mem);

		curr_conversation_log.push_back(conv_log_obj);//add entry to log*/

		player_conv_point_choice = choice[ConvPointName];

		/*Hero* temp_hero = nullptr;
		if (other->getType() >= WorldObj::TYPE_NPC) {
			if (temp_hero = CheckClass::isHero(other))//added another equals was single equals before
			{
				perror("you cannot talk to this type of object");
			}
		}
		else {
			return;
		}*/

		/*handles applying of post conditions for relationship related conversation
		points. I also thought to incorporate checks for if a player completed an action
		by doing any of these here, but this is probably not a good place.*/
		/*if (player_conv_point_choice == "Bribe") {
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
		}*/
		state = 5;
	}
	else {
		state = 4;
		other_response_soldier(player_conv_point_choice, curr_hero_topic);

		player_conv_point_choice = "";
	}
}

void DialogueController::player_conversation_point_babalawo()
{
	dialogue_point choice;

	/*prevents the player's selection of the "Next" option from being stored
	in the log for the current conversation. Uses the fact that we know
	that the player's conversation point choice will not be empty if
	they have reached the state with the "Next" option.*/
	if (player_conv_point_choice == "") {
		//capture player's selection
		choice = babalawo_options[optionsIndex][select + DialogueController::scroll_control];

		//get a sentence to say based on their option selection
		std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);

		/*adds the hero's name to the end of the sentence if the conversation
		point is hero-related, or adds an empty string if it is not. The value
		at choice[Topic()] will be one of these depending on the conversation
		point option selected.*/
		replace_all(conversation_pt_sentence, "HERO", choice[Topic]);

		message = player->getName() + ": " + conversation_pt_sentence;

		/*stores the player's conversation point(choice[ConvPointName()]) in a log entry
		and that entry gets stored in the log for the current conversation.
		We use index 1 of choice because that is where the name of the
		conversation point is kept.*/
		/*ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;

		conv_log_obj->set_who(1);
		conv_log_obj->set_conv_point(Containers::conv_point_table[choice[ConvPointName]]);
		conv_log_obj->update_number_of_times_said();

		/*set the topic for the log entry of the player's selection.
		If player's selection has no topic, the topic is set to a value
		that indicates that there is no topic asscoiated with their
		conversation point.
		if (choice[ConvPointName].find("Advise To") != string::npos || choice[ConvPointName].find("Ask About") != string::npos) {
		conv_log_obj->set_topic(dialogue.hero_name_to_int(choice[Topic]), mem);
		curr_hero_topic = choice[Topic];
		}
		else
		conv_log_obj->set_topic(NoTopic, mem);

		curr_conversation_log.push_back(conv_log_obj);//add entry to log*/

		player_conv_point_choice = choice[ConvPointName];

		/*Hero* temp_hero = nullptr;
		if (other->getType() >= WorldObj::TYPE_NPC) {
		if (temp_hero = CheckClass::isHero(other))//added another equals was single equals before
		{
		perror("you cannot talk to this type of object");
		}
		}
		else {
		return;
		}*/

		/*handles applying of post conditions for relationship related conversation
		points. I also thought to incorporate checks for if a player completed an action
		by doing any of these here, but this is probably not a good place.*/
		/*if (player_conv_point_choice == "Bribe") {
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
		}*/
		state = 5;
	}
	else {
		state = 4;
		other_response_babalawo(player_conv_point_choice, curr_hero_topic);

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
		/*if (prompted_quest)
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

		}*/
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
				player->quests_log.push_back(quest);
				planner->quests_given.push_back(quest); //gives npc record of what they gave player

				//player->cur_action = quest; //gives player record of what they are doing
				first_q_press = false;//make sure player can still quit GUI if they accepted a quest when they were about to exit already

			}
			if (choice[ConvPointName] == "Decline_Quest") {
				quest_declined = true;
				state = 10;
			}

		}
		if (choice[1] == "Boast In Response" || choice[1] == "Intimidate In Response" || choice[1] == "Insult In Response" || choice[1] == "Compliment In Response" || choice[1] == "Offer Praise In Response") {
			std::string::size_type reply_end = choice[1].find_last_of(' ');
			std::string act_name = choice[1].substr(0, reply_end);
			reply_end = act_name.find_last_of(' ');
			act_name = choice[1].substr(0, reply_end);

			bool react_positively = true; 
			for (auto precond : Containers::conv_point_table[act_name]->req_preconds) {
				int temp1 = precond->get_cost(temp_hero, player);
				//the ori stuff means that the higher the ori the more likely it is for the hero to respond
				//positivly to what whatever it is you are saying
				if (precond->get_cost(temp_hero, player) - (player->ori / 10) <= 0) {
					std::cout << "a string: " << precond->get_cost(temp_hero, player) << std::endl;
				}
				else {
					react_positively = false;
				}
				if (react_positively) {
					Containers::conv_point_table[act_name]->apply_postconditions(true,player,temp_hero);
				}
				else {
					Containers::conv_point_table[act_name]->apply_postconditions(false, player, temp_hero);
				}

				
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

		//add conversation point to NPC's permanent conversation log storage
		ConversationLogObj* perm_log_entry = new ConversationLogObj();
		perm_log_entry->set_who(conv_log_obj->get_who());
		perm_log_entry->set_topic(conv_log_obj->get_topic().first, conv_log_obj->get_topic().second);
		perm_log_entry->set_conv_point(conv_log_obj->get_conv_point());
		add_to_perm_storage(perm_log_entry);

		//limit the number of conversation log entries for the current conversation
		//to a maximum of 8
		if (curr_conversation_log.size() > 8) {
			delete curr_conversation_log[0];
			curr_conversation_log.erase(curr_conversation_log.begin());
		}

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
			if(is_hero_act)
				apply_post_from_response(choice[ConvPointName], hero_act_toward_player);
		}
		else if(state != 10 && is_hero_act == false)//move to exit dialogue if player declined a quest
		    PlayerChoose();//start all over from player conversation point again
		else if(is_hero_act) {
			apply_post_from_response(choice[ConvPointName],hero_act_toward_player);
			state = 7;
		}

	}
	else {
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

		if (player_conv_point_choice == "Accept Alliance Offer") {
			dialogue_point diog_pt = {"Confirm Alliance","Confirm Alliance"};
			std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
			message = check_if_known(reply_pt_sentence, "");
			PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);
		}
		else if (player_conv_point_choice == "Accept Duel") {
			dialogue_point diog_pt = { "Confirm Duel","Confirm Duel"};
			std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
			message = check_if_known(reply_pt_sentence, "");
			PlayerActExecFunctions::execute_start("Duel", temp_hero);
		}
		else if (player_conv_point_choice == "Accept Spar Request") {
			dialogue_point diog_pt = {"Confirm Spar","Confirm Spar" };
			std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
			message = check_if_known(reply_pt_sentence, "");
			PlayerActExecFunctions::execute_start("Spar", temp_hero);
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
	log for the current conversation. The reply point is line[ConvPointName] and the
	conversation point is point[ConvPointName].*/
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

		//add conversation point to NPC's permanent conversation log storage
		ConversationLogObj* perm_log_entry = new ConversationLogObj();
		perm_log_entry->set_who(conv_log_obj->get_who());
		perm_log_entry->set_topic(conv_log_obj->get_topic().first, conv_log_obj->get_topic().second);
		perm_log_entry->set_conv_point(conv_log_obj->get_conv_point());
		add_to_perm_storage(perm_log_entry);

		//limit the number of conversation log entries for the current conversation
		//to a maximum of 8
		if (curr_conversation_log.size() > 8) {
			delete curr_conversation_log[0];
			curr_conversation_log.erase(curr_conversation_log.begin());
		}
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
			conv_log_obj2->set_topic(quest->getReceiver()->name, mem2);

			//these two lines strip the number off the end of the name 
			std::string::size_type name_end = quest->name.find_last_of('_');
			std::string act_name = quest->name.substr(0, name_end);

			std::string village = "'s village";
			std::string hero_name = dialogue.int_to_hero_name(quest->getReceiver()->name);

			player->quest_status[quest->getOwner()->name] = 1;// set shango to "doing quest"

			if (act_name.find("Conquer") != string::npos || act_name.find("Occupy") != string::npos) {
				replace_all(con_pt_sentence, "HERO", hero_name + village);
			}
			else
			    replace_all(con_pt_sentence, "HERO", hero_name);//receiver or doer here? ask Justin


			std::string with = "";
			if (act_name.find("Train") != string::npos || act_name.find("Spar") != string::npos || act_name.find("Form_Alliance") != string::npos) {
				with = " with ";
				replace_all(con_pt_sentence, "ACTION", act_name + with);
			}
			else
			    replace_all(con_pt_sentence, "ACTION", act_name + with);
			

		}
	    else
			conv_log_obj2->set_topic(NoTopic, mem2);

	    curr_conversation_log.push_back(conv_log_obj2);

		//add conversation point to NPC's permanent conversation log storage
		ConversationLogObj* perm_log_entry2 = new ConversationLogObj();
		perm_log_entry2->set_who(conv_log_obj2->get_who());
		perm_log_entry2->set_topic(conv_log_obj2->get_topic().first, conv_log_obj2->get_topic().second);
		perm_log_entry2->set_conv_point(conv_log_obj2->get_conv_point());
		add_to_perm_storage(perm_log_entry2);

		//limit the number of conversation log entries for the current conversation
		//to a maximum of 8
		if (curr_conversation_log.size() > 8) {
			delete curr_conversation_log[0];
			curr_conversation_log.erase(curr_conversation_log.begin());
		}
    }
	


	/*skips the player's reply point if the npc does not say a conversation
	point, if the npc tells the player that they already asked them something,
	if an npc runs out of relevant conversation points to say, or if an NPC tells
	the player that they do not have a quest for them.
	*/
	if (point[ConvPointName] != "No_More_Phrases" && line[ConvPointName] != "Already_Asked" && point[ConvPointName] != "" && point[ConvPointName] != "No Quest") {
		state = 2;
		message = check_if_known(reply_pt_sentence, con_pt_sentence);
		replyOptions = dialogue.get_possible_reply_pts(point[ConvPointName], optionsIndex);
	}
	else {
		if (point[ConvPointName] == "No Quest") {
			dialogue_point dp = { "No Quest","No Quest" };
			con_pt_sentence = dialogue.gen_dialog(dp, temp_hero);
		}
		else
			con_pt_sentence = "";
		message = check_if_known(reply_pt_sentence, con_pt_sentence);
		state = 1;//skip player reply if npc cannot give a conversation point
	}
	select = 0;
	DialogueController::scroll_control = 0;
}

void DialogueController::other_conversation_point_soldier(dialogue_point line)
{
	Hero* temp_hero = nullptr;
	/*if (other->getType() >= WorldObj::TYPE_NPC) {
		if (temp_hero = CheckClass::isHero(other))//added another equals was single equals before
		{
			perror("you cannot talk to this type of object");
		}
	}
	else {
		return;
	}*/

	dialogue_point point = dialogue.choose_conv_pt(curr_conversation_log, temp_hero, player);

	/*Only sets the topic of the npc's conversation point if it is not
	a special case. Special case dialogue points are typically only
	of size 2.*/
	if (point[0] != "No_More_Phrases" && point[0] != "Already_Asked" && point.size() >= 4)
		point[Topic] = curr_hero_topic;

	/*handles special case of quest conversation point by making
	sure it's dialogue point will be the same size as the basic
	conversation points like "Ask_Name" etc.*/
	/*if (point[ConvPointName].find("Quest") != string::npos) {
		point.push_back("");
		point.push_back("");
	}*/

	replyString = point[ConvPointName];

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);

	/*Stores the npc's conversation and reply points as entries in the
	log for the current conversation. The reply point is line[ConvPointName()] and the
	conversation point is point[ConvPointName()].*/
	/* if (line[ConvPointName] != "Already_Asked") {
		ConversationLogObj* conv_log_obj = new ConversationLogObj();
		Memory* mem = nullptr;

		//initialization of conversation log entry for reply point
		conv_log_obj->set_who(dialogue.hero_name_to_int(other->getName()));
		conv_log_obj->set_conv_point(Containers::conv_point_table[line[ConvPointName]]);
		conv_log_obj->update_number_of_times_said();

		/*insert the topic at the beginning of the npc's reply point sentence
		if they are replying to a hero-related conversation point.*/
		/*if (line[ConvPointName].find("Take Advice") != string::npos || line[ConvPointName].find("Tell About") != string::npos) {
			conv_log_obj->set_topic(dialogue.hero_name_to_int(line[Topic]), mem); //make the topic Oya if the player selected a move to action
			replace_all(reply_pt_sentence, "HERO", line[Topic]);
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
		//if (point[ConvPointName].find("Advise To") != string::npos || point[ConvPointName].find("Ask About") != string::npos) {
		//	conv_log_obj2->set_topic(dialogue.hero_name_to_int(point[Topic]), mem2);
		//	replace_all(con_pt_sentence, "HERO", point[Topic]);
		//}
		//else if (point[ConvPointName].find("Offer_Quest") != string::npos) {
			//Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
			//DialogueController::quest = planner->get_current_action();
			//conv_log_obj2->set_topic(quest->getReceiver()->name, mem2);

			//these two lines strip the number off the end of the name 
			//std::string::size_type name_end = quest->name.find_last_of('_');
			//std::string act_name = quest->name.substr(0, name_end);

			//std::string village = "'s village";
			//std::string hero_name = dialogue.int_to_hero_name(quest->getReceiver()->name);
			//if (act_name.find("Conquer") != string::npos || act_name.find("Occupy") != string::npos) {
			//	replace_all(con_pt_sentence, "HERO", hero_name + village);
			//}
			//else
				//replace_all(con_pt_sentence, "HERO", hero_name);//receiver or doer here? ask Justin


			//std::string with = "";
			//if (act_name.find("Train") != string::npos || act_name.find("Spar") != string::npos || act_name.find("Form_Alliance") != string::npos) {
			//	with = " with ";
			//	replace_all(con_pt_sentence, "ACTION", act_name + with);
		//	}
			//else
			//	replace_all(con_pt_sentence, "ACTION", act_name + with);


	//	}
		//else
		//	conv_log_obj2->set_topic(NoTopic, mem2);

		//curr_conversation_log.push_back(conv_log_obj2);
	//} 

	message = other->getName() + ": " + reply_pt_sentence + "\n" + con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[ConvPointName], optionsIndex);

	select = 0;

	/*skips the player's reply point if the npc does not say a conversation
	point, if the npc tells the player that they already asked them something,
	or if an npc runs out of relevant conversation points to say.
	*/
	//if (point[ConvPointName] != "No_More_Phrases" && point[ConvPointName] != "Already_Asked" && point[ConvPointName] != "" && point[ConvPointName] != "No Quest")
		//state = 2;
	//else
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

	if (state != 8 && state != 12 && state != 7) {
		dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log,temp_hero);
		replyString = line[ConvPointName];

		/*avoids setting a topic when npc replies with "You already asked me that"
		 or if npc says any other special case reply. Special case replies are
		 typically vectors with a size of only 2.*/
		if (line.size() >= 4)
			line[Topic] = hero_topic;


		if (replyString == "Accept Alliance Offer") {
			//calls action start if the question is asked at all
			PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = check_if_known(reply_pt_sentence,"");
			} else{
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer","",curr_hero_topic,"1"};
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				message = check_if_known(reply_pt_sentence, "");
			}
			
			state = 8;
		}
		else if (replyString == "Accept Duel") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Duel", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Duel","Accept Duel","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				message = check_if_known(reply_pt_sentence, "");

			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Duel","Accept Duel","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = check_if_known(reply_pt_sentence, "");
			}

			state = 8;
		}
		else if (replyString == "Accept Spar Request") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Spar Request","Accept Spar Request","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = check_if_known(reply_pt_sentence, "");

				//state = 8;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Spar Request","Accept Spar Request","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				message = check_if_known(reply_pt_sentence, "");

				//state = 1;
			}
			state = 8;
		}
		else if (replyString == "Take Advice To Fight") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Take Advice To Fight","Take Advice To Fight","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence,"HERO",curr_hero_topic);
				message = check_if_known(reply_pt_sentence,"");

				//state = 8;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Take Advice To Fight","Take Advice To Fight","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");

				//state = 1;
			}
			state = 8;
		}
		else if (replyString == "Take Advice To Conquer") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Take Advice To Conquer","Take Advice To Conquer","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");

				//state = 8;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Take Advice To Conquer","Take Advice To Conquer","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");

				//state = 1;
			}
			state = 8;
		}
		else if (replyString == "Take Advice To Send Peace Offering To") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Take Advice To Send Peace Offering To","Take Advice To Send Peace Offering To","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");

				//state = 8;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Take Advice To Send Peace Offering To","Take Advice To Send Peace Offering To","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");

				//state = 1;
			}
			state = 8;
		}
		else if (replyString == "Take Advice To Ally With") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Take Advice To Ally With","Take Advice To Ally With","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Take Advice To Ally With","Take Advice To Ally With","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
			}
			state = 8;
		}
		else if (replyString == "Teach") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Teach","Teach","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				dynamic_cast<Hero*>(other)->rel[1]->addStrength(10);
				//state = 12;
				
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt;
				if((temp_hero->name == YEMOJA && player->can_fire) || (temp_hero->name == OYA && player->can_spin))
					diog_pt = { "Already Taught","Already Taught","",curr_hero_topic,"1" };
				else
				    diog_pt = { "Teach","Teach","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				//state = 8;
			}
			state = 8;
		}

		else if (replyString == "Accept Bribe") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Bribe", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Bribe","Accept Bribe","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Bribe","Accept Bribe","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(false);
			}
			state = 3;
			otherConversationPoint(line);
		}

		else if (replyString == "Defend Self") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Insult", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Defend Self","Defend Self","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Defend Self","Defend Self","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(false);
			}
			state = 3;
			otherConversationPoint(line);
		}

		else if (replyString == "Thank") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Compliment", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Thank","Thank","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Thank","Thank","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			state = 3;
			otherConversationPoint(line);
		}
		else if (replyString == "Congratulate") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Boast", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Congratulate","Congratulate","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Congratulate","Congratulate","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(false);
			}
			state = 3;
			otherConversationPoint(line);
		}
		else if (replyString == "Accept Plea") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Grovel", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Plea","Accept Plea","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Plea","Accept Plea","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(false);
			}
			state = 3;
			otherConversationPoint(line);
		}
		else if (replyString == "Talk Back") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Intimidate", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt = { "Intimidate","Intimidate","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(true);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Intimidate","Intimidate","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				PlayerActExecFunctions::execute_end(false);
			}
			state = 3;
			otherConversationPoint(line);
		}
		else if (replyString == "Response_Recruit_For_Party") {
			if (temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance()) {
				player->getVillage()->barracks->addToParty(temp_hero, false);
				//soldier->getParty()->setAlliance(player->getParty()->getAlliance());
				temp_hero->setCurrentLeader(player);
				temp_hero->setParty(player->getParty());
				std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);

				//adds all of the hero's party members to the player's party
				std::vector<Soldier*> heroes_soldiers = temp_hero->getParty()->getMembers();
				for (int i = 0; i < heroes_soldiers.size(); ++i) {
					player->getVillage()->barracks->addToParty(heroes_soldiers[i], false);
					heroes_soldiers[i]->setCurrentLeader(player);
					heroes_soldiers[i]->setParty(player->getParty());
				}

			}
			else { //they will say no if not part of same alliance as you
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(line, temp_hero);
			}
			state = 7;
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
				dialogue_point diog_pt = { "Confirm Alliance","Confirm Alliance","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////

				dialogue_point diog_pt = { "Confirm Alliance","Confirm Alliance","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Accept Duel") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Duel","Confirm Duel","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
				PlayerActExecFunctions::execute_start("Duel", temp_hero);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Duel","Confirm Duel","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				//PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Accept Spar Request") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Spar","Confirm Spar","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
				PlayerActExecFunctions::execute_start("Spar", temp_hero);
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Spar","Confirm Spar","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				//PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Take Advice To Fight") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Fight","Confirm Fight","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
				//ActionPool* hero_map;
				//hero_map = temp_hero->actionPool_map[dialogue.hero_name_to_int(curr_hero_topic)];
				int hero_num = dialogue.hero_name_to_int(curr_hero_topic);
				//std::string hero_id = std::to_string(hero_num);
				std::string hero_id = std::to_string(temp_hero->name);
				std::string act_str = "Fight_" + hero_id;
				planner->set_current_action(Containers::action_table[act_str]);
				planner->get_current_action()->setDoer(temp_hero);
				planner->get_current_action()->setOwner(temp_hero);
				std::string my_hero = dialogue.int_to_hero_name(hero_num);
				planner->get_current_action()->setReceiver(Containers::hero_table[my_hero]);
				planner->get_current_action()->checkpoint = 0;
				ActionExecFunctions::execute_fight(planner->get_current_action());
				temp_hero->SUGG_ACT_STATUS = temp_hero->SUGG_ACT;
				
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Fight","Confirm Fight","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				//PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Take Advice To Conquer") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Conquer","Confirm Conquer","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
				//ActionPool* hero_map;
				//hero_map = temp_hero->actionPool_map[dialogue.hero_name_to_int(curr_hero_topic)];
				int hero_num = dialogue.hero_name_to_int(curr_hero_topic);
				//std::string hero_id = std::to_string(hero_num);
				std::string hero_id = std::to_string(temp_hero->name);
				std::string act_str = "Conquer_" + hero_id;
				planner->set_current_action(Containers::action_table[act_str]);
				planner->get_current_action()->setDoer(temp_hero);
				planner->get_current_action()->setOwner(temp_hero);
				std::string my_hero = dialogue.int_to_hero_name(hero_num);
				planner->get_current_action()->setReceiver(Containers::hero_table[my_hero]);
				planner->get_current_action()->checkpoint = 0;
				ActionExecFunctions::execute_conquer(planner->get_current_action());
				temp_hero->SUGG_ACT_STATUS = temp_hero->SUGG_ACT;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Conquer","Confirm Conquer","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				//PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Take Advice To Send Peace Offering To") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Peace","Confirm Peace","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Peace","Confirm peace","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				//PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Take Advice To Ally With") {
			//choose different dialog if they denied the action
			if (accepted_action) {
				dialogue_point diog_pt = { "Confirm Ally","Confirm Ally","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
				//ActionPool* hero_map;
				//hero_map = temp_hero->actionPool_map[dialogue.hero_name_to_int(curr_hero_topic)];
				int hero_num = dialogue.hero_name_to_int(curr_hero_topic);
				//std::string hero_id = std::to_string(hero_num);
				std::string hero_id = std::to_string(temp_hero->name);
				std::string act_str = "Form_Alliance_" + hero_id;
				planner->set_current_action(Containers::action_table[act_str]);
				planner->get_current_action()->setDoer(temp_hero);
				planner->get_current_action()->setOwner(temp_hero);
				std::string my_hero = dialogue.int_to_hero_name(hero_num);
				planner->get_current_action()->setReceiver(Containers::hero_table[my_hero]);
				planner->get_current_action()->checkpoint = 0;
				ActionExecFunctions::execute_form_alliance(planner->get_current_action());
				temp_hero->SUGG_ACT_STATUS = temp_hero->SUGG_ACT;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Ally","Confirm Ally","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";

				//calls action end if the question is denied otherwise called on cmpletion of the action
				//PlayerActExecFunctions::execute_end(false);
			}
			state = 9;
		}
		else if (replyString == "Teach") {
			//calls action start if the question is asked at all
			//PlayerActExecFunctions::execute_start("Spar", temp_hero);

			//check if I want to accept
			if (accepted_action) {
				dialogue_point diog_pt;
				if (temp_hero->name == YEMOJA){ //if Yemoja is doing the teaching
					diog_pt = { "Teach Fireball","Teach Fireball","",curr_hero_topic,"1" };
				    player->can_fire = true;//enable player to shoot fireball
			    }
				else if (temp_hero->name == OYA) {//if Oya is doing the teaching
					diog_pt = { "Teach Spin","Teach Spin","",curr_hero_topic,"1" };
					player->can_spin = true;//enable player to do spin slash
				}	
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = check_if_known(reply_pt_sentence, "");
				state = 12;
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Confirm Teach","Confirm Teach","",curr_hero_topic,"1" };
				std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
				replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
				message = player->getName() + ": " + reply_pt_sentence + "\n\n";
				state = 9;
			}
		}
		//state = 9;
	}
}

/*Handles the generation of the npc's reply point by calling functions from
DialogueHelper. Calls otherConversationPoint() function to generate the
npc's conversation point and to display the npc's reply and conversation
points.*/
void DialogueController::other_response_soldier(std::string info, std::string hero_topic)
{
        Hero* temp_hero = CheckClass::isHero(other);
	

	//if (state != 8) {
		dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log,temp_hero);
		replyString = line[ConvPointName];

		/*avoids setting a topic when npc replies with "You already asked me that"
		or if npc says any other special case reply. Special case replies are
		typically vectors with a size of only 2.*/
		if (line.size() >= 4)
			line[Topic] = hero_topic;


		/*if (replyString == "Accept Alliance Offer") {
			//calls action start if the question is asked at all
			PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);

			//check if I want to accept (seeting to fail for testing)
			accepted_action = true; //should call a function

			if (accepted_action) {
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}
			else {
				/////////////need to be changed to correct calls/dialog if not accepted///////////////////
				dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
				std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";
			}

			state = 8;*/
		/*}
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
		}*/
		//else {
		Soldier* soldier;
		soldier = dynamic_cast<Soldier*>(other);

		std::string reply_pt_sentence = "";

		//currently adds an NPC to the player's party right away if
		//the player asks them to join(NPC always says yes)
		//eventually make it so NPC can refuse to join player's party
		if (replyString == "Response_Recruit_For_Party") {
			if (soldier->getVillage()->get_alliance() == player->getVillage()->get_alliance()) {
				player->getVillage()->barracks->addToParty(soldier, false);
				//soldier->getParty()->setAlliance(player->getParty()->getAlliance());
				soldier->setCurrentLeader(player);
				soldier->setParty(player->getParty());
				reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
			}
			else { //they will say no if not part of same alliance as you
				reply_pt_sentence = dialogue.gen_dialog_negative(line, temp_hero);
			}
		}

		//removes an NPC of the player's choosing from their party
		if (replyString == "Response_Remove_From_Party") {
			soldier->setCurrentLeader(soldier);
			player->getParty()->removeSoldier(soldier, true);
			reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
			//soldier->getParty()->removeSoldier(soldier, true);
			//soldier->getParty()->setAlliance(player->getParty()->getAlliance());
			//cout << soldier->getParty()->getAlliance();
			//Party* p = nullptr;
			//soldier->setParty(p);
			//soldier->getParty()->setLeader(nullptr);
			//std::cout << soldier->getCurrentLeader()->getName();
		}

		
		message = other->getName() + ": " + reply_pt_sentence + "\n\n";

		state = 7;
			//otherConversationPoint(line);
		//}
	/*}
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
	}*/
}

void DialogueController::other_response_babalawo(std::string info, std::string hero_topic)
{
	Hero* temp_hero = CheckClass::isHero(other);


	//if (state != 8) {
	dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log, temp_hero);
	replyString = line[ConvPointName];

	//

	/*avoids setting a topic when npc replies with "You already asked me that"
	or if npc says any other special case reply. Special case replies are
	typically vectors with a size of only 2.*/
	if (line.size() >= 4)
		line[Topic] = hero_topic;


	/*if (replyString == "Accept Alliance Offer") {
	//calls action start if the question is asked at all
	PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);

	//check if I want to accept (seeting to fail for testing)
	accepted_action = true; //should call a function

	if (accepted_action) {
	dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
	std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
	message = other->getName() + ": " + reply_pt_sentence + "\n\n";
	}
	else {
	/////////////need to be changed to correct calls/dialog if not accepted///////////////////
	dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer" };
	std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
	message = other->getName() + ": " + reply_pt_sentence + "\n\n";
	}

	state = 8;*/
	/*}
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
	}*/
	//else {
	

	std::string reply_pt_sentence = "";

	//currently adds an NPC to the player's party right away if
	//the player asks them to join(NPC always says yes)
	//eventually make it so NPC can refuse to join player's party
	reply_pt_sentence = dialogue.gen_dialog_babalawo(line,other);


	message = other->getName() + ": " + reply_pt_sentence + "\n\n";

	
	if(replyString == "Response Ask For Divination"){
		if (other->getName().find("Oasis") != string::npos)
		{
			if (!DialogueController::talked_to_babalawo_o)
			{
				//give shrine blessing
				player->addHealth(300);//regenerate to full he
				player->ori += 20;//boost ori by 30
			}
			else {
				dialogue_point diog_pt = { "No Divination","No Divination","","","1","0" };
				reply_pt_sentence = dialogue.gen_dialog_babalawo(diog_pt, other);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";

			}
		}
		else if (other->getName().find("Jungle") != string::npos)
		{
			if (!DialogueController::talked_to_babalawo_j)
			{
				//give shrine blessing
				player->addHealth(300);//regenerate to full he
				player->ori += 20;//boost ori by 30
			}
			else {
				dialogue_point diog_pt = { "No Divination","No Divination","","","1","0" };
				reply_pt_sentence = dialogue.gen_dialog_babalawo(diog_pt, other);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";

			}
		}
		else if (other->getName().find("Mountain") != string::npos)
		{
			if (!DialogueController::talked_to_babalawo_m)
			{
				//give shrine blessing
				player->addHealth(300);//regenerate to full he
				player->ori += 20;//boost ori by 30
			}
			else {
				dialogue_point diog_pt = { "No Divination","No Divination","","","1","0" };
				reply_pt_sentence = dialogue.gen_dialog_babalawo(diog_pt, other);
				message = other->getName() + ": " + reply_pt_sentence + "\n\n";

			}
		}
		
	}
	else if(replyString == "Response Inquire About Ifa"){

	}

	state = 1;
	//otherConversationPoint(line);
	//}
	/*}
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
	}*/
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

vector<std::vector<std::string>> DialogueController::get_soldier_options()
{
	vector<std::vector<std::string>> tmp;

	for (int i = 0; i < soldier_options[optionsIndex].size(); i++)
	{
		tmp.push_back(soldier_options[optionsIndex][i]);
	}
	return tmp;
}

vector<std::vector<std::string>> DialogueController::get_babalawo_options()
{
	vector<std::vector<std::string>> tmp;

	for (int i = 0; i < babalawo_options[optionsIndex].size(); i++)
	{
		tmp.push_back(babalawo_options[optionsIndex][i]);
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
	optionsIndex = 0;

	if (temp_hero) {

		//temp_hero->rel[player->name]->addNotoriety(50);
		//temp_hero->rel[player->name]->addStrength(50);
		//temp_hero->rel[player->name]->addAffinity(50);

			remove_dialog_option("Ask_To_Duel", NotorietyIcon);
			remove_dialog_option("Ask_To_Spar", StrengthIcon);
			add_dialog_option("Ask_To_Duel", NotorietyIcon);
			add_dialog_option("Ask_To_Spar", StrengthIcon);

			if (temp_hero->rel[player->name]->getAffinity() <= 30 && temp_hero->rel[player->name]->getStrength() <= 60)
				set_selectable(true, "Ask_To_Duel", NotorietyIcon);
			else
				set_selectable(false, "Ask_To_Duel", NotorietyIcon);

			if (temp_hero->rel[player->name]->getStrength() >= 50 && temp_hero->rel[player->name]->getAffinity() <= 85 && temp_hero->rel[player->name]->getNotoriety() <= 75)
				set_selectable(true, "Ask_To_Spar", StrengthIcon);
			else
				set_selectable(false, "Ask_To_Spar", StrengthIcon);

			if (temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance())
				set_selectable(true, "Recruit_For_Party", StrengthIcon);
			else
				set_selectable(false, "Recruit_For_Party", StrengthIcon);

			if (temp_hero->rel[player->name]->getAffinity() + (player->ori / 10) >= 60 &&
				temp_hero->rel[player->name]->getStrength() + (player->ori / 10) >= 60)
				set_selectable(true, "Request_Teaching", StrengthIcon);
			else
				set_selectable(false, "Request_Teaching", StrengthIcon);

			if (temp_hero->rel[player->name]->getAffinity() >= 85)
				set_selectable(true, "Ask_To_Form_Alliance", NotorietyIcon);
			else
				set_selectable(false, "Ask_To_Form_Alliance", NotorietyIcon);

			unselectable_to_bottom();
			options = dialogue.get_possible_conv_pts();


		
		player->filter_move_to(temp_hero);
		unselectable_to_bottom();
		//if (first_buff) {
			//temp_hero->rel[player->name]->addNotoriety(50);
			//temp_hero->rel[player->name]->addStrength(50);
			//temp_hero->rel[player->name]->addAffinity(50);
		//}
		//first_buff = false;
	}
	/*handles what the greeting phrase should be based on whether or not the player
	has taken or completed a quest from the npc*/
		if (temp_hero) {
			Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
			bool player_doing_quest = false;
			bool quest_complete = false;

			for (int i = 0; i < planner->quests_given.size(); ++i) {
				if (planner->quests_given[i]->getDoer()->name == SHANGO && planner->quests_given[i]->executed == false) {
					player_doing_quest = true;
				}
				if (planner->quests_given[i]->getDoer()->name == SHANGO && (planner->quests_given[i]->executed == true || 
					(player->quest_status[temp_hero->name] == Player::SUCC_QUEST || player->quest_status[temp_hero->name] == Player::SUCC_QUEST))) {
					quest_complete = true;
				}
			}
			if (quest_complete) {
				if (player->quest_status[temp_hero->name] == Player::SUCC_QUEST) {
					message = check_if_known(dialogue.gen_dialog({ "Quest_Complete","Quest_Complete" }, temp_hero),"");
					player->quest_status[temp_hero->name] = Player::NOT_QUEST;
					quest_complete = false;
					for (int i = 0; i < planner->quests_given.size();) {
						if (planner->quests_given[i]->getDoer()->name == SHANGO /*&& planner->quests_given[i]->executed == true*/)
							planner->quests_given.erase(planner->quests_given.begin() + i);//erase from npc's quests log
						else
							++i;
					}
					for (int i = 0; i < player->quests_log.size();) {
						if (player->quests_log[i]->executed) {
							player->remove_quest(player->quests_log[i]);//remove from "quests" map
							player->quests_log.erase(player->quests_log.begin() + i);//erase from player's quests log
						}
						else
							++i;
					}
				}
				else if (player->quest_status[temp_hero->name] == Player::FAIL_QUEST) {
					message = check_if_known(dialogue.gen_dialog({ "Quest_Failed","Quest_Failed" }, temp_hero),"");
					player->quest_status[temp_hero->name] = Player::NOT_QUEST;
					quest_complete = false;
					for (int i = 0; i < planner->quests_given.size();) {
						if (planner->quests_given[i]->getDoer()->name == SHANGO /*&& planner->quests_given[i]->executed == true*/)
							planner->quests_given.erase(planner->quests_given.begin() + i);
						else
							++i;
					}
					for (int i = 0; i < player->quests_log.size();) {
						if (player->quests_log[i]->executed) {
							player->remove_quest(player->quests_log[i]);//remove from "quests" map
							player->quests_log.erase(player->quests_log.begin() + i);//erase from player's quests log
						}
						else
							++i;
					}
					
				}
			}
			else if (player_doing_quest && temp_hero->SUGG_ACT_STATUS == 0){
				message = check_if_known(dialogue.gen_dialog({ "Quest_In_Progress","Quest_In_Progress" }, temp_hero),"");	
			}
			else if (temp_hero->SUGG_ACT_STATUS == 2) {
				message = check_if_known(dialogue.gen_dialog({ "Terrible Advice","Terrible Advice" }, temp_hero),"");
				temp_hero->SUGG_ACT_STATUS = 0;
			}
			else if (temp_hero->SUGG_ACT_STATUS == 3) {
				message = check_if_known(dialogue.gen_dialog({ "Good Advice","Good Advice" }, temp_hero),"");
				temp_hero->SUGG_ACT_STATUS = 0;
			}
			else {
				message = check_if_known(dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero),"");
			}
		}
		else
		    message = n->getName() + ": " + dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero);
		if (playerTalk && temp_hero) {
			PlayerChoose();
		}
		else {//call player_choose fucntion for soldiers instead if not talking to Hero
			Soldier* soldier;
			soldier = dynamic_cast<Soldier*>(other);
			//soldier = nullptr;//used to treat soldiers as shrines for testing purposes.
			if (soldier)
				player_choose_soldier();
			else {
				//check if player is attempting to interact with babalawo, villager, or shrine
				//and call appropriate function
				NPC* thing;
				thing = dynamic_cast<NPC*>(other);
				if (thing) {
					if (other->getName().find("Babalawo") != string::npos) {//if player interacting with babalawo
						player_choose_babalawo();
						message = n->getName() + ": " + dialogue.gen_dialog_babalawo({ "Greeting","Greeting" }, other);
					}
					else if (other->getName().find("Shrine") != string::npos)//if player interacting with shrine
						shrine_interact();
					else//otherwise player is interacting with a villager
						villager_interact();
				}
			}
	
		}
}

/*
void DialogueController::start_soldier_conversation(WorldObj* n, bool playerTalk)
{
	other = n;
	//Hero* temp_hero = CheckClass::isHero(other);
	std::string start_message = "";

	Hero* temp_hero = CheckClass::isHero(other);
	message = n->getName() + ": " + dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero);
	if (playerTalk) {
		PlayerChoose();
	}

}
*/

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
	Hero* temp_hero = CheckClass::isHero(other);
	/*does normal exitDialogue stuff if "other" is not a hero*/
	if (state == 7 || state == 9) {

		//removes all conversation log entries from the log for the current conversation
		for (int i = 0; i < curr_conversation_log.size(); i++) {

			//delete memory allocated for instance of Memory class here
			//delete tmp_top.second;
			//delete memory allocated for conversation log object here
			if (curr_conversation_log[i] != nullptr)
				delete curr_conversation_log[i];
		}
		curr_conversation_log.clear();

		//removes unwanted conversation log entries from NPC's permanent storage
		if (temp_hero) {
			for (int i = 0; i < temp_hero->conversation_log.size(); ) {

				//delete memory allocated for instance of Memory class here
				//delete tmp_top.second;
				//delete memory allocated for conversation log object here
				if (temp_hero->conversation_log[i] != nullptr) {
					if (temp_hero->conversation_log[i]->get_conv_point()->get_name() != "Ask_Name"
						&& temp_hero->conversation_log[i]->get_conv_point()->get_name() != "Ask_Origin") {
						delete temp_hero->conversation_log[i];
						temp_hero->conversation_log.erase(temp_hero->conversation_log.begin() + i);
					}
					else
						++i;
				}
			}
		}

		if (temp_hero && is_hero_act == false) {
			remove_hero_related_conv_points();
			//temp_hero->rel[player->name]->addNotoriety(50);
			//temp_hero->rel[player->name]->addStrength(50);
			//temp_hero->rel[player->name]->addAffinity(50);
			//remove_ask_for_quest();
		}
		else {
			Soldier* sold = dynamic_cast<Soldier*>(other);
			if(sold)
			    remove_soldier_opts();
		}
		other = nullptr;
		state = 0;
		DialogueController::scroll_control = 0;
		DialogueController::quest_declined = false;

		first_call = true;
		started_conv = false;
		quited_gui = true;
		first_q_press = false;
		shrine_talk_counter = 0;
		teach_move_counter = 0;
		is_hero_act = false;
	}
	else {
		state = 7;
		if (temp_hero) {//check if "other" is a hero before seeing if they can offer you a quest
			offer_quest_on_exit(temp_hero);
			/*does normal exitDialogue stuff if quest is not given or if player has denied quest offer*/
			if (quest_declined == true)
				state = 7;
		}
		else {
			Soldier* my_sol = dynamic_cast<Soldier*>(other);
			if(!my_sol)//make babalawo farewell appear on exit
                message = other->getName() + ": " + dialogue.gen_dialog_babalawo({ "Farewell","Farewell" }, other);
			remove_soldier_opts();
			remove_babalawo_opts();
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
/*
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

*/

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
		if (itor->second->get_name() == "Ask_For_Quest"){
			tmp_dpoint = itor->second->dpoint;
		    options[QuestionMarkIcon].push_back(tmp_dpoint);
		    dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].push_back(tmp_dpoint);
	    }
		for (int j = 0; j < player->heroes_player_knows.size(); ++j) {
			if (player->heroes_player_knows[j] != dialogue.hero_name_to_int(other->getName())) {
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Ask About",0) != string::npos && itor->second->dpoint[CorrespondingConvPt] == "") {
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[Topic] = dialogue.int_to_hero_name(player->heroes_player_knows[j]);
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
		for (int j = 0; j < player->heroes_player_knows.size(); ++j) {
			if (player->heroes_player_knows[j] != dialogue.hero_name_to_int(other->getName())) {
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Advise To", 0) != string::npos && itor->second->dpoint[CorrespondingConvPt] == "") {
						tmp_dpoint = itor->second->dpoint;
						tmp_dpoint[Topic] = dialogue.int_to_hero_name(player->heroes_player_knows[j]);
						if (player->move_to_flags.find(itor->second->get_name()) != player->move_to_flags.end()) {
							if(player->move_to_flags[itor->second->get_name()] == 1)
							    tmp_dpoint[IsSelectable] = "1";
							else
								tmp_dpoint[IsSelectable] = "0";
						}
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
		if (options[QuestionMarkIcon][i][ConvPointName].find("Advise To", 0) != string::npos || options[QuestionMarkIcon][i][ConvPointName].find("Ask About", 0) != string::npos 
			|| options[QuestionMarkIcon][i][ConvPointName].find("Ask_For_Quest", 0) != string::npos) {

			options[QuestionMarkIcon].erase(options[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible
	conversation points that are associated with the question mark icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].size();) {
		if (dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Advise To", 0) != string::npos || dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Ask About", 0) != string::npos
			|| dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Ask_For_Quest", 0) != string::npos) {

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

/*Removes Ask For Quest conversation point from player's dialog options.*/
/*
void DialogueController::remove_ask_for_quest() {
	/*removes hero-related conversation points that are associated with the
	question mark icon from player's dialog options vector 
	for (int i = 0; i < options[QuestionMarkIcon].size();) {
		if (options[QuestionMarkIcon][i][ConvPointName].find("Ask_For_Quest", 0) != std::string::npos) {
			options[QuestionMarkIcon].erase(options[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible
	conversation points that are associated with the question mark icon
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].size();) {
		if (dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Ask_For_Quest", 0) != string::npos) {
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].erase(dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

}
*/

/*Adds Ask For Quest conversation point to players dialog options.*/
/*
void DialogueController::add_ask_for_quest() {
	options = dialogue.get_possible_conv_pts();
	dialogue_point tmp_dpoint;

	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
	    if (itor->second->get_topic() != "" && itor->second->get_name().find("Ask_For_Quest", 0) != string::npos && itor->second->dpoint[CorrespondingConvPt] == "") {
		    tmp_dpoint = itor->second->dpoint;
			options[QuestionMarkIcon].push_back(tmp_dpoint);
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].push_back(tmp_dpoint);
		}

	}
	tmp_dpoint.clear();

}
*/

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
	if (planner->give_as_quest && AIController::quest_response(temp_hero,player)) {
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

			message = check_if_known(reply_pt_sentence, con_pt_sentence);
			replyOptions = dialogue.get_possible_reply_pts("Offer_Quest", optionsIndex);

			select = 0;
			state = 2;
			offered_quest = true;
			//planner->quests_given.push_back(planner->get_current_action());
		}
	}
	return offered_quest;
	
}

/*changes message on upper GUI window to the NPC's farewell message*/
void DialogueController::create_farewell() {
	dialogue_point diog_pt = { "Farewell","Farewell" };
	Hero* temp_hero = CheckClass::isHero(DialogueController::other);
	std::string farewell_sentence = DialogueController::getDialogueHelper()->gen_dialog(diog_pt, temp_hero);
	if (temp_hero) {
		message = check_if_known(farewell_sentence, "");
	}
	else
		message = DialogueController::other->getName() + ": " + farewell_sentence + "\n\n";
}

/*removes soldier dialog options*/
void DialogueController::remove_soldier_opts() {
	//for (int i = 0; i < soldier_options[StrengthIcon].size(); i++)
	//{
		//soldier_options[StrengthIcon][i].erase();
	//}
	soldier_options.clear();
}

void DialogueController::remove_babalawo_opts() {
	
	babalawo_options.clear();
}

/*Adds a conversation log entry to an NPC's permanent conversation log if
the NPC does not already have an entry identical to that one in their log.
Otherwise, it does nothing.*/
void DialogueController::add_to_perm_storage(ConversationLogObj* log_entry) {
	Hero* temp_hero = CheckClass::isHero(other);
	if (temp_hero != nullptr) {
		if (temp_hero->conversation_log.size() > 0) {
			for (int i = 0; i < temp_hero->conversation_log.size(); ++i) {
				if (temp_hero->conversation_log[i]->get_conv_point() == log_entry->get_conv_point()
					&& temp_hero->conversation_log[i]->get_who() == log_entry->get_who()
					&& temp_hero->conversation_log[i]->get_topic() == log_entry->get_topic())
					return;
			}
		}
		temp_hero->conversation_log.push_back(log_entry);
		
	}

}

/*used to cause player to scroll to nearest selectable option when they 
are scrolling down. unselectable options are skipped.*/
void DialogueController::move_to_selectable_down() {
	int scroll_counter = 0;
	Hero* temp_hero = CheckClass::isHero(other);
	if (temp_hero && DialogueController::getState() == 1) {
		if (DialogueController::scroll_control == DialogueController::getOptions().size() - 1)
			return;
		if (DialogueController::scroll_control == DialogueController::getOptions().size() - 2) {
			if (DialogueController::getOptions()[DialogueController::scroll_control + 1][4] == "0")
				return;
		}
	}
	else if(DialogueController::getState() == 1 && other->getName().find("Babalawo") != string::npos){//babalawo case
		if (DialogueController::scroll_control == DialogueController::get_babalawo_options().size() - 1)
			return;
		if (DialogueController::scroll_control == DialogueController::get_babalawo_options().size() - 2) {
			if (DialogueController::get_babalawo_options()[DialogueController::scroll_control + 1][4] == "0")
				return;
		}
	}
	else if (state == 2) {
		if (DialogueController::scroll_control == DialogueController::getReplyOptions().size() - 1)
			return;
	}
	if (temp_hero && state != 2) {
		for (int i = 0; (DialogueController::scroll_control + i) < DialogueController::getOptions().size(); ++i) {
			if (DialogueController::getOptions()[DialogueController::scroll_control + i][4] == "1") {
				if ((i != 0) || (DialogueController::getOptions().size() == 2 && DialogueController::getOptions()[1][4] == "1")) {
					scroll_counter++;
					break;
				}
			}
			else {
				scroll_counter++;
				if (i == DialogueController::getOptions().size() - 1)
					scroll_counter = 0;
			}
		}
	}
	else if(state != 2 && other->getName().find("Babalawo") != string::npos) {//babalawo case
		for (int i = 0; (DialogueController::scroll_control + i) < DialogueController::get_babalawo_options().size(); ++i) {
			if (DialogueController::get_babalawo_options()[DialogueController::scroll_control + i][4] == "1") {
				if (i != 0 || (DialogueController::get_babalawo_options().size() == 2 && DialogueController::get_babalawo_options()[1][4] == "1")) {
					scroll_counter++;
					break;
				}
			}
			else {
				scroll_counter++;
				if (i == DialogueController::getOptions().size() - 1)
					scroll_counter = 0;
			}
		}
	}
	if (state == 2)
		++scroll_counter;
	DialogueController::scroll_control += scroll_counter;
}

/*used to cause player to scroll to nearest selectable option when they
are scrolling up. unselectable options are skipped.*/
void DialogueController::move_to_selectable_up() {
	int scroll_counter = 0;
	if (DialogueController::scroll_control == 0)
		return;
	if (state != 2) {
		for (int i = 0; (DialogueController::scroll_control - i) >= 1; ++i) {
			Hero* temp_hero = CheckClass::isHero(other);
			if (temp_hero) {
				if (DialogueController::getOptions()[DialogueController::scroll_control - i - 1][4] == "1") {
					scroll_counter++;
					break;
				}
				else {
					scroll_counter++;
					if (DialogueController::scroll_control == 0)
						scroll_counter = 0;
				}
			}
			else {//babalawo case
				if (DialogueController::get_babalawo_options()[DialogueController::scroll_control - i - 1][4] == "1") {
					scroll_counter++;
					break;
				}
				else {
					scroll_counter++;
					if (DialogueController::scroll_control == 0)
						scroll_counter = 0;
				}
			}
		}
	}
	else
		++scroll_counter;
	DialogueController::scroll_control -= scroll_counter;
}

/*sets a dialog option specified by the arguments to be either selectable or unselectable*/
void DialogueController::set_selectable(bool is_selectable, std::string option_name, int icon) {
	std::vector<std::vector<std::vector<std::string>>> tmp_conv_points;
	tmp_conv_points = dialogue.get_possible_conv_pts();
	for (int i = 0; i < tmp_conv_points[icon].size(); ++i) {
		if (tmp_conv_points[icon][i][ConvPointName] == option_name) {
			if (is_selectable)
				dialogue.get_possible_conv_pts_ref()[icon][i][IsSelectable] = "1";
			else
				dialogue.get_possible_conv_pts_ref()[icon][i][IsSelectable] = "0";

			break;
		}
	}
	options = dialogue.get_possible_conv_pts();
}

/*adds a dialog option specified by the name of the option to add, and the
icon that the option should go under*/
void DialogueController::add_dialog_option(std::string option_name, int icon){
	dialogue_point tmp_dpoint;
	tmp_dpoint = Containers::conv_point_table[option_name]->dpoint;
	dialogue.get_possible_conv_pts_ref()[icon].push_back(tmp_dpoint);
	options = dialogue.get_possible_conv_pts();
}

/*removes a dialog option specified by the name of the option to remove, and the
icon that the option is currently associated with*/
void DialogueController::remove_dialog_option(std::string option_name, int icon){
	std::vector<std::vector<std::vector<std::string>>> tmp_opts;
	tmp_opts = dialogue.get_possible_conv_pts();
	for (int i = 0; i < tmp_opts[icon].size();) {
		if (tmp_opts[icon][i][ConvPointName] == option_name) {
			dialogue.get_possible_conv_pts_ref()[icon].erase
			(dialogue.get_possible_conv_pts_ref()[icon].begin() + i);
			break;
		}
		else
			++i;
	}
	options = dialogue.get_possible_conv_pts();
}

bool DialogueController::check_advice_acceptance(Player* p, Hero* npc) {
	int range_cap = 60 + (npc->rel[p->name]->getNotoriety() - 70) + p->ori/10;
	int result = rand() % 101;//get random number between 0 and 100
	if(result <= range_cap)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool DialogueController::check_acceptance(Player* p, Hero* npc) {
	std::string::size_type name_end = p->cur_action->getName().find_last_of('_');
	std::string act_name = p->cur_action->getName().substr(0, name_end);

	int range_cap = npc->get_range_cap(p->cur_action);
	for (auto i : curr_conversation_log) {
		if (i->get_who() == SHANGO && i->get_conv_point()->get_name() == act_name)
			range_cap = range_cap;// / 2;
	}
	int result = rand() % 101;//get random number between 0 and 100
	if (result <= range_cap)
	{
		return true;
	}
	else
	{
		return false;
	}

}

/*Used for breaking up the dialog that a Hero says when teaching the player a skill into multiple different screens,
forcing the player to select the "Next" option to view more text until eventually being forced to "EXIT".*/
void DialogueController::load_teach_dialog()
{
	dialogue_point dpoint;
	Hero* npc = CheckClass::isHero(other);
	if (npc->name == YEMOJA) {
		switch (teach_move_counter) {
		case 1:
			dpoint = { "Teach Fireball 1","Teach Fireball 1" };
			break;
		case 2:
			dpoint = { "Teach Fireball 2","Teach Fireball 2" };
			break;
		case 3:
			dpoint = { "Teach Fireball 3","Teach Fireball 3" };
			break;
		}

	}
	else if (npc->name == OYA) {
		switch (teach_move_counter) {
		case 1:
			dpoint = { "Teach Spin 1","Teach Spin 1" };
			break;
		case 2:
			dpoint = { "Teach Spin 2","Teach Spin 2" };
			break;
		case 3:
			dpoint = { "Teach Spin 3","Teach Spin 3" };
			break;
		}
	}
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint,npc);
	message = check_if_known(conversation_pt_sentence, "");
	if (teach_move_counter == 3)
		state = 7;
	else
		state = 12;
}

void DialogueController::duel_pop_up(Action* act)
{
	other = act->getReceiver();
	dialogue_point dpoint = {"Finish Duel","Finish Duel"};
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getReceiver());
	message = act->getReceiver()->getName() + ": " + conversation_pt_sentence;
	state = 7;

}

void DialogueController::spar_pop_up(Action* act)
{
	other = act->getReceiver();
	dialogue_point dpoint = {"Finish Spar","Finish Spar"};
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getReceiver());
	message = act->getReceiver()->getName() + ": " + conversation_pt_sentence;
	state = 7;
}

void DialogueController::hero_act_alliance_pop_up(Action* act) {
	other = act->getDoer();
	dialogue_point dpoint = { "Ask_To_Form_Alliance","Ask_To_Form_Alliance" };
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getDoer());
	bool known = false;
	for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
		if (player->heroes_player_knows[i] == act->getDoer()->name) {
			known = true;
			break;
		}
	}
	if (known)
		message = act->getDoer()->getName() + ": " + conversation_pt_sentence;
	else
		message = check_if_known(conversation_pt_sentence, "");
	replyOptions = dialogue.get_possible_reply_pts(dpoint[ConvPointName], optionsIndex);
	is_hero_act = true;
	hero_act_toward_player = act;
	state = 2;
}

void DialogueController::hero_act_bribe_pop_up(Action* act) {
	other = act->getDoer();
	dialogue_point dpoint = { "Bribe","Bribe" };
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getDoer());
	bool known = false;
	for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
		if (player->heroes_player_knows[i] == act->getDoer()->name) {
			known = true;
			break;
		}
	}
	if (known)
		message = act->getDoer()->getName() + ": " + conversation_pt_sentence;
	else
		message = check_if_known(conversation_pt_sentence, "");
	replyOptions = dialogue.get_possible_reply_pts(dpoint[ConvPointName], optionsIndex);
	is_hero_act = true;
	hero_act_toward_player = act;
	state = 2;
}

void DialogueController::hero_act_compliment_pop_up(Action* act) {
	other = act->getDoer();
	dialogue_point dpoint = { "Compliment","Compliment" };
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getDoer());
	bool known = false;
	for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
		if (player->heroes_player_knows[i] == act->getDoer()->name) {
			known = true;
			break;
		}
	}
	if (known)
		message = act->getDoer()->getName() + ": " + conversation_pt_sentence;
	else
		message = check_if_known(conversation_pt_sentence, "");
	replyOptions = dialogue.get_possible_reply_pts(dpoint[ConvPointName], optionsIndex);
	is_hero_act = true;
	hero_act_toward_player = act;
	state = 2;
}

void DialogueController::hero_act_boast_pop_up(Action* act) {
	other = act->getDoer();
	dialogue_point dpoint = { "Boast","Boast" };
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getDoer());
	bool known = false;
	for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
		if (player->heroes_player_knows[i] == act->getDoer()->name) {
			known = true;
			break;
		}
	}
	if (known)
		message = act->getDoer()->getName() + ": " + conversation_pt_sentence;
	else
		message = check_if_known(conversation_pt_sentence, "");
	replyOptions = dialogue.get_possible_reply_pts(dpoint[ConvPointName], optionsIndex);
	is_hero_act = true;
	hero_act_toward_player = act;
	state = 2;
}

void DialogueController::hero_act_grovel_pop_up(Action* act) {
	other = act->getDoer();
	dialogue_point dpoint = { "Grovel","Grovel" };
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getDoer());
	bool known = false;
	for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
		if (player->heroes_player_knows[i] == act->getDoer()->name) {
			known = true;
			break;
		}
	}
	if (known)
		message = act->getDoer()->getName() + ": " + conversation_pt_sentence;
	else
		message = check_if_known(conversation_pt_sentence, "");
	replyOptions = dialogue.get_possible_reply_pts(dpoint[ConvPointName], optionsIndex);
	is_hero_act = true;
	hero_act_toward_player = act;
	state = 2;
}

void DialogueController::hero_act_intimidate_pop_up(Action* act) {
	other = act->getDoer();
	dialogue_point dpoint = { "Intimidate","Intimidate" };
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getDoer());
	bool known = false;
	for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
		if (player->heroes_player_knows[i] == act->getDoer()->name) {
			known = true;
			break;
		}
	}
	if (known)
		message = act->getDoer()->getName() + ": " + conversation_pt_sentence;
	else
		message = check_if_known(conversation_pt_sentence, "");
	replyOptions = dialogue.get_possible_reply_pts(dpoint[ConvPointName], optionsIndex);
	is_hero_act = true;
	hero_act_toward_player = act;
	state = 2;
}

std::string DialogueController::check_if_known(std::string rep_str,std::string con_str) {
	Hero* temp_hero = CheckClass::isHero(other);
	bool known = false;
	std::string ret_str = "";
	if (temp_hero) {
		for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
			if (player->heroes_player_knows[i] == temp_hero->name) {
				known = true;
			}
		}
		if(known)
			ret_str = other->getName() + ": " + rep_str + "\n" + con_str;
		else
			ret_str = "???: " + rep_str + "\n" + con_str;

	}
	else
		ret_str = other->getName() + ": " + con_str + "\n\n";

	return ret_str;
}

void DialogueController::apply_post_from_response(std::string rep_choice, Action* act) {
	
	if (rep_choice.find("Accept") != string::npos || DialogueController::scroll_control > 0) {
		if (act->getDoer()->SUGG_ACT_STATUS == 1) {
			//sets suggested action flag to success
			act->getDoer()->SUGG_ACT_STATUS = 3;

			//update notoriety/affinity/strength accordingly
			act->getDoer()->rel[SHANGO]->setNotoriety(act->getDoer()->rel[SHANGO]->getNotoriety() + 7);
			act->getDoer()->rel[SHANGO]->setAffinity(act->getDoer()->rel[SHANGO]->getAffinity() + 7);
			act->getDoer()->rel[SHANGO]->setStrength(act->getDoer()->rel[SHANGO]->getStrength() + 7);
		}
		act->apply_postconditions(true);
	}
	else {
		act->apply_postconditions(false);

		if (act->getDoer()->SUGG_ACT_STATUS == 1) {
			//sets suggested action flag to failure
			act->getDoer()->SUGG_ACT_STATUS = 2;

			//update notoriety/affinity/strength accordingly
			act->getDoer()->rel[SHANGO]->setNotoriety(act->getDoer()->rel[SHANGO]->getNotoriety() - 7);
		}
	}
}

/*Makes it so no unselectable options are the first option in the list for any icon*/
void DialogueController::unselectable_to_bottom() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < dialogue.get_possible_conv_pts_ref()[i].size(); ++j) {
			if (dialogue.get_possible_conv_pts_ref()[i][j][IsSelectable] == "0") {
				dialogue_point dpoint = dialogue.get_possible_conv_pts_ref()[i][j];
				dialogue.get_possible_conv_pts_ref()[i].erase(dialogue.get_possible_conv_pts_ref()[i].begin() + j);
				dialogue.get_possible_conv_pts_ref()[i].push_back(dpoint);
			}
			else//dialog option at top of list is selectable so do nothing
				break;
		}
		
	}

}
