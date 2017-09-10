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

//Holds an npc's reaction to player's action
bool DialogueController::react_positively = true;

Player* DialogueController::player;
WorldObj* DialogueController::other; //the npc speaking with the player
int DialogueController::state = 0;

/*Used in an attempt to lessen the use of the
hard coded indices for dialogue points as suggested
at the dialogue code review. Index 0 normally holds
a string that represents the icon that a conversation point 
is displayed under,but not all conversation points are 
displayed under an icon. As a result, index 0 simply has a string
that represents the name of the conversation point 
for some dialogue points just like
index 1.*/
constexpr int ConvPointName = 1;
constexpr int CorrespondingConvPt = 2;
constexpr int Topic = 3;
constexpr int IsSelectable = 4;

//used to indicate that a conversation log entry has no topic
constexpr int NoTopic = -1;

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

std::string DialogueController::message;    //text displayed on upper window of dialogue GUI
std::string DialogueController::replyString;//stores npc reply or conversation point

int DialogueController::optionsIndex=0;    //indicates icon the player has selected(heart,head,question mark etc.)
int DialogueController::select = 0;        //indicates the position of the option selected by the player

bool DialogueController::accepted_quest = false;
bool DialogueController::prompted_quest = false;

Action* DialogueController::quest = nullptr;

//used for hero actions
bool DialogueController::accepted_action = false;

//used to decide index to begin iterating at for displaying dialog options
int DialogueController::scroll_control = 0;

/*Holds entries for what the player and the npc say during the current conversation.*/
std::vector<ConversationLogObj*> DialogueController::curr_conversation_log;

/*used for passing player's conversation point selection to 
otherResponse() function*/
std::string player_conv_point_choice = ""; 

//current topic of the current conversation cycle
std::string curr_hero_topic = "";

//keeps track of what heroes the player knows(2=Yemoja and 3=Oya)
//Is placeholder that will eventually be gotten rid of
//std::vector<int> DialogueController::heroes_player_knows = {2,3};

/*Used to ensure add_hero_related_conv_points() function is called only 
once per conversation.*/
bool first_call = true;

bool DialogueController::quest_declined = false;

/*Points to conversation log entry that corresponds to
 player's most recent conversation point selection.*/
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

/*Holds whether npc or player reacts + or - to action and what the action is.
Helps determine what visual feedback to display.*/
std::pair<bool, std::string> DialogueController::vis_feedback;

/*Used for controlling the duration of time that feedback(+/-) is displayed
to player after they make a conversation point selection.*/
int DialogueController::feedback_timer = 100;
int DialogueController::feedback_timer_2 = 100;
int DialogueController::feedback_timer_3 = 100;

/*Used for determining whether to show + or - feedback
to the player after an npc has acted on the player's advice.
0 = no advice, 1 = failed advice, 2 = successful advice.*/
int DialogueController::show_advice_feedback = 0;


DialogueController::DialogueController()
{
	srand(time(0));//seeds rand function to ensure good variety of random numbers

	player_conv_point_choice = "";

	//keeps track of the topic of the current conversation cycle
	curr_hero_topic = "";

}


DialogueController::~DialogueController()
{
}

/*Loads player's dialog options based on who the player is speaking to
and sets which ones are selectable. Is called at the beginning of each
new conversation cycle to allow the player to choose a conversation point.*/
void DialogueController::PlayerChoose()
{
	scroll_control = 0;
	Hero* temp_hero = CheckClass::isHero(other);
	DialogueController::feedback_timer = 100;
	options = dialogue.get_possible_conv_pts();

	/*Makes npc player is speaking to react positively to the player's 
	response by default*/
	if (curr_conversation_log.size() > 0) {
		if (curr_conversation_log[curr_conversation_log.size() - 1]->get_conv_point()->get_name().
			find("In Response") != string::npos) 
		{
			vis_feedback.first = react_positively;
		}
	}

	if (temp_hero) {
		if (temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance())
			remove_dialog_option("Ask_To_Form_Alliance", NotorietyIcon);

		if (temp_hero->getParty() == player->getParty())
			remove_dialog_option("Recruit_For_Party", StrengthIcon);

		remove_dialog_option("Ask_To_Duel", NotorietyIcon);
		remove_dialog_option("Ask_To_Spar", StrengthIcon);
		add_dialog_option("Ask_To_Duel", NotorietyIcon);
		add_dialog_option("Ask_To_Spar", StrengthIcon);

		if (temp_hero->rel[player->name]->getAffinity() <= 45 && temp_hero->rel[player->name]->getStrength() <= 80)
			set_selectable(true, "Ask_To_Duel", NotorietyIcon);
		else
			set_selectable(false, "Ask_To_Duel", NotorietyIcon);

		if (temp_hero->rel[player->name]->getStrength() >= 30 && temp_hero->rel[player->name]->getAffinity() >= 60)
			set_selectable(true, "Ask_To_Spar", StrengthIcon);
		else
			set_selectable(false, "Ask_To_Spar", StrengthIcon);

		if (temp_hero->getParty() != player->getParty())
			set_selectable(true, "Recruit_For_Party", StrengthIcon);
		else
			set_selectable(false, "Recruit_For_Party", StrengthIcon);

		if (temp_hero->rel[player->name]->getAffinity() + (player->ori / 10) >= 55 &&
			temp_hero->rel[player->name]->getStrength() + (player->ori / 10) >= 55)
			set_selectable(true, "Request_Teaching", StrengthIcon);
		else
			set_selectable(false, "Request_Teaching", StrengthIcon);

		if (temp_hero->rel[player->name]->getAffinity() >= 85)
			set_selectable(true, "Ask_To_Form_Alliance", NotorietyIcon);
		else
			set_selectable(false, "Ask_To_Form_Alliance", NotorietyIcon);

		player->filter_move_to(temp_hero);

		unselectable_to_bottom();
	}

	if (first_call) {
		if (temp_hero)
		    add_hero_related_conv_points();
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
	std::string name_str = other->getName();
	replace_all(name_str, "_", " ");
	message = name_str + ": " + conversation_pt_sentence;
	if (shrine_talk_counter == 3 || dpoint[ConvPointName] == "Shrine Not Worthy")
		state = 7;
	else
	    state = 11;
}


void DialogueController::villager_interact() {
	dialogue_point dpoint = { other->getName(), other->getName() };
	std::string conversation_pt_sentence = dialogue.gen_dialog_villager(dpoint, other);
	std::string name_str = other->getName();
	std::string::size_type name_end = name_str.find_last_of('_');
	std::string n_str = name_str.substr(0, name_end);
	replace_all(n_str,"_"," ");
	name_str = n_str;
	message = name_str + ": " + conversation_pt_sentence;

	state = 7;
}

/*Identifies the player's conversation point selection, stores
it in the log for the current conversation, sets the conversation state to 5
to make GUI wait for player to press "Enter" to see npc's reply and 
conversation points, sets state to 4 after player presses "Enter", which
shifts the conversation to see the npc reply.*/
void DialogueController::PlayerConversationPoint()
{
	options = dialogue.get_possible_conv_pts();
	dialogue_point choice; //player's option selection

	DialogueController::feedback_timer = 100;
	DialogueController::feedback_timer_2 = 0;

	Hero* temp_hero = CheckClass::isHero(other);

	if (player_conv_point_choice == "") {
	    choice = options[optionsIndex][select + DialogueController::scroll_control];
		
		//Text the player sees as what they say
		std::string conversation_pt_sentence = dialogue.gen_dialog(choice, player);

		replace_all(conversation_pt_sentence,"HERO",choice[Topic]);

		message = player->getName() + ": " + conversation_pt_sentence;

		ConversationLogObj* conv_log_entry;
		ConversationPoint* cp = Containers::conv_point_table[choice[ConvPointName]];
		conv_log_entry = create_conv_log_entry(choice,SHANGO,cp);

		curr_conversation_log.push_back(conv_log_entry);

		entry = create_conv_log_entry(choice, SHANGO, cp);
		
		limit_log_size();

		player_conv_point_choice = choice[ConvPointName];

		vis_feedback.second = player_conv_point_choice;

		set_accepted_action(temp_hero, choice);

		if (player_conv_point_choice == "Request_Teaching")
		    set_accepted_teaching(temp_hero);

		state = 5;
	}
	else {
		state = 4;
		otherResponse(player_conv_point_choice, curr_hero_topic);
		if(temp_hero)
		    add_to_perm_storage(entry, temp_hero);

		if (player_conv_point_choice == "Ask_Name")
		    add_known_hero();

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

		player_conv_point_choice = choice[ConvPointName];

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

		player_conv_point_choice = choice[ConvPointName];

		state = 5;
	}
	else {
		state = 4;
		other_response_babalawo(player_conv_point_choice, curr_hero_topic);

		player_conv_point_choice = "";
	}
}

/*Identifies the player's reply point selection, stores it in the log for
  the current conversation and creates a sentence that the player will say based
  on their reply option selection. Calls function to apply postconditions if the
  player is responding to an action that an npc approached them to perform.*/
void DialogueController::PlayerResponse()
{
	if (state != 6) {

		//player's reply point selection
		dialogue_point choice = replyOptions[select + DialogueController::scroll_control];

		feedback_timer = 0;
		feedback_timer_2 = 100;

		vis_feedback.second = choice[ConvPointName];

		//assumes that the player's reply option associated with a negative response
		//to the npc is at position 0 and that the option(s) asscoiated with a 
		//positive response are not at position 0
		if (choice[ConvPointName].find("In Response") == string::npos) {
			if (DialogueController::scroll_control == 0)
				accepted_action = false;
			else
				accepted_action = true;

			vis_feedback.first = accepted_action;
		}

		Hero* temp_hero = CheckClass::isHero(other);

		if(temp_hero)
		    accept_quest(choice);
		
		set_response_reaction(choice, temp_hero);

		//get a sentence to say based on player's reply option selection
		std::string reply_pt_sentence = dialogue.gen_dialog(choice, player);

		ConversationLogObj* conv_log_entry;
		ConversationPoint* cp = Containers::conv_point_table[choice[ConvPointName]];
		conv_log_entry = create_conv_log_entry(choice, SHANGO, cp);

		curr_conversation_log.push_back(conv_log_entry);

		ConversationLogObj* perm_log_entry = create_conv_log_entry(choice, SHANGO, cp);
		add_to_perm_storage(perm_log_entry,temp_hero);

		limit_log_size();

		/*insert the topic in the player's reply point sentence
		if they are replying to a hero-related conversation point*/
		unsigned int advice_found = choice[ConvPointName].find("Take Advice");
		if (conv_log_entry->get_topic().first != NoTopic && ( advice_found != string::npos || 
			choice[ConvPointName].find("Tell About") != string::npos))
		{ 
			replace_all(reply_pt_sentence, "HERO", choice[Topic]);
		}
			
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		/*If player replies accepting an alliance, duel or spar, causes 
		dialogue to enter farewell state to force player to exit dialogue.*/
		if (choice[ConvPointName] == "Accept Alliance Offer"|| choice[ConvPointName] == "Accept Duel"|| 
			choice[ConvPointName] == "Accept Spar Request") 
		{
			player_conv_point_choice = choice[ConvPointName];
			state = 6;
			if(is_hero_act && !(temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance()))
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
		start_event();
		state = 7;
	}
}

/*Calls functions from the DialogueHelper to handle generating the npc's
  conversation point and reply point. Creates log entries for the npc's
  conversation and reply points and stores the entries in the log
  for the current conversation and stores them in the npc's permanent
  conversation log.*/
void DialogueController::otherConversationPoint(dialogue_point line)
{
	Hero* temp_hero = CheckClass::isHero(other);

	//stores the npc's conversation point
	dialogue_point point = dialogue.choose_conv_pt(curr_conversation_log, temp_hero,player);

	point[Topic] = curr_hero_topic;
	    
	replyString = point[ConvPointName];

	std::string reply_pt_sentence = message;

	//sets reply sentence to positive if npc reacts positively or to negative if
	//npc replies negatively
	if(accepted_action || line[ConvPointName].find("Tell About") != string::npos)
	    reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	else
        reply_pt_sentence = dialogue.gen_dialog_negative(line, temp_hero);

	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero);

	/*Stores the npc's conversation and reply points as entries in the
	log for the current conversation. The reply point is line[ConvPointName] and the
	conversation point is point[ConvPointName].*/
    if(line[ConvPointName] != "Already_Asked" && line[ConvPointName] != "No_More_Phrases"){
		int person = dialogue.hero_name_to_int(other->getName());

		//creation of conversation log entry for reply point
		ConversationPoint* cp = Containers::conv_point_table[line[ConvPointName]];
		ConversationLogObj* conv_log_obj = create_conv_log_entry(line, person,cp );

		/*insert the topic in the npc's reply point sentence
		if they are replying to a hero-related conversation point.*/
		replace_all(reply_pt_sentence, "HERO", line[Topic]);

	    curr_conversation_log.push_back(conv_log_obj);

		ConversationLogObj* perm_log_entry = create_conv_log_entry(line, person, cp);
		add_to_perm_storage(perm_log_entry,temp_hero);

		limit_log_size();

	    //Creation of conversation log entry for conversation point
		ConversationPoint* cp2 = Containers::conv_point_table[point[ConvPointName]];
		ConversationLogObj* conv_log_obj2 = create_conv_log_entry(point, person, cp2);

		if (point[ConvPointName].find("Offer_Quest") != string::npos)
			format_quest_str(conv_log_obj2, con_pt_sentence);
		else
			/*insert the topic at the end of the npc's conversation point sentence
			if they are saying a hero-related conversation point.*/
			replace_all(con_pt_sentence, "HERO", point[Topic]);

	    curr_conversation_log.push_back(conv_log_obj2);

		ConversationLogObj* perm_log_entry2 = create_conv_log_entry(point,person,cp2);
		add_to_perm_storage(perm_log_entry2,temp_hero);

		limit_log_size();
    }
	
	skip_player_reply(point, line,reply_pt_sentence,con_pt_sentence,temp_hero);
	select = 0;
	DialogueController::scroll_control = 0;
}

void DialogueController::other_conversation_point_soldier(dialogue_point line)
{
	Hero* temp_hero = nullptr;

	dialogue_point point = dialogue.choose_conv_pt(curr_conversation_log, temp_hero, player);

	/*Only sets the topic of the npc's conversation point if it is not
	a special case. Special case dialogue points are typically only
	of size 2.*/
	if (point[0] != "No_More_Phrases" && point[0] != "Already_Asked" && point.size() >= 4)
		point[Topic] = curr_hero_topic;

	replyString = point[ConvPointName];

	std::string reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(point, temp_hero); 

	message = other->getName() + ": " + reply_pt_sentence + "\n" + con_pt_sentence;
	replyOptions = dialogue.get_possible_reply_pts(point[ConvPointName], optionsIndex);

	select = 0;
	state = 1;//skip player reply if npc cannot give a conversation point

	DialogueController::scroll_control = 0;
}

/*Calls functions to choose the npc reply point, to set the npc dialogue 
  spoken to the player based on the reply point, and to call execution 
  functions for actions that require them(execute_start(), execute_end() etc.).*/
void DialogueController::otherResponse(std::string info, std::string hero_topic)
{
	Hero* temp_hero = CheckClass::isHero(other);

	DialogueController::feedback_timer_2 = 100;

	if (state != 8 && state != 12 && state != 7) {
		dialogue_point line; //NPC reply selection
		line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log,temp_hero);
		replyString = line[ConvPointName];

		vis_feedback.first = accepted_action;

		if (replyString == "Accept Alliance Offer") 
			initiate_alliance(temp_hero);
		else if (replyString == "Accept Duel") 
			initiate_duel(temp_hero);
		else if (replyString == "Accept Spar Request")
			initiate_spar(temp_hero);
		else if (replyString == "Take Advice To Fight")
			initiate_advice_fight(temp_hero);
		else if (replyString == "Take Advice To Conquer")
			initiate_conquer(temp_hero);
		else if (replyString == "Take Advice To Ally With")
			initiate_ally_advice(temp_hero);
		else if (replyString == "Teach")
			initiate_teach(temp_hero);
		else if (replyString == "Accept Bribe")
			resolve_bribe(line, temp_hero);
		else if (replyString == "Defend Self")
			resolve_defend(line,temp_hero);
		else if (replyString == "Thank")
			resolve_thank(line, temp_hero);
		else if (replyString == "Congratulate")
			resolve_congratulate(line, temp_hero);
		else if (replyString == "Accept Plea")
			resolve_plea(line,temp_hero);
		else if (replyString == "Talk Back")
			resolve_talk_back(line,temp_hero);
		else if (replyString == "Response_Recruit_For_Party")
			finish_recruit(temp_hero,line);
		else {
			state = 3;
			otherConversationPoint(line);
		}
	}
	else {
		if (replyString == "Accept Alliance Offer")
			finish_alliance(temp_hero);
		else if (replyString == "Accept Duel")
			finish_duel();
		else if (replyString == "Accept Spar Request")
			finish_spar();
		else if (replyString == "Take Advice To Fight")
			finish_fight_advice(temp_hero);
		else if (replyString == "Take Advice To Conquer")
			finish_conquer_advice(temp_hero);
		else if (replyString == "Take Advice To Send Peace Offering To")
			finish_peace_advice();
		else if (replyString == "Take Advice To Ally With")
			finish_ally_advice(temp_hero);
		else if (replyString == "Teach")
			finish_teach(temp_hero);
	}
}

/*Handles the generation of the npc's reply point by calling functions from
DialogueHelper. Calls otherConversationPoint() function to generate the
npc's conversation point and to display the npc's reply and conversation
points.*/
void DialogueController::other_response_soldier(std::string info, std::string hero_topic)
{
        Hero* temp_hero = CheckClass::isHero(other);
	
		dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log,temp_hero);
		replyString = line[ConvPointName];

		Soldier* soldier;
		soldier = dynamic_cast<Soldier*>(other);

		std::string reply_pt_sentence = "";

		//currently adds an NPC to the player's party right away if
		//the player asks them to join(NPC always says yes)
		//eventually make it so NPC can refuse to join player's party
		if (replyString == "Response_Recruit_For_Party") {
			if (soldier->getVillage()->get_alliance() == player->getVillage()->get_alliance()) {
				player->getParty()->addToParty(soldier, false);
				reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
			}
			else//they will say no if not part of same alliance as you
				reply_pt_sentence = dialogue.gen_dialog_negative(line, temp_hero);
		}

		//removes an NPC of the player's choosing from their party
		if (replyString == "Response_Remove_From_Party") {
			soldier->setCurrentLeader(soldier);
			player->getParty()->removeSoldier(soldier, true);
			reply_pt_sentence = dialogue.gen_dialog(line, temp_hero);
		}

		std::string name_str = other->getName();
		std::string::size_type name_end = name_str.find_last_of('_');
		std::string n_str = name_str.substr(0, name_end);
		replace_all(n_str, "_", " ");
		name_str = n_str;
		
		message = name_str + ": " + reply_pt_sentence + "\n\n";

		state = 7;
}

void DialogueController::other_response_babalawo(std::string info, std::string hero_topic)
{
	Hero* temp_hero = CheckClass::isHero(other);

	dialogue_point line = dialogue.choose_reply_pt(info, optionsIndex, curr_conversation_log, temp_hero);
	replyString = line[ConvPointName];
	
	std::string reply_pt_sentence = "";

	//currently adds an NPC to the player's party right away if
	//the player asks them to join(NPC always says yes)
	//eventually make it so NPC can refuse to join player's party
	reply_pt_sentence = dialogue.gen_dialog_babalawo(line,other);

	std::string name_str = other->getName();
	replace_all(name_str, "_", " ");


	message = name_str + ": " + reply_pt_sentence + "\n\n";

	
	if(replyString == "Response Ask For Divination")
	    load_divination(reply_pt_sentence, name_str);

	state = 1;
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

/*The origin function of all conversations. Initializes important vars
such as the NPC speaking with the player, as well as some control flow
vars. Calls appropriate functions based on what kind of NPC the player
is conversing with. Checks player's quest status and calls appropriate
functions to handle quest completion and proper message display.*/
void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	other = n;
	Hero* temp_hero = CheckClass::isHero(other);

	optionsIndex = 0;
	player_conv_point_choice = "";
	DialogueController::feedback_timer = 0;
	curr_hero_topic = "";

	/*Helps determine what the greeting phrase should be based on whether or not the player
	has taken or completed a quest from the npc, or if the player has advised an npc
	to do something.*/
	if (temp_hero) {
		init_dialogue_options(temp_hero);

		if (temp_hero->SUGG_ACT_STATUS == 2)
			show_advice_feedback = 1;
		else if (temp_hero->SUGG_ACT_STATUS == 3)
			show_advice_feedback = 2;

		Planner* planner = AIController::get_plan(temp_hero->name);

		/*Used to determine if player already has a quest from the
		npc they are talking to and to determine if the player has
		completed a quest from that npc.*/
		bool player_doing_quest = false;
		bool quest_complete = false;

		for (int i = 0; i < planner->quests_given.size(); ++i) {
			if (planner->quests_given[i]->getDoer()->name == SHANGO && 
				planner->quests_given[i]->executed == false) 
			{
				player_doing_quest = true;
			}

			if (planner->quests_given[i]->getDoer()->name == SHANGO && 
				(planner->quests_given[i]->executed == true || 
				(player->quest_status[temp_hero->name] == Player::SUCC_QUEST || 
				 player->quest_status[temp_hero->name] == Player::FAIL_QUEST))) 
			{
				quest_complete = true;
			}
		}
		initiate_quest_completion(quest_complete,player_doing_quest,temp_hero,planner);
	}
	else
		start_greeting(temp_hero);

	if (playerTalk && temp_hero)
		PlayerChoose();
	else 
		talk_non_hero();
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
	Hero* temp_hero = CheckClass::isHero(other);
	/*does normal exitDialogue stuff if "other" is not a hero*/
	if (state == 7 || state == 9){
		clear_conversation_logs(temp_hero);

		if (temp_hero && is_hero_act == false) {
			remove_hero_related_conv_points();

			remove_dialog_option("Recruit_For_Party", StrengthIcon);
			remove_dialog_option("Ask_To_Form_Alliance", NotorietyIcon);
			add_dialog_option("Recruit_For_Party", StrengthIcon);
			add_dialog_option("Ask_To_Form_Alliance", NotorietyIcon);
		}
		else {
			Soldier* sold = dynamic_cast<Soldier*>(other);
			if(sold)
			    remove_soldier_opts();
		}
		reset_conversation_vars();
	}
	else {
		state = 7;
		if (temp_hero) {//check if "other" is a hero before seeing if they can offer you a quest
			offer_quest_on_exit(temp_hero);
			/*does normal exitDialogue stuff if quest is not given or if player has denied quest offer*/
			if (quest_declined == true)
				state = 7;
		}
		else
		    exit_non_hero();
	}
}

/*Returns a pointer to the instance of the DialogueHelper class that
the DialogueController uses to call DialogueHelper functions.*/
DialogueHelper* DialogueController::getDialogueHelper()
{
	return &dialogue;
}

/*Adds hero-related conversation points to the 3D vector of possible
conversation points and adds them to the vector of the player's dialog
options. Hero-related conversation points are the ones displayed to
the player with a hero's name in them.*/
void DialogueController::add_hero_related_conv_points() {
	options = dialogue.get_possible_conv_pts();

	add_question_pts();

	add_notoriety_pts();
}

/*Removes hero-related conversation points from the 3D vector of possible
conversation points and removes them from the vector of the player's dialog
options.*/
void DialogueController::remove_hero_related_conv_points() {
	remove_question_pts();

	remove_notoriety_pts();
}

/*Replaces all appearances of "from" in "str" with "to". Used for filling dialogue
templates with appropriate hero and action names.*/
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
		for (auto i : player->quest_status) {
			if (i.first == temp_hero->name && i.second == Player::IN_PROGRESS)
				offered_quest = true;
		}

		if (has_quest == false && quest_declined == false && offered_quest == false) {

			initiate_quest_offer(temp_hero);

			select = 0;
			state = 2;
			offered_quest = true;
			scroll_control = 0;
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
	soldier_options.clear();
}

void DialogueController::remove_babalawo_opts() {
	babalawo_options.clear();
}

/*Adds a conversation log entry to an NPC's permanent conversation log if
the NPC does not already have an entry identical to that one in their log.
Otherwise, it does nothing.*/
void DialogueController::add_to_perm_storage(ConversationLogObj* log_entry, Hero* temp_hero) {
	for (int i = 0; i < temp_hero->conversation_log.size(); ++i) {
		if (temp_hero->conversation_log[i]->get_conv_point() == log_entry->get_conv_point()
			&& temp_hero->conversation_log[i]->get_who() == log_entry->get_who()
			&& temp_hero->conversation_log[i]->get_topic() == log_entry->get_topic())
		{
			return;
	    }
    }

	temp_hero->conversation_log.push_back(log_entry);
}

/*used to cause player to scroll to nearest selectable option when they 
are scrolling down. unselectable options are skipped.*/
void DialogueController::move_to_selectable_down() {
	int scroll_counter = 0;
	bool selectable_found = false;
	Hero* temp_hero = CheckClass::isHero(other);

	if (check_down_cases(temp_hero))
		return;

	/*Searches for nearest selectable option and increments scroll counter until found.
	Scroll counter is used to move the player downward to the nearest selectable option in
	the list.*/
	if (temp_hero && state != 2) {
		for (int i = 0; (DialogueController::scroll_control + i) < DialogueController::getOptions().size(); ++i) {
			if (DialogueController::getOptions()[DialogueController::scroll_control + i][IsSelectable] == "1") {
				if ((i != 0) || (DialogueController::getOptions().size() == 2 && 
					DialogueController::getOptions()[1][IsSelectable] == "1")) 
				{
					selectable_found = true;
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
			if (DialogueController::get_babalawo_options()[DialogueController::scroll_control + i]
				[IsSelectable] == "1") 
			{
				if (i != 0 || (DialogueController::get_babalawo_options().size() == 2 && 
					DialogueController::get_babalawo_options()[1][IsSelectable] == "1"))
				{
					selectable_found = true;
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

	if(selectable_found)
	    DialogueController::scroll_control += scroll_counter;
}

/*used to cause player to scroll to nearest selectable option when they
are scrolling up. unselectable options are skipped.*/
void DialogueController::move_to_selectable_up() {
	int scroll_counter = 0;
	if (DialogueController::scroll_control == 0)
		return;

	if (state != 2) {
		Hero* temp_hero = CheckClass::isHero(other);
		for (int i = 0; (DialogueController::scroll_control - i) >= 1; ++i) {
			scroll_counter++;
			if (temp_hero) {
				if (DialogueController::getOptions()
					[DialogueController::scroll_control - i - 1][IsSelectable] == "1") 
				{
					break;
				}
			}
			else {//babalawo case
				if (DialogueController::get_babalawo_options()
					[DialogueController::scroll_control - i - 1][IsSelectable] == "1") 
				{
					break;
				}
			}
		}
	}
	else
		++scroll_counter;

	DialogueController::scroll_control -= scroll_counter;
}

/*Sets whether or not a dialog option is selectable. The option whose selectability is
to be set is determined by the option's name and the icon that it goes under. The first
arg specifies if we are setting the option to be selectable or unselectable.*/
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

/*Adds a dialog option to player's list of options. Option to add is specified 
by the name of the option to add, and the icon that the option should go under.*/
void DialogueController::add_dialog_option(std::string option_name, int icon){
	dialogue_point tmp_dpoint;
	tmp_dpoint = Containers::conv_point_table[option_name]->dpoint;
	dialogue.get_possible_conv_pts_ref()[icon].push_back(tmp_dpoint);
	options = dialogue.get_possible_conv_pts();
}

/*Removes a dialog option from player's list of options. Option to remove is specified 
by the name of the option to remove, and the icon that the option is currently 
associated with.*/
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
/*Andrew's version of my check_advice_acceptance function. Used for social actions.*/
bool DialogueController::check_acceptance(Player* p, Hero* npc) {
	std::string::size_type name_end = p->cur_action->getName().find_last_of('_');
	std::string act_name = p->cur_action->getName().substr(0, name_end);

	int range_cap = npc->get_range_cap(p->cur_action);
	for (auto i : curr_conversation_log) {
		if (i->get_who() == SHANGO && i->get_conv_point()->get_name() == act_name)
			range_cap = range_cap / 2;
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
		dpoint = load_yemoja_lesson();

	}
	else if (npc->name == OYA) {
		dpoint = load_oya_lesson();
	}
	else {
		dpoint = load_ogun_lesson();

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
	DialogueController::feedback_timer = 0;
	state = 7;

}

void DialogueController::spar_pop_up(Action* act)
{
	other = act->getReceiver();
	dialogue_point dpoint = {"Finish Spar","Finish Spar"};
	std::string conversation_pt_sentence = dialogue.gen_dialog(dpoint, act->getReceiver());
	message = act->getReceiver()->getName() + ": " + conversation_pt_sentence;
	DialogueController::feedback_timer_2 = 0;
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

/*Calls function to apply post conditions based on whether or not the player reacted
  postively to the npc's action. If the action is a suggested action, it's status gets
  set based on whether or not the player accepted the action.*/
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

/*Moves any unselectable dialogue options to the bottom of the player's list
of options. Used to prevent player from starting on unselectable options.*/
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

	options = dialogue.get_possible_conv_pts();
}

/*creates a conversation log entry and initializes the entry's values.
Does NOT handle the adding of the new entry to a conversation log.*/
ConversationLogObj* DialogueController::create_conv_log_entry(dialogue_point dp, int person, ConversationPoint* conv_point) {
	ConversationLogObj* conv_log_obj = new ConversationLogObj();
	Memory* mem = nullptr;

	conv_log_obj->set_who(person);
	conv_log_obj->set_conv_point(conv_point);


	/*set the topic for the log entry of the player's selection.
	If player's selection has no topic, the topic is set to a value
	that indicates that there is no topic asscoiated with their
	conversation point.*/
	if (dp[ConvPointName].find("Advise To") != string::npos || dp[ConvPointName].find("Ask About") != 
		string::npos) 
	{
		conv_log_obj->set_topic(dialogue.hero_name_to_int(dp[Topic]), mem);
		curr_hero_topic = dp[Topic];
	}
	else if(dp[ConvPointName].find("Take Advice") != string::npos || 
		    dp[ConvPointName].find("Tell About") != string::npos) 
	{
		conv_log_obj->set_topic(dialogue.hero_name_to_int(dp[Topic]), mem);
	}
	else
		conv_log_obj->set_topic(NoTopic, mem);

	return conv_log_obj;
}

/*Adjusts the number of entries in the conversation log for current conversation
if the current number exceeds the max allowed.*/
void DialogueController::limit_log_size() {
	if (curr_conversation_log.size() > 32) {
		delete curr_conversation_log[0];
		curr_conversation_log.erase(curr_conversation_log.begin());
	}
}

/*Sets whether or not an npc reacts positively to the player's action.
  Calls appropriate functions to apply post conditions based on reaction.*/
void DialogueController::set_accepted_action(Hero* temp_hero, dialogue_point choice) {
	    accepted_action = true;

		if (player_conv_point_choice == "Advise To Fight"    || 
			player_conv_point_choice == "Advise To Conquer"  || 
			player_conv_point_choice == "Advise To Ally With"  ) 
		{
			accepted_action = check_advice_acceptance(player, temp_hero);
			if (temp_hero->SUGG_ACT_STATUS == 1)
				accepted_action = false;

			if (accepted_action) {
				Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
				planner->set_action_suggested(true);
			}
		}

		if (player_conv_point_choice =="Bribe"||player_conv_point_choice == "Compliment"|| 
			player_conv_point_choice =="Grovel"||player_conv_point_choice == "Insult"   || 
			player_conv_point_choice =="Boast" ||player_conv_point_choice == "Intimidate") 
		{
		    PlayerActExecFunctions::execute_start(player_conv_point_choice, temp_hero);
			accepted_action = check_acceptance(player, temp_hero);
		}

		for (auto precond : Containers::conv_point_table[player_conv_point_choice]->req_preconds) {
			int temp1 = precond->get_cost(temp_hero, player);
			//the ori stuff means that the higher the ori the more likely it is for the hero to respond
			//positivly to what whatever it is you are saying
			if (precond->get_cost(temp_hero, player) - (player->ori / 5) <= 0) {
				std::cout << "a string: " << precond->get_cost(temp_hero, player) 
					      << std::endl;
			}
			else {
				accepted_action = false;
			}
		}

		if (player_conv_point_choice =="Bribe"|| player_conv_point_choice == "Compliment"     || 
			player_conv_point_choice =="Grovel"|| player_conv_point_choice == "Insult"        || 
			player_conv_point_choice =="Boast"|| player_conv_point_choice == "Advise To Fight"|| 
			player_conv_point_choice =="Advise To Conquer"                                    || 
			player_conv_point_choice =="Advise To Ally With"                                  || 
			player_conv_point_choice =="Intimidate")
		{
			if (accepted_action)
				Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(true, player, temp_hero);
			else
				Containers::conv_point_table[player_conv_point_choice]->apply_postconditions(false, player, temp_hero);
		}

		dialogue.act_accepted = accepted_action;
}

/*Sets whether or not an npc decides to teach the player a skill.*/
void DialogueController::set_accepted_teaching(Hero* temp_hero) {
	
		//the ori variable is to increase the chance of teaching based on
		//how high the ori is 
		if (temp_hero->rel[player->name]->getAffinity() + (player->ori / 10) >= 55 &&
			temp_hero->rel[player->name]->getStrength() + (player->ori / 10) >= 55) 
		{
			accepted_action = true;
		}
		else
		    accepted_action = false;

		//sets hero to respond negatively if they already taught player their skill
		if (player->can_fire && temp_hero->name == YEMOJA) {//case where player already learned Yemoja's move
			accepted_action = false;
		}

		if (player->can_spin && temp_hero->name == OYA) {//case where player already learned Oya's move
			accepted_action = false;
		}

		if (player->can_shield && temp_hero->name == OGUN) {//case where player already learned Ogun's move
			accepted_action = false;
		}

		dialogue.act_accepted = accepted_action;
}

/*Adds a hero to the player's vector of heroes that the player knows if
  the player asks for a hero's name and if the hero to be added is not
  already present in the aforementioned vector.*/
void DialogueController::add_known_hero() {
		bool already_know = false;
		for (int i = 0; i < player->heroes_player_knows.size(); ++i) {
			if (dialogue.hero_name_to_int(DialogueController::getOther()->getName())
				== player->heroes_player_knows[i])
			{
				already_know = true;
			}
		}
		if (!already_know)
		    player->heroes_player_knows.push_back(dialogue.hero_name_to_int(other->getName()));
}

/*Calls execution function(s) and sets npc dialogue based on whether the player 
  replies accepting or declining an alliance offer, a duel, or a spar.*/
void DialogueController::start_event() {
	Hero* temp_hero = CheckClass::isHero(other);
	dialogue_point diog_pt;

	if (player_conv_point_choice == "Accept Alliance Offer") {
		diog_pt = { "Confirm Alliance","Confirm Alliance" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
		if (temp_hero->getVillage()->get_alliance() != player->getVillage()->get_alliance()) {
			PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);
			PlayerActExecFunctions::execute_end(true);
		}
	}
	else if (player_conv_point_choice == "Accept Duel") {
		diog_pt = { "Confirm Duel","Confirm Duel" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
		PlayerActExecFunctions::execute_start("Duel", temp_hero);
	}
	else if (player_conv_point_choice == "Accept Spar Request") {
		diog_pt = { "Confirm Spar","Confirm Spar" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
		PlayerActExecFunctions::execute_start("Spar", temp_hero);
	}
}

/*Sets the npc's reaction to the player's response and calls functions to apply the
  post conditions for the action. */
void DialogueController::set_response_reaction(dialogue_point dp, Hero* temp_hero) {
	if (dp[ConvPointName] == "Boast In Response" || dp[ConvPointName] == "Intimidate In Response" ||
		dp[ConvPointName] == "Insult In Response"|| dp[ConvPointName] == "Compliment In Response" ||
		dp[ConvPointName] == "Offer Praise In Response")
	{
		std::string::size_type reply_end = dp[ConvPointName].find_last_of(' ');
		std::string act_name = dp[ConvPointName].substr(0, reply_end);
		reply_end = act_name.find_last_of(' ');
		act_name = dp[ConvPointName].substr(0, reply_end);

		if (act_name == "Offer Praise")
	        act_name = "Grovel";

		DialogueController::react_positively = true;

		for (auto precond : Containers::conv_point_table[act_name]->req_preconds) {
			int temp1 = precond->get_cost(temp_hero, player);
			//the ori stuff means that the higher the ori the more likely it is for the hero to respond
			//positivly to what whatever it is you are saying
			if (precond->get_cost(temp_hero, player) - (player->ori / 5) <= 0)
				std::cout << "a string: " << precond->get_cost(temp_hero, player) << std::endl;
			else
				DialogueController::react_positively = false;

			if (DialogueController::react_positively) {
				vis_feedback.second = act_name;

				Containers::conv_point_table[act_name]->apply_postconditions(true, player, temp_hero);
			}
			else {
				vis_feedback.second = act_name;

				Containers::conv_point_table[act_name]->apply_postconditions(false, player, temp_hero);
			}
		}
	}
}

/*Calls function to add a quest to the player's quest log if they decide to accept
  an npc's quest offer. */
void DialogueController::accept_quest(dialogue_point dp) {
		Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
		if (dp[ConvPointName] == "Accept_Quest") {
			quest->setDoer(player);

			player->quest_status[quest->getOwner()->name] = 1;
			int time_limit = 3600;
			player->add_quest(quest, time_limit);
			player->quests_log.push_back(quest);
			planner->quests_given.push_back(quest); //gives npc record of what they gave player

            //make sure player can still quit GUI if they accepted a quest when they were about 
			//to exit already
			first_q_press = false;
		}

		if (dp[ConvPointName] == "Decline_Quest") {
			quest_declined = true;
			state = 10;
		}
}

/*skips the player's reply point if the npc does not say a conversation
  point, if the npc tells the player that they already asked them something,
  if an npc runs out of relevant conversation points to say, or if an NPC tells
  the player that they do not have a quest for them. If skipped, conversation
  returns to playerConversationPoint.*/
void DialogueController::skip_player_reply(dialogue_point point, dialogue_point line, std::string reply_pt_sentence, std::string con_pt_sentence, Hero* temp_hero) {
	if (point[ConvPointName] != "No_More_Phrases" && line[ConvPointName] != 
		"Already_Asked" && point[ConvPointName] != "" && point[ConvPointName] != 
		"No Quest") 
	{
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
}

/*Formats the string for the npc's quest sentence based on the 
  quest so that the sentence will be gramatically correct.*/
void DialogueController::format_quest_str(ConversationLogObj* conv_log_obj2, std::string& con_pt_sentence ) {
	Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
	DialogueController::quest = planner->get_current_action();
	Memory* mem2 = nullptr;
	conv_log_obj2->set_topic(quest->getReceiver()->name, mem2);

	//these two lines strip the number off the end of the name 
	std::string::size_type name_end = quest->name.find_last_of('_');
	std::string act_name = quest->name.substr(0, name_end);

	std::string village = "'s village";
	std::string hero_name = dialogue.int_to_hero_name(quest->getReceiver()->name);

	player->quest_status[quest->getOwner()->name] = 1;// set shango to "doing quest"

	if (act_name.find("Conquer") != string::npos || act_name.find("Occupy") != 
		string::npos) 
	{
		replace_all(con_pt_sentence, "HERO", hero_name + village);
	}
	else if (act_name.find("Bribe") != string::npos) {
		std::string gift = "offer a gift to";
		replace_all(con_pt_sentence, "HERO", hero_name);
		replace_all(con_pt_sentence, "ACTION", gift);
	}
	else if (act_name.find("Boast") != string::npos) {
		std::string to = " to";
		replace_all(con_pt_sentence, "HERO", hero_name);
		replace_all(con_pt_sentence, "ACTION", act_name + to);
	}
	else if (act_name.find("Grovel") != string::npos) {
		std::string praise = "offer praise to ";
		replace_all(con_pt_sentence, "HERO", hero_name);
		replace_all(con_pt_sentence, "ACTION", praise);
	}
	else if (act_name.find("Form_Alliance") != string::npos) {
		replace_all(con_pt_sentence, "HERO", hero_name);
		replace_all(con_pt_sentence, "ACTION", "form an alliance with ");
	}
	else if (act_name.find("Spar") != string::npos) {
		replace_all(con_pt_sentence, "HERO", hero_name);
		replace_all(con_pt_sentence, "ACTION", "spar with ");
	}
	else if (act_name.find("Train") != string::npos || act_name.find("Spar") != 
		     string::npos || act_name.find("Form_Alliance") != string::npos) 
	{
		std::string with = "";
		with = " with ";
		replace_all(con_pt_sentence, "ACTION", act_name + with);
	}
	else
		replace_all(con_pt_sentence, "ACTION", act_name);
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  alliance offer. Calls function to end "alliance" execution.*/
void DialogueController::finish_alliance(Hero* temp_hero) {
	//choose different dialog if they denied the action
	if (accepted_action) {
		dialogue_point diog_pt = { "Confirm Alliance","Confirm Alliance","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";
		if (temp_hero->getVillage()->get_alliance() != player->getVillage()->get_alliance())
			PlayerActExecFunctions::execute_end(true);
	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////

		dialogue_point diog_pt = { "Confirm Alliance","Confirm Alliance","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		//calls action end if the question is denied otherwise called on cmpletion of the action
		if (temp_hero->getVillage()->get_alliance() != player->getVillage()->get_alliance())
			PlayerActExecFunctions::execute_end(false);
	}

	state = 9;
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  challenge to a duel. Calls function to end "duel" execution.*/
void DialogueController::finish_duel() {
	//choose different dialog if they denied the action
	if (accepted_action) {
		dialogue_point diog_pt = { "Confirm Duel","Confirm Duel","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";
	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Confirm Duel","Confirm Duel","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		//calls action end if the question is denied otherwise called on cmpletion of the action
		PlayerActExecFunctions::execute_end(false);
	}
	
	state = 9;
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  request to spar. Calls function to end "spar" execution.*/
void DialogueController::finish_spar() {
	//choose different dialog if they denied the action
	if (accepted_action) {
		dialogue_point diog_pt = { "Confirm Spar","Confirm Spar","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";
	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Confirm Spar","Confirm Spar","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		//calls action end if the question is denied otherwise called on cmpletion of the action
		PlayerActExecFunctions::execute_end(false);
	}
	
	state = 9;
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  advice to fight another npc. Calls function to begin fight execution.*/
void DialogueController::finish_fight_advice(Hero* temp_hero) {
	//choose different dialog if they denied the action
	if (accepted_action) {
		dialogue_point diog_pt = { "Confirm Fight","Confirm Fight","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
		int hero_num = dialogue.hero_name_to_int(curr_hero_topic);
		std::string hero_id = std::to_string(temp_hero->name);
		std::string act_str = "Fight_" + hero_id + "-" + std::to_string(hero_num);

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

	}
	
	state = 9;
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  advice to conquer another npc's village. Calls function to begin "conquer" execution.*/
void DialogueController::finish_conquer_advice(Hero* temp_hero) {
	//choose different dialog if they denied the action
	if (accepted_action) {
		dialogue_point diog_pt = { "Confirm Conquer","Confirm Conquer","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);

		int hero_num = dialogue.hero_name_to_int(curr_hero_topic);

		std::string hero_id = std::to_string(temp_hero->name);
		std::string act_str = "Conquer_" + hero_id + "-" + std::to_string(hero_num);
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
	}
	
	state = 9;
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  advice to send a peace offering to another npc. */
void DialogueController::finish_peace_advice() {
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

	}

	state = 9;
}

/*Sets player dialogue based on whether or not the npc decided to accept the player's
  advice to ally with another npc. Calls function to begin "alliance" execution.*/
void DialogueController::finish_ally_advice(Hero* temp_hero) {
	//choose different dialog if they denied the action
	if (Containers::hero_table[curr_hero_topic]->getVillage()->get_alliance() == 
		temp_hero->getVillage()->get_alliance()) 
	{
		dialogue_point diog_pt = { "Already Allies","Already Allies","",curr_hero_topic,"1"};
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
	}
	else if (accepted_action) {
		dialogue_point diog_pt = { "Confirm Ally","Confirm Ally","",curr_hero_topic,"1"};
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, player);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";

		Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);

		int hero_num = dialogue.hero_name_to_int(curr_hero_topic);

		std::string hero_id = std::to_string(temp_hero->name);
		std::string act_str = "Form_Alliance_" + hero_id + "-" + std::to_string(hero_num);
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

	}
	
	state = 9;
}

/*Sets player and npc dialogue based on whether or not the npc decided to accept 
  the player's request for teaching. Enables the player to use new skill if the npc
  decided to teach them.*/
void DialogueController::finish_teach(Hero* temp_hero) {
	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt;
		if (temp_hero->name == YEMOJA) { //if Yemoja is doing the teaching
			diog_pt = { "Teach Fireball","Teach Fireball","",curr_hero_topic,"1" };
			player->can_fire = true;//enable player to shoot fireball
		}
		else if (temp_hero->name == OYA) {//if Oya is doing the teaching
			diog_pt = { "Teach Spin","Teach Spin","",curr_hero_topic,"1" };
			player->can_spin = true;//enable player to do spin slash
		}
		else {//if Ogun is doing the teaching
			diog_pt = { "Teach Shield","Teach Shield","",curr_hero_topic,"1" };
			player->can_shield = true;//enable player to do flame shield
		}
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
		state = 12;
	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Confirm Teach","Confirm Teach","",curr_hero_topic,"1"};
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, player);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = player->getName() + ": " + reply_pt_sentence + "\n\n";
		state = 9;
	}
}

/*Sets npc dialogue for joining the player's party.*/
void DialogueController::finish_recruit(Hero* temp_hero, dialogue_point dp){
	if (temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance()) {
		player->getParty()->add_party_to_party(temp_hero->getParty());
		std::string reply_pt_sentence = dialogue.gen_dialog(dp, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
	}
	else { //they will say no if not part of same alliance as you
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(dp, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
	}
	state = 7;
}

/*Sets npc dialogue based on whether or not they react positively to the player's 
  intimidation. Calls function to end "intimidation" execution.*/
void DialogueController::resolve_talk_back(dialogue_point line, Hero* temp_hero) {
	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt = { "Talk Back","Talk Back","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
		PlayerActExecFunctions::execute_end(true);
	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Talk Back","Talk Back","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
		PlayerActExecFunctions::execute_end(false);
	}

	state = 3;
	otherConversationPoint(line);
}

/*Sets npc dialogue based on whether or not they decide to react positively to the player's
  praise. Calls function to end "offer praise" execution.*/
void DialogueController::resolve_plea(dialogue_point line, Hero* temp_hero) {
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

/*Sets npc dialogue based on whether or not they react positively to the player's
  boast. Calls function to end "boast" execution.*/
void DialogueController::resolve_congratulate(dialogue_point line, Hero* temp_hero) {
	
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

/*Sets npc dialogue based on whether or not they react positively to the player's
  compliment. Calls funciton to end "compliment" execution.*/
void DialogueController::resolve_thank(dialogue_point line, Hero* temp_hero) {
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
		PlayerActExecFunctions::execute_end(false);
	}

	state = 3;
	otherConversationPoint(line);
}

/*Sets npc dialogue based on whether or not they react postively to the player's
  insult. Calls function to end "insult" execution.*/
void DialogueController::resolve_defend(dialogue_point line, Hero* temp_hero) {

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

/*Sets npc dialogue based on whether or not they react positively to the player's
  gift. Calls function to end the "offer gift" execution.*/
void DialogueController::resolve_bribe(dialogue_point line, Hero* temp_hero) {
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

/*Sets npc dialogue based on whether or not they decide to teach the player
  a skill. Increases the player's strength if the npc chooses to teach them.*/
void DialogueController::initiate_teach(Hero* temp_hero) {
	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt = { "Teach","Teach","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
		dynamic_cast<Hero*>(other)->rel[1]->addStrength(10);

	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt;
		if ((temp_hero->name == YEMOJA && player->can_fire) || 
			(temp_hero->name == OYA && player->can_spin)    || 
			(temp_hero->name == OGUN && player->can_shield))
		{ 
			diog_pt = { "Already Taught","Already Taught","",curr_hero_topic,"1" };
		}
		else
			diog_pt = { "Teach","Teach","",curr_hero_topic,"1" };

		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
	}

	state = 8;
	dialogue.state_is_8 = true;
}

/*Sets npc dialogue based on whether or not they decide to take the player's
  advice to ally with another npc.*/
void DialogueController::initiate_ally_advice(Hero* temp_hero) {

	//checks if this hero is already allies with the hero that the player is suggesting an alliance with
	if (Containers::hero_table[curr_hero_topic]->getVillage()->get_alliance() == temp_hero->getVillage()->get_alliance()) {
		dialogue_point diog_pt = { "Already Allies","Already Allies","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
	}
	//check if I want to accept
	else if (accepted_action) {
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
	dialogue.state_is_8 = true;
}

/*Sets npc dialogue based on whether or not they decide to take the player's
  advice to conquer another npc's village.*/
void DialogueController::initiate_conquer(Hero* temp_hero) {
	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt = { "Take Advice To Conquer","Take Advice To Conquer","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");

	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Take Advice To Conquer","Take Advice To Conquer","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");

	}

	state = 8;
	dialogue.state_is_8 = true;
}

/*Sets npc dialogue based on whether or not they decide to take the player's
  advice to fight another npc.*/
void DialogueController::initiate_advice_fight(Hero* temp_hero) {
	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt = { "Take Advice To Fight","Take Advice To Fight","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");

	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Take Advice To Fight","Take Advice To Fight","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
		replace_all(reply_pt_sentence, "HERO", curr_hero_topic);
		message = check_if_known(reply_pt_sentence, "");
	}

	state = 8;
	dialogue.state_is_8 = true;
}

/*Sets npc dialogue based on whether or not they decide to accept the player's
  request to spar. Calls function to execute the spar.*/
void DialogueController::initiate_spar(Hero* temp_hero) {
	//calls action start if the question is asked at all
	PlayerActExecFunctions::execute_start("Spar", temp_hero);

	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt = { "Accept Spar Request","Accept Spar Request","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");

	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Accept Spar Request","Accept Spar Request","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");

	}

	state = 8;
	dialogue.state_is_8 = true;
}

/*Sets npc dialogue based on whether or not they decide to accept the player's
  challenge to a duel. Calls function to execute the duel.*/
void DialogueController::initiate_duel(Hero* temp_hero) {
	//calls action start if the question is asked at all
	PlayerActExecFunctions::execute_start("Duel", temp_hero);

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
	dialogue.state_is_8 = true;
}

/*Sets npc dialogue based on whether or not they decide to accept the player's 
  alliance offer. Calls function to execute the alliance.*/
void DialogueController::initiate_alliance(Hero* temp_hero) {
	if (temp_hero->getVillage()->get_alliance() != player->getVillage()->get_alliance())
		PlayerActExecFunctions::execute_start("Form_Alliance", temp_hero);

	//check if I want to accept
	if (accepted_action) {
		dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
	}
	else {
		/////////////need to be changed to correct calls/dialog if not accepted///////////////////
		dialogue_point diog_pt = { "Accept Alliance Offer","Accept Alliance Offer","",curr_hero_topic,"1" };
		std::string reply_pt_sentence = dialogue.gen_dialog_negative(diog_pt, temp_hero);
		message = check_if_known(reply_pt_sentence, "");
	}

	state = 8;
	dialogue.state_is_8 = true;
}

void DialogueController::load_divination(std::string reply_pt_sentence, std::string name_str) {
	if (other->getName().find("Oasis") != string::npos)
	{
		if (!DialogueController::talked_to_babalawo_o)
		{
			//give shrine blessing
			player->addHealth(300);//regenerate to full he
			player->ori += 20;//boost ori by 30
		}
		else {
			dialogue_point diog_pt = { "No Divination","No Divination","","","1"};
			reply_pt_sentence = dialogue.gen_dialog_babalawo(diog_pt, other);
			message = name_str + ": " + reply_pt_sentence + "\n\n";

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
			dialogue_point diog_pt = { "No Divination","No Divination","","","1"};
			reply_pt_sentence = dialogue.gen_dialog_babalawo(diog_pt, other);
			message = name_str + ": " + reply_pt_sentence + "\n\n";

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
			dialogue_point diog_pt = { "No Divination","No Divination","","","1"};
			reply_pt_sentence = dialogue.gen_dialog_babalawo(diog_pt, other);
			message = name_str + ": " + reply_pt_sentence + "\n\n";

		}
	}
}

/*Is called instead of PlayerChoose() function if player is speaking to non-hero npc.
Calls the appropriate functions based on if the player is interacting with a 
babalawo, soldier, shrine, or villager and sets the correct greeting.*/
void DialogueController::talk_non_hero() {
	Soldier* soldier;
	soldier = dynamic_cast<Soldier*>(other);
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
				std::string name_str = other->getName();
				replace_all(name_str, "_", " ");
				message = name_str + ": " + dialogue.gen_dialog_babalawo({ "Greeting","Greeting" }, other);
			}
			else if (other->getName().find("Shrine") != string::npos)//if player interacting with shrine
				shrine_interact();
			else//otherwise player is interacting with a villager
				villager_interact();
		}
	}
}

/*Used when a conversation first starts.Adds the appropriate dialog options to the 
list of options available to the player based on who the player is speaking to. Sets 
whether or not available options are selectable when a conversation starts.*/
void DialogueController::init_dialogue_options(Hero* temp_hero) {
	if (temp_hero->getVillage()->get_alliance() == player->getVillage()->get_alliance())
		remove_dialog_option("Ask_To_Form_Alliance", NotorietyIcon);

	if (temp_hero->getParty() == player->getParty())
		remove_dialog_option("Recruit_For_Party", StrengthIcon);

	remove_dialog_option("Ask_To_Duel", NotorietyIcon);
	remove_dialog_option("Ask_To_Spar", StrengthIcon);
	add_dialog_option("Ask_To_Duel", NotorietyIcon);
	add_dialog_option("Ask_To_Spar", StrengthIcon);

	if (temp_hero->rel[player->name]->getAffinity() <= 30 && temp_hero->rel[player->name]->getStrength() <= 60)
		set_selectable(true, "Ask_To_Duel", NotorietyIcon);
	else
		set_selectable(false, "Ask_To_Duel", NotorietyIcon);

	if (temp_hero->rel[player->name]->getStrength() >= 55 && temp_hero->rel[player->name]->getAffinity() >= 60)
		set_selectable(true, "Ask_To_Spar", StrengthIcon);
	else
		set_selectable(false, "Ask_To_Spar", StrengthIcon);

	if (temp_hero->getParty() != player->getParty())
		set_selectable(true, "Recruit_For_Party", StrengthIcon);
	else
		set_selectable(false, "Recruit_For_Party", StrengthIcon);

	if (temp_hero->rel[player->name]->getAffinity() + (player->ori / 10) >= 55 &&
		temp_hero->rel[player->name]->getStrength() + (player->ori / 10) >= 55)
		set_selectable(true, "Request_Teaching", StrengthIcon);
	else
		set_selectable(false, "Request_Teaching", StrengthIcon);

	if (temp_hero->rel[player->name]->getAffinity() >= 85)
		set_selectable(true, "Ask_To_Form_Alliance", NotorietyIcon);
	else
		set_selectable(false, "Ask_To_Form_Alliance", NotorietyIcon);


	player->filter_move_to(temp_hero);

	unselectable_to_bottom();
}

/*Sets proper greeting message for non-hero npcs, making sure to remove the
underscore(_) and the number that suffix non-hero names by default.*/
void DialogueController::start_greeting(Hero* temp_hero) {
	std::string name_str = other->getName();
	std::string::size_type name_end = name_str.find_last_of('_');
	std::string n_str = name_str.substr(0, name_end);
	replace_all(n_str, "_", " ");
	name_str = n_str;
	message = name_str + ": " + dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero);
}

/*Sets the proper greeting message for the npc that the player is speaking to based on whether 
or not the player has completed a quest for that npc and based on whether or not the player
has advised that npc to do something. Erases the completed quest from both the npc's and the
player's quest logs.*/
void DialogueController::initiate_quest_completion(bool quest_complete, bool player_doing_quest, Hero* temp_hero, Planner* planner) {
	if (quest_complete) {
		quest_complete = false;

		if (player->quest_status[temp_hero->name] == Player::SUCC_QUEST) {
			message = check_if_known(dialogue.gen_dialog({ "Quest_Complete","Quest_Complete" }, temp_hero), "");
			player->quest_status[temp_hero->name] = Player::NOT_QUEST;
		}
		else if (player->quest_status[temp_hero->name] == Player::FAIL_QUEST) {
			message = check_if_known(dialogue.gen_dialog({ "Quest_Failed","Quest_Failed" }, temp_hero), "");
			player->quest_status[temp_hero->name] = Player::NOT_QUEST;
		}

		for (int i = 0; i < planner->quests_given.size();) {
			if (planner->quests_given[i]->getDoer()->name == SHANGO)
				planner->quests_given.erase(planner->quests_given.begin() + i);
			else
				++i;
		}
		for (int i = 0; i < player->quests_log.size();) {
			if (player->quests_log[i]->getOwner()->name == temp_hero->name) {
				player->remove_quest(player->quests_log[i]);//remove from "quests" map
				player->quests_log.erase(player->quests_log.begin() + i);//erase from player's quests log
			}
			else
				++i;
		}
	}
	else if (player_doing_quest && temp_hero->SUGG_ACT_STATUS == 0) {
		message = check_if_known(dialogue.gen_dialog({ "Quest_In_Progress","Quest_In_Progress" }, temp_hero), "");
	}
	else if (temp_hero->SUGG_ACT_STATUS == 2) {
		message = check_if_known(dialogue.gen_dialog({ "Terrible Advice","Terrible Advice" }, temp_hero), "");
		temp_hero->SUGG_ACT_STATUS = 0;
	}
	else if (temp_hero->SUGG_ACT_STATUS == 3) {
		message = check_if_known(dialogue.gen_dialog({ "Good Advice","Good Advice" }, temp_hero), "");
		temp_hero->SUGG_ACT_STATUS = 0;
	}
	else
		message = check_if_known(dialogue.gen_dialog({ "Greeting","Greeting" }, temp_hero), "");
}

void DialogueController::clear_conversation_logs(Hero* temp_hero) {
	//removes all conversation log entries from the log for the current conversation
	for (int i = 0; i < curr_conversation_log.size(); i++) {

		if (curr_conversation_log[i] != nullptr)
			delete curr_conversation_log[i];
	}
	curr_conversation_log.clear();

	//removes unwanted conversation log entries from NPC's permanent storage
	if (temp_hero) {
		for (int i = 0; i < temp_hero->conversation_log.size(); ) {

			if (temp_hero->conversation_log[i] != nullptr) {
				if (temp_hero->conversation_log[i]->get_conv_point()->get_name() != "Ask_Name"
					&& temp_hero->conversation_log[i]->get_conv_point()->get_name() != "Ask_Origin") 
				{
					delete temp_hero->conversation_log[i];
					temp_hero->conversation_log.erase(temp_hero->conversation_log.begin() + i);
				}
				else
					++i;
			}
		}
	}
}

void DialogueController::exit_non_hero() {
	std::string name_str = other->getName();
	replace_all(name_str, "_", " ");
	Soldier* my_sol = dynamic_cast<Soldier*>(other);
	if (!my_sol)//make babalawo farewell appear on exit
		message = name_str + ": " + dialogue.gen_dialog_babalawo({ "Farewell","Farewell" }, other);

	remove_soldier_opts();
	remove_babalawo_opts();
}

void DialogueController::reset_conversation_vars() {
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

void DialogueController::add_question_pts() {
	/*Adds hero-related conversation points to player's vector of dialogue options
	and to their 3D vector of possible conversation points for conversation points
	associated with the question mark icon*/
	dialogue_point tmp_dpoint;
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
		if (itor->second->get_name() == "Ask_For_Quest") {
			tmp_dpoint = itor->second->dpoint;
			options[QuestionMarkIcon].push_back(tmp_dpoint);
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].push_back(tmp_dpoint);
		}
		for (int j = 0; j < player->heroes_player_knows.size(); ++j) {
			if (player->heroes_player_knows[j] != dialogue.hero_name_to_int(other->getName())) {
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Ask About", 0) != 
					string::npos && itor->second->dpoint[CorrespondingConvPt] == "") 
				{
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[Topic] = dialogue.int_to_hero_name(player->heroes_player_knows[j]);
					options[QuestionMarkIcon].push_back(tmp_dpoint);
					dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].push_back(tmp_dpoint);
				}
			}
		}
	}
}

void DialogueController::add_notoriety_pts() {
	/*Adds hero-related conversation points to player's vector of dialogue options
	and to their 3D vector of possible conversation points for conversation points
	associated with the notoriety icon*/
	dialogue_point tmp_dpoint;
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
		for (int j = 0; j < player->heroes_player_knows.size(); ++j) {
			if (player->heroes_player_knows[j] != dialogue.hero_name_to_int(other->getName())) {
				if (itor->second->get_topic() != "" && itor->second->get_name().find("Advise To", 0) != 
					string::npos && itor->second->dpoint[CorrespondingConvPt] == "") 
				{
					tmp_dpoint = itor->second->dpoint;
					tmp_dpoint[Topic] = dialogue.int_to_hero_name(player->heroes_player_knows[j]);
					if (player->move_to_flags.find(itor->second->get_name()) != player->move_to_flags.end()) {
						if (player->move_to_flags[itor->second->get_name()] == 1)
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

void DialogueController::remove_question_pts() {
	/*removes hero-related conversation points that are associated with the
	question mark icon from player's dialog options vector */
	for (int i = 0; i < options[QuestionMarkIcon].size();) {
		if (options[QuestionMarkIcon][i][ConvPointName].find("Advise To", 0) != string::npos || 
			options[QuestionMarkIcon][i][ConvPointName].find("Ask About", 0) != string::npos || 
			options[QuestionMarkIcon][i][ConvPointName].find("Ask_For_Quest", 0) != string::npos) 
		{
			options[QuestionMarkIcon].erase(options[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible
	conversation points that are associated with the question mark icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].size();) {
		if (dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Advise To", 0) != string::npos || 
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Ask About", 0) != string::npos || 
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon][i][ConvPointName].find("Ask_For_Quest", 0) != string::npos) 
		{
			dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].erase(dialogue.get_possible_conv_pts_ref()[QuestionMarkIcon].begin() + i);
		}
		else
			++i;
	}

}

void DialogueController::remove_notoriety_pts() {
	/*removes hero-related conversation points that are associated with the
	notoriety icon from player's dialog options vector */
	for (int i = 0; i < options[NotorietyIcon].size();) {
		if (options[NotorietyIcon][i][ConvPointName].find("Advise To", 0) != string::npos || 
			options[NotorietyIcon][i][ConvPointName].find("Ask About", 0) != string::npos) 
		{
			options[NotorietyIcon].erase(options[NotorietyIcon].begin() + i);
		}
		else
			++i;
	}

	/*removes hero-related conversation points from 3D vector of possible
	conversation points that are associated with the notoriety icon*/
	for (int i = 0; i < dialogue.get_possible_conv_pts_ref()[NotorietyIcon].size();) {
		if (dialogue.get_possible_conv_pts_ref()[NotorietyIcon][i][ConvPointName].find("Advise To", 0) != string::npos || 
			dialogue.get_possible_conv_pts_ref()[NotorietyIcon][i][ConvPointName].find("Ask About", 0) != string::npos) 
		{
			dialogue.get_possible_conv_pts_ref()[NotorietyIcon].erase(dialogue.get_possible_conv_pts_ref()[NotorietyIcon].begin() + i);
		}
		else
			++i;
	}

}

void DialogueController::initiate_quest_offer(Hero* temp_hero) {
	dialogue_point reply_diog_pt = { "Exit Quest","Exit Quest" };
	dialogue_point con_diog_pt = { "Offer_Quest","Offer_Quest" };
	std::string reply_pt_sentence = dialogue.gen_dialog(reply_diog_pt, temp_hero);
	std::string con_pt_sentence = dialogue.gen_dialog(con_diog_pt, temp_hero);
	Planner* planner = AIController::get_plan(CheckClass::isHero(other)->name);
	DialogueController::quest = planner->get_current_action();
	std::string hero_name = dialogue.int_to_hero_name(quest->getReceiver()->name);

	//these two lines strip the number off the end of the name 
	std::string::size_type name_end = quest->name.find_last_of('_');
	std::string act_name = quest->name.substr(0, name_end);

	std::string village = "'s village";
	
	if (act_name == "Bribe")
		replace_all(con_pt_sentence, "ACTION", "offer a gift to");
	else if (act_name.find("Conquer") != string::npos || act_name.find("Occupy") != string::npos) {
		replace_all(con_pt_sentence, "HERO", hero_name + village);
		replace_all(con_pt_sentence, "ACTION", act_name);
	}
	else if (act_name.find("Boast") != string::npos) {
		std::string to = " to";
		replace_all(con_pt_sentence, "ACTION", (act_name + " to"));
	}
	else if (act_name.find("Grovel") != string::npos) {
		std::string praise = "offer praise to ";
		replace_all(con_pt_sentence, "ACTION", praise);
	}
	else if (act_name.find("Form_Alliance") != string::npos) {
		replace_all(con_pt_sentence, "ACTION", "form an alliance with ");
	}
	else if (act_name.find("Spar") != string::npos) {
		replace_all(con_pt_sentence, "ACTION", "spar with ");
	}
	else {
		replace_all(con_pt_sentence, "ACTION", act_name);
	}

	replace_all(con_pt_sentence, "HERO", hero_name);

	message = check_if_known(reply_pt_sentence, con_pt_sentence);
	replyOptions = dialogue.get_possible_reply_pts("Offer_Quest", optionsIndex);
}

bool DialogueController::check_down_cases(Hero*  temp_hero) {
	/*Special cases where the player is prevented from scrolling down. This includes
	the case when the player is already at the bottom of the list of options and case
	when the player is on the second to last option and the last option is not selectable.*/
	bool result = false;
	if (temp_hero && DialogueController::getState() == 1) {
		if (DialogueController::scroll_control == DialogueController::getOptions().size() - 1)
			result = true;
		if (DialogueController::scroll_control == DialogueController::getOptions().size() - 2) {
			if (DialogueController::getOptions()[DialogueController::scroll_control + 1][IsSelectable] == "0")
				result = true;
		}
	}
	else if (DialogueController::getState() == 1 && other->getName().find("Babalawo") != string::npos) {//babalawo case
		if (DialogueController::scroll_control == DialogueController::get_babalawo_options().size() - 1)
			result = true;
		if (DialogueController::scroll_control == DialogueController::get_babalawo_options().size() - 2) {
			if (DialogueController::get_babalawo_options()[DialogueController::scroll_control + 1][IsSelectable] == "0")
				result = true;
		}
	}
	else if (state == 2) {
		if (DialogueController::scroll_control == DialogueController::getReplyOptions().size() - 1)
			result = true;
	}

	return result;
}

dialogue_point DialogueController::load_yemoja_lesson() {
	dialogue_point dpoint;
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

	return dpoint;

}

dialogue_point DialogueController::load_oya_lesson() {
	dialogue_point dpoint;
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

	return dpoint;
}

dialogue_point DialogueController::load_ogun_lesson() {
	dialogue_point dpoint;
	switch (teach_move_counter) {
	    case 1:
		    dpoint = { "Teach Shield 1","Teach Shield 1" };
		    break;
	    case 2:
		    dpoint = { "Teach Shield 2","Teach Shield 2" };
		    break;
	    case 3:
		    dpoint = { "Teach Shield 3","Teach Shield 3" };
		    break;
	}

	return dpoint;
}