#include "stdafx.h"
#include "DialogueHelper.h"
#include "Player.h"
#include "Tag.h"
#include "AIController.h"
typedef std::pair<int, ConversationPoint*> appealPoint;
template<>
bool std::operator==(const appealPoint& p1, const appealPoint& p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}

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

Player* player;
WorldObj* other; //the npc in conversation with the player
int state = 0;
//States:
//0 is no conversation
//1 is waiting for player input
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response
//5 is waiting for player to select "Next" option

/*state 5 is used to show the player's conversation point and
to allow the player to choose when to allow the npc to reply*/

//Hero to int associations
// SHANGO 1
// YEMOJA 2
// OYA 3
// OSHOSI 4
// OGUN 5

//Dummy vectors for Yemoja's and Shango's relationships and personalities

/*index 0 = Affinity, index 1 = notoriety, index 2 = strength, index 3 = AffEstimate
index 4 = NotorEstimate, index 5 = StrEstimate*/
std::vector<int> yemoja_relationship_with_shango = { 60, 50, 50, 50, 50, 50 };
std::vector<int> yemoja_relationship_with_oya = { 20, 40, 80, 70, 40, 80 };
std::vector<int> shango_relationship_with_yemoja = { 50, 50, 60, 50, 50, 60 };
std::vector<int> shango_relationship_with_oya = { 50, 50, 60, 50, 50, 60 };

/*index 0 = honor, index 1 = pride, index 2 = aggression, index 3 = kindness
index 4 = greed, index 5 = recklessness, index 6 = extroversion*/
std::vector<int> yemoja_personality = { 30, 70, 80, 60, 30, 30, 50 };
std::vector<int> shango_personality = { 50, 50, 60, 60, 50, 60, 20 };

DialogueHelper dialogue;

bool DialogueHelper::accepted_quest = false;
bool DialogueHelper::prompted_quest = false;
Action* DialogueHelper::quest = nullptr;
bool DialogueHelper::state_is_8 = false;
bool DialogueHelper::act_accepted = true;


DialogueHelper::DialogueHelper()
{
	srand(time(0)); //ensure good variation of random numbers when using rand()
}


DialogueHelper::~DialogueHelper()
{
}

int DialogueHelper::personality_appeal(ConversationPoint* point, Personality* personality) {

	

	return ((personality->getHonor()*point->multipliers->getHonor())+
	(personality->getPride() *point->multipliers->getPride())+
	(personality->getAggression() *point->multipliers->getAggression())+
	(personality->getKindness() *point->multipliers->getKindness())+
	(personality->getGreed() *point->multipliers->getGreed())+
	(personality->getRecklessness() *point->multipliers->getRecklessness())+
	(personality->getExtroversion() *point->multipliers->getExtroversion()));
};
int DialogueHelper::relationship_appeal(ConversationPoint* point, Relationship* my_rel) {
	int appeal = 0;
	int str_mult = point->rel_multipliers->getAffinity();
	int aff_mult = point->rel_multipliers->getAffinity();
	int noto_mult = point->rel_multipliers->getAffinity();

	appeal += my_rel->getStrength() * str_mult;
	appeal += my_rel->getAffinity() * aff_mult;
	appeal += my_rel->getNotoriety() * noto_mult;
	return appeal;
}


/*Runs the heuristic that npc's use to select a conversation point to say.*/
dialogue_point DialogueHelper::choose_conv_pt(std::vector<ConversationLogObj*> curr_conversation_log, Hero* other,Player* player)
{	/*index 0 = Affinity, index 1 = notoriety, index 2 = strength, index 3 = AffEstimateindex 4 = NotorEstimate, index 5 = StrEstimate*/

	/*index 0 = honor, index 1 = pride, index 2 = aggression, index 3 = kindnessindex 4 = greed, index 5 = recklessness, index 6 = extroversion*/
	vector<appealPoint> possible_replies;
	
	Personality* personality = other->traits;
	Relationship* relationship = other->rel[1];

	/*Hero* temp_hero = nullptr;
	if (other->getType() >= WorldObj::TYPE_NPC) {
		if (temp_hero = CheckClass::isHero(other))//added another equals was single equals before
		{
			perror("you cannot talk to this type of object");
		}
	}*/

	/*commented out code below that uses the real personalities and relationships
	because it caused Yemoja to stop having conversation points to say.*/
	/*Personality* per = other->traits;
	personality.push_back(per->getHonor());
	personality.push_back(per->getPride());
	personality.push_back(per->getAggression());
	personality.push_back(per->getKindness());
	personality.push_back(per->getGreed());
	personality.push_back(per->getRecklessness());
	personality.push_back(per->getExtroversion());

	Relationship* rel = other->rel[SHANGO];
	relationship.push_back(rel->getAffinity());
	relationship.push_back(rel->getNotoriety());
	relationship.push_back(rel->getStrength());
	relationship.push_back(rel->getAffEstimate());
	relationship.push_back(rel->getNotorEstimate());
	relationship.push_back(rel->getStrEstimate());*/

	if (curr_conversation_log.size() > 0) {
		if (curr_conversation_log[curr_conversation_log.size() - 1]->get_conv_point()->get_name() == "Ask_For_Quest") {
			Planner* p = AIController::get_plan(other->name);
			dialogue_point diog_pt = { "No Quest","No Quest" };
			///////////////////////////////////////////////////////
			/*Stand in stuff to check whether or not NPC wants to give quest
			to player when the player asks for one. NPC currently always
			gives quest to player.*/
			///////////////////////////////////////////////////////
			if (give_quest() && AIController::quest_response(other, player)) {//do they wanna give it to you?
				DialogueHelper::quest = p->get_current_action();
				bool has_quest = false;//initially assume player does not have quest from this NPC
				for (int i = 0; i < p->quests_given.size(); ++i) {//did they already give you a quest that you are currently working on?
					if (p->quests_given[i]->getDoer()->name == SHANGO && p->quests_given[i]->executed == false)
						has_quest = true;
				}
				if (!has_quest) {
					diog_pt = { "Offer_Quest","Offer_Quest" };
				}
				
			}
			return diog_pt;
		}
	}

	//check if the player has already asked the npc this question
	if (curr_conversation_log.size() > 0) {
		for (int i = 0; i < curr_conversation_log.size() - 1; ++i) {
			if (curr_conversation_log[i]->get_conv_point() == NULL)
				continue;
			if ((curr_conversation_log[i]->get_conv_point()->get_name() == curr_conversation_log[curr_conversation_log.size() - 1]->get_conv_point()->get_name())
				&&
				(curr_conversation_log[curr_conversation_log.size() - 1]->get_who() == curr_conversation_log[i]->get_who())
				&&
				(curr_conversation_log[curr_conversation_log.size() - 1]->get_conv_point()->get_name().find("Ask", 0) != string::npos))
				return{ "","" };
		}
	}
	//add related conversation points
		//for every thing in current conversation
	for (auto i = curr_conversation_log.begin(); i != curr_conversation_log.end(); ++i) {
			//for all related tags
		for (auto j : (*i)->get_conv_point()->tag) {  
				//for all conversation points related to each of those tags
			for (auto k : j->conversation_point) {
				//only consider it if it is not already in the vector of possible replies	
				if (std::find(possible_replies.begin(), possible_replies.end(), std::make_pair(0, k)) != possible_replies.end()) {
				}
				else {
					//only add it in if it fuffills the prereqs. 
				//if(relationship->getAffinity()>= k->rel_multipliers->getAffinity() && relationship->getNotoriety() >= k->rel_multipliers->getNotoriety() && relationship->getStrength() >= k->rel_multipliers->getStrength()){
					bool allowed = true;
					for (auto precond : Containers::conv_point_table[k->dpoint[1]]->req_preconds) {
						int temp1 = precond->get_cost(player, other);
						//the ori stuff means that the higher the ori the more likely it is for the hero to respond
						//positivly to what whatever it is you are saying
						if (precond->get_cost(player, other) != 0) {
							allowed = false;
						}

						//}//push it with a utility of 0 for now
					}
					if (allowed == true)
						possible_replies.push_back(std::make_pair(0, k));

				}
			}

	    }
		
	}
	//remove conversation points yemoja has already said in temp vector
		//for everything in current conversation
	for (auto i = curr_conversation_log.begin(); i != curr_conversation_log.end(); ++i) {
		appealPoint tmp = std::make_pair(0, (*i)->get_conv_point());//to check against possible replies
		auto it = std::find(possible_replies.begin(), possible_replies.end(), tmp);
		if (it != possible_replies.end() && (*i)->get_who() == other->name) {//if yemoja has said it
				//remove it from the possible replies
			possible_replies.erase(std::remove(possible_replies.begin(), possible_replies.end(), *it), possible_replies.end());
		}
		else {

		}
	}

	//remove conversation points from possible replies if they are in the NPC's permanent conversation vec
	for (auto i = other->conversation_log.begin(); i != other->conversation_log.end(); ++i) {
		appealPoint tmp = std::make_pair(0, (*i)->get_conv_point());
		auto it = std::find(possible_replies.begin(), possible_replies.end(), tmp);
		if (it != possible_replies.end() && (*i)->get_who() == other->name) {
			possible_replies.erase(std::remove(possible_replies.begin(), possible_replies.end(), *it), possible_replies.end());
		}
		else {

		}
	}

	//remove "form alliance" conversation point from NPC's possible replies if they are already allied with the player 
	for (int i = 0; i < possible_replies.size(); ++i) {
		if (possible_replies[i].second->get_name() == "Ask_To_Form_Alliance")
			possible_replies.erase(possible_replies.begin() + i);
	}
	//remove duel as reply if prereqs not met
	for (int i = 0; i < possible_replies.size(); ++i) {
		if (!(other->rel[player->name]->getAffinity() <= 30 && other->rel[player->name]->getStrength() <= 60)) {
			if (possible_replies[i].second->get_name() == "Ask_To_Duel")
				possible_replies.erase(possible_replies.begin() + i);
		}
	}

	//relationship filtering
	
	//choose based on personality
	std::vector<std::pair<int, ConversationPoint*>>  temp;

	

	int appeal;
	//prioritize, possible replies vector
		//for every reply
	for (auto itor = possible_replies.begin(); itor != possible_replies.end(); itor++) {
		//+ relationship_appeal(itor->second, relationship)
			appeal = personality_appeal(itor->second, personality) + relationship_appeal(itor->second, relationship);
				temp.push_back(make_pair(appeal, itor->second));//push onto temp vector with appeal
	}
	possible_replies = temp;//replace possible replies with temp
	struct greatestAppeal {
		inline bool operator()(std::pair<int, ConversationPoint*> appeal1, std::pair<int, ConversationPoint*> appeal2) {//is temporarily an action
			return (appeal1.first > appeal2.first);
		};
	};
	//sort possible replies by appeal
	std::sort(possible_replies.begin(), possible_replies.end(), greatestAppeal());

	//debug output
		std::ofstream ofs;
		ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::trunc);
		for (auto itor = possible_replies.begin(); itor != possible_replies.end(); itor++) {
	
			ofs << "Conversation Point Name: " << itor->second->get_name() << " Appeal " << itor->first << std::endl;

		}
		ofs.close();
	
	//handle having nothing to say
	if (possible_replies.size() != 0) {
		return possible_replies[0].second->dpoint;
	}
	else {
		return{ "No_More_Phrases","No_More_Phrases" };
	}
}

/*Returns all of the possible reply points that an npc can say
based on the player's conversation point. Since conversation points
between the player and soldiers do not get stored, the curr_conversation_log
will have size 0 if player is talking to soldier.*/
dialogue_point DialogueHelper::choose_reply_pt(std::string point, int optn_inx, std::vector<ConversationLogObj*> curr_conversation_log,Hero* other)
{

	Hero* temp_hero = CheckClass::isHero(other);
	ConversationLogObj* player_just_said = nullptr;
	if(temp_hero && curr_conversation_log.size() > 0)
	    player_just_said = curr_conversation_log[curr_conversation_log.size() - 1];

	//check if the player has already asked the npc this question
	for (int i = 0; i < curr_conversation_log.size() - 1; ++i) {
		if (curr_conversation_log.size() > 0) {
			if (curr_conversation_log[i]->get_conv_point() == NULL)
				continue;
			if ((curr_conversation_log[i]->get_conv_point()->get_name() == player_just_said->get_conv_point()->get_name()) &&
				(player_just_said->get_who() == curr_conversation_log[i]->get_who()) && (player_just_said->get_conv_point()->get_name().find("Ask", 0) != string::npos)) {
				if (player_just_said->get_conv_point()->get_name().find("Ask_For_Quest", 0) == string::npos)
					return{ "Already_Asked","Already_Asked" };
			}
		}
		else
			break;
	}

	//checks NPC permanent conversation log to check what player has already asked
	if (temp_hero) {
		for (int i = 0; i < temp_hero->conversation_log.size(); ++i) {
			if (temp_hero->conversation_log.size() > 0) {
				if (temp_hero->conversation_log[i]->get_conv_point() == NULL)
					continue;
				if ((temp_hero->conversation_log[i]->get_conv_point()->get_name() == player_just_said->get_conv_point()->get_name()) &&
					(player_just_said->get_who() == temp_hero->conversation_log[i]->get_who()) && (player_just_said->get_conv_point()->get_name().find("Ask", 0) != string::npos)) {
					if (player_just_said->get_conv_point()->get_name().find("Ask_For_Quest", 0) == string::npos)
						return{ "Already_Asked","Already_Asked" };
				}
			}
			else
				break;
		}
	}

	for (int i = 0; i < possible_reply_pts[optn_inx].size(); i++)
	{
		if (possible_reply_pts[optn_inx][i][CorrespondingConvPt] == point)
		{
			return possible_reply_pts[optn_inx][i];
		}
	}
	return{ "error phrase_type not found" };

}

/*Returns all of the possible conversation points that the player can say.*/
std::vector<std::vector<dialogue_point>> DialogueHelper::get_possible_conv_pts()
{
	return possible_conv_pts;
}

/*Returns a reference to all of the possible conversation points that the 
player can say.*/
std::vector<std::vector<dialogue_point>>& DialogueHelper::get_possible_conv_pts_ref()
{
	return possible_conv_pts;
}

/*gets player's possible replies to hero's conversation points*/
std::vector<dialogue_point> DialogueHelper::get_possible_reply_pts(std::string point, int opts_inx)
{
	std::vector<dialogue_point> reply;
	//reply.push_back({"Decline_To_Answer","Decline_To_Answer","","","1"});
	if (point != "Boast" && point != "Insult" && point != "Intimidate" && point != "Compliment" && point != "Offer Praise" && point != "Grovel") {
		if(point.find("_Quest") == string::npos && point.find("Name") == string::npos && point.find("Ask About") == string::npos)
		    reply.push_back({ "Refuse","Refuse","","","1","0" });
		for (int i = 0; i < possible_reply_pts[opts_inx].size(); i++) {
			if ((/*possible_reply_pts[opts_inx][i][CorrespondingConvPt].compare("Decline_To_Answer") == 0 ||*/ possible_reply_pts[opts_inx][i][CorrespondingConvPt].compare(point) == 0)
				&& point.find("_Quest") == string::npos) {
				reply.push_back({ possible_reply_pts[opts_inx][i] });
			}

		}
		

	}
	else {
		reply.push_back({ "Boast In Response", "Boast In Response","","","1","0" });
		reply.push_back({ "Intimidate In Response", "Intimidate In Response","","","1","0" });
		reply.push_back({ "Compliment In Response", "Compliment In Response","","","1","0" });
		reply.push_back({ "Offer Praise In Response", "Offer Praise In Response","","","1","0" });
		reply.push_back({ "Insult In Response", "Insult In Response","","","1","0" });
	}
	if (point.find("_Quest") != string::npos) {
		reply.push_back({ "Decline_Quest", "Decline_Quest","","","1","0" });
		reply.push_back({ "Accept_Quest", "Accept_Quest","","","1","0" });
	}
	
	return reply;
}

std::string DialogueHelper::gen_dialog(dialogue_point diog_pt, Hero* hero)
{
	std::string name = "";
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	//ofs << "type name: " << typeid(hero).name() << std::endl;
	//ofs.close();
	if (hero != nullptr) {
		if (hero->name == SHANGO)
		{
			name = "Shango";
		}
		else if (hero->name == YEMOJA)
		{
			name = "Yemoja";
		}
		else if (hero->name == OSHOSI)
		{
			name = "Oshosi";
		}
		else if (hero->name == OYA)
		{
			name = "Oya";
		}
		else if (hero->name == OGUN)
		{
			name = "Ogun";
		}
	}
	else {
		name = "SilverSoldier";
	}
	std::string sentence = convert_to_sentence(get_dialog(name, diog_pt,hero));

	return sentence;
}

std::string DialogueHelper::gen_dialog_negative(dialogue_point diog_pt, Hero* hero)
{
	std::string name = "";
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	//ofs << "type name: " << typeid(hero).name() << std::endl;
	//ofs.close();
	if (hero != nullptr) {
		if (hero->name == SHANGO)
		{
			name = "Shango";
		}
		else if (hero->name == YEMOJA)
		{
			name = "Yemoja";
		}
		else if (hero->name == OSHOSI)
		{
			name = "Oshosi";
		}
		else if (hero->name == OYA)
		{
			name = "Oya";
		}
		else if (hero->name == OGUN)
		{
			name = "Ogun";
		}
	}
	else {
		name = "SilverSoldier";
	}
	std::string sentence = convert_to_sentence(get_dialog_negative(name, diog_pt, hero));

	return sentence;
}

std::string DialogueHelper::gen_dialog_shrine(dialogue_point diog_pt, WorldObj* shrine)
{
	std::string name = shrine->getName();
	std::string sentence = convert_to_sentence(get_dialog_shrine(name, diog_pt));

	return sentence;
}

std::string DialogueHelper::gen_dialog_villager(dialogue_point diog_pt, WorldObj* villager)
{
	std::string name = villager->getName();
	std::string sentence = convert_to_sentence(get_dialog_villager(name, diog_pt));

	return sentence;
}

std::string DialogueHelper::gen_dialog_babalawo(dialogue_point diog_pt, WorldObj* babalawo)
{
	std::string name = babalawo->getName();
	std::string sentence = convert_to_sentence(get_dialog_babalawo(name, diog_pt));

	return sentence;
}

//poientially don't need this function
std::string DialogueHelper::gen_reply(dialogue_point diog_pt, Hero* hero, int relationship_phrase_picker, int relationship_phrase_picker_shango)
{
	std::string name;
	if (hero->name == SHANGO)
	{
		name = "Shango";
	}
	else if (hero->name == YEMOJA)
	{
		name = "Yemoja";
	}
	else if (hero->name == OSHOSI)
	{
		name = "Oshosi";
	}
	else if (hero->name == OYA)
	{
		name = "Oya";
	}
	else if (hero->name == OGUN)
	{
		name = "Ogun";
	}

	std::string sentence = convert_to_sentence(get_dialog(name, diog_pt, hero));

	return sentence;
}

dialogue_template DialogueHelper::get_template(dialogue_point diog_pt) {
	Json::Value root;


	Json::Reader reader;
	Json::CharReaderBuilder builder;
	//std::string test = 
	std::ifstream test("../ChildrenofOsi/script_templates.json", std::ifstream::binary);
	std::string errs;
	bool ok = reader.parse(test, root, false);
	if (!ok)
	{
		// report to the user the failure and their locations in the document.
		std::cout << errs.c_str() << "\n";
	}
	test.close();
	std::string encoding = root.get("encoding", "UTF-8").asString();
	std::cout << encoding << "\n";


	dialogue_template dtemp;

	//get a random conversation template
	int j = 0;
	if (root[diog_pt[ConvPointName] + "_Templates"].size() > 1)
		j = rand() % root[diog_pt[ConvPointName] + "_Templates"].size() + 1;
	else
		j = 1;
	/*populate a dialogue template using the contents
	of the randomly obtained dialogue template*/
	for (int i = 1; i <= root[diog_pt[ConvPointName] + "_Templates"]
		[to_string(j)].size(); i++) {
		dtemp.push_back(root[diog_pt[ConvPointName] + "_Templates"][to_string(j)]
			[to_string(i)].asString());
	}

	return dtemp;

}

dialogue_point DialogueHelper::get_dialog(std::string name, dialogue_point diog_pt, Hero* hero) {
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	dialogue_template dtemp = get_template(diog_pt);

	std::string my_name = name;
	if (name != "Yemoja" && name != "Shango" && name != "Oshosi" && name != "Ogun" && name != "Oya")
		my_name = "SilverSoldier"; //placeholder until there are jsons for other non-hero NPCs
	//////////////////////////////////
	/*add several else if statements here as more NPCs are added to the game in
	order to handle different json files for every NPC. json files are opened on a
	name basis*/
	//////////////////////////////////

	Json::Value root;


	Json::Reader reader;
	Json::CharReaderBuilder builder;
	//std::string test = 
	std::ifstream test("../ChildrenofOsi/_dialog.json", std::ifstream::binary);
	std::string errs;
	bool ok = reader.parse(test, root, false);
	if (!ok)
	{
		// report to the user the failure and their locations in the document.
		std::cout << errs.c_str() << "\n";
	}

	std::string encoding = root.get("encoding", "UTF-8").asString();
	std::cout << encoding << "\n";

	dialogue_point dpoint;
	
	int phrase_picker = 3; //set phrase picker to "neutral" by default

	std::pair<int, Memory*> topic;
	topic.first = SHANGO;
	if (name != "Shango" && name != "SilverSoldier") {
		/////////*set phrase picker based on relationship with topic of diog_pt*//////
			if (diog_pt[ConvPointName].find("Advise To",0) != string::npos || diog_pt[ConvPointName].find("Ask About", 0) != string::npos
				|| diog_pt[ConvPointName].find("Take Advice", 0) != string::npos || diog_pt[ConvPointName].find("Tell About", 0) != string::npos) {
				topic.first = hero_name_to_int(diog_pt[Topic]);
				phrase_picker = calc_text_choice_from_relationship(hero,topic);
			}
			//choose phrase based on relationship with Shango
		    else {
			    topic.first = 1;
				phrase_picker = calc_text_choice_from_relationship(hero,topic);
		    }
	}

	if (name != "Shango") {
		std::string tmp = "";
		for (int i = 1; i <= dtemp.size(); i++) {
			tmp = dtemp[i - 1];
			if (tmp != "?" && tmp != "," && tmp != "." &&
				tmp != "!" && tmp != "_") {
				//if (root[tmp].size() > 1)
					//j = rand() % root[tmp].size() + 1;
				//else
					//j = 1;
				dpoint.push_back(root[tmp][to_string(phrase_picker)]
					.asString());
				//ofs << "dp: " << root[tmp][to_string(j)]
					//.asString() << std::endl;
			}
			else {
				dpoint.push_back(tmp);

			}

		}
	}
	else {
		if(state_is_8 == false)
	        phrase_picker = (rand() % 5 + 1);//pick Shango flavor text randomly
		dpoint.push_back(root[diog_pt[ConvPointName]][to_string(phrase_picker)]
			.asString());
	}
	if (state_is_8)
		state_is_8 = false;
	return dpoint;

}

dialogue_point DialogueHelper::get_dialog_negative(std::string name, dialogue_point diog_pt, Hero* hero) {
	//std::ofstream ofs;
	//ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	dialogue_template dtemp = get_template(diog_pt);

	std::string my_name = name;
	if (name != "Yemoja" && name != "Shango" && name != "Oshosi" && name != "Ogun" && name != "Oya")
		my_name = "SilverSoldier"; //placeholder until there are jsons for other non-hero NPCs
									   //////////////////////////////////
								   /*add several else if statements here as more NPCs are added to the game in
								   order to handle different json files for every NPC. json files are opened on a
								   name basis*/
								   //////////////////////////////////

	Json::Value root;

	std::string dialogue_filename = my_name + "_dialog.json";

	std::ifstream file(dialogue_filename);
	file >> root;

	dialogue_point dpoint;

	//sets phrase_picker to either 1 or 2, which reflects a negative/hateful response
	int phrase_picker = rand() % 2 + 1;

	if (name != "Shango") {
		std::string tmp = "";
		for (int i = 1; i <= dtemp.size(); i++) {
			tmp = dtemp[i - 1];
			if (tmp != "?" && tmp != "," && tmp != "." &&
				tmp != "!" && tmp != "_") {
				//if (root[tmp].size() > 1)
				//j = rand() % root[tmp].size() + 1;
				//else
				//j = 1;
				dpoint.push_back(root[tmp][to_string(phrase_picker)]
					.asString());
				//ofs << "dp: " << root[tmp][to_string(j)]
				//.asString() << std::endl;
			}
			else {
				dpoint.push_back(tmp);

			}

		}
	}
	else {
		dpoint.push_back(root[diog_pt[ConvPointName]][to_string(phrase_picker)]
			.asString());
	}

	return dpoint;

}

dialogue_point DialogueHelper::get_dialog_shrine(std::string name,dialogue_point diog_pt) {

	dialogue_template dtemp = get_template(diog_pt);

	std::string my_name = "Shrine";

	Json::Value root;

	std::string dialogue_filename = my_name + "_dialog.json";

	std::ifstream file(dialogue_filename);
	file >> root;

	dialogue_point dpoint;

	int phrase_picker = rand() % 5 + 1;//rand num between 1 and 5 inclusive

	if (name != "Shango") {
		std::string tmp = "";
		for (int i = 1; i <= dtemp.size(); i++) {
			tmp = dtemp[i - 1];
			if (tmp != "?" && tmp != "," && tmp != "." &&
				tmp != "!" && tmp != "_") {
				dpoint.push_back(root[name][tmp][to_string(phrase_picker)]
					.asString());
			}
			else {
				dpoint.push_back(tmp);

			}

		}
	}
	else {
		dpoint.push_back(root[diog_pt[ConvPointName]][to_string(phrase_picker)]
			.asString());
	}

	return dpoint;

}

dialogue_point DialogueHelper::get_dialog_babalawo(std::string name, dialogue_point diog_pt) {

	dialogue_template dtemp = get_template(diog_pt);

	std::string my_name = "Babalawo";

	Json::Value root;

	std::string dialogue_filename = my_name + "_dialog.json";

	std::ifstream file(dialogue_filename);
	file >> root;

	dialogue_point dpoint;

	int phrase_picker = rand() % 5 + 1;//rand num between 1 and 5 inclusive

	if (name != "Shango") {
		std::string tmp = "";
		for (int i = 1; i <= dtemp.size(); i++) {
			tmp = dtemp[i - 1];
			if (tmp != "?" && tmp != "," && tmp != "." &&
				tmp != "!" && tmp != "_") {
				dpoint.push_back(root[name][tmp][to_string(phrase_picker)]
					.asString());
			}
			else {
				dpoint.push_back(tmp);

			}

		}
	}
	else {
		dpoint.push_back(root[diog_pt[ConvPointName]][to_string(phrase_picker)]
			.asString());
	}

	return dpoint;

}

dialogue_point DialogueHelper::get_dialog_villager(std::string name, dialogue_point diog_pt) {

	dialogue_template dtemp = get_template(diog_pt);

	std::string my_name = "Villager";

	Json::Value root;

	std::string dialogue_filename = my_name + "_dialog.json";

	std::ifstream file(dialogue_filename);
	file >> root;

	dialogue_point dpoint;

	int phrase_picker = rand() % 5 + 1;//rand num between 1 and 5 inclusive

	if (name != "Shango") {
		std::string tmp = "";
		for (int i = 1; i <= dtemp.size(); i++) {
			tmp = dtemp[i - 1];
			if (tmp != "?" && tmp != "," && tmp != "." &&
				tmp != "!" && tmp != "_") {
				dpoint.push_back(root[tmp][to_string(phrase_picker)]
					.asString());
			}
			else {
				dpoint.push_back(tmp);

			}

		}
	}
	else {
		dpoint.push_back(root[diog_pt[ConvPointName]][to_string(phrase_picker)]
			.asString());
	}

	return dpoint;

}

std::string DialogueHelper::convert_to_sentence(dialogue_point dialog_pt)
{
	string sentence;
	for (auto i = dialog_pt.begin(); i != dialog_pt.end(); ++i) {
		std::string tmp = "";
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			tmp += *j;
		}
		sentence += tmp;
	}
	return sentence;
}

/*Associates conversation and reply points with icons
on the GUI. "qcp" = question conversation point, "qrp" = question reply point
etc. Every reply point is associated with every icon because it is possible 
for an npc to say conversation points to the player that are not part of the icon
associated with the player's conversation point. The player needs to be able
to reply to any conversation point regardless of what icon they are on.*/
void DialogueHelper::fill_conversations() {
	for (int i = 0; i < Containers::conv_point_table.size(); i++)
	{
		possible_conv_pts.push_back({});
	}
	for (int i = 0; i < Containers::conv_point_table.size(); i++)
	{
		possible_reply_pts.push_back({});
	}
	for (auto itor = Containers::conv_point_table.begin(); itor != Containers::conv_point_table.end(); ++itor) {
		if (itor->second->get_icon() == "qcp" && itor->second->get_name().find("Ask About",0) == string::npos && itor->second->get_name().find("Ask_For_Quest", 0) == string::npos) {
			possible_conv_pts[QuestionMarkIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "qrp") {
			possible_reply_pts[QuestionMarkIcon].push_back(itor->second->dpoint);
			possible_reply_pts[StrengthIcon].push_back(itor->second->dpoint);
			possible_reply_pts[AffinityIcon].push_back(itor->second->dpoint);
			possible_reply_pts[NotorietyIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "d") {
			
				possible_reply_pts[QuestionMarkIcon].push_back(itor->second->dpoint);
				possible_reply_pts[StrengthIcon].push_back(itor->second->dpoint);
				possible_reply_pts[AffinityIcon].push_back(itor->second->dpoint);
				possible_reply_pts[NotorietyIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "scp") {
			possible_conv_pts[StrengthIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "srp") {
			possible_reply_pts[QuestionMarkIcon].push_back(itor->second->dpoint);
			possible_reply_pts[StrengthIcon].push_back(itor->second->dpoint);
			possible_reply_pts[AffinityIcon].push_back(itor->second->dpoint);
			possible_reply_pts[NotorietyIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "acp") {
			possible_conv_pts[AffinityIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "arp" || itor->second->get_topic() == "nmp") {
			possible_reply_pts[QuestionMarkIcon].push_back(itor->second->dpoint);
			possible_reply_pts[StrengthIcon].push_back(itor->second->dpoint);
			possible_reply_pts[AffinityIcon].push_back(itor->second->dpoint);
			possible_reply_pts[NotorietyIcon].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "ncp" && itor->second->get_name().find("Advise To", 0) == string::npos) {
			possible_conv_pts[NotorietyIcon].push_back(itor->second->dpoint);
		}
		else if(itor->second->get_icon() == "nrp"){
			possible_reply_pts[QuestionMarkIcon].push_back(itor->second->dpoint);
			possible_reply_pts[StrengthIcon].push_back(itor->second->dpoint);
			possible_reply_pts[AffinityIcon].push_back(itor->second->dpoint);
			possible_reply_pts[NotorietyIcon].push_back(itor->second->dpoint);
		}
	}
}

int DialogueHelper::calc_text_choice_from_relationship(Hero* hero, std::pair<int,Memory*> topic) {

	int phrase_picker = 1;
	unordered_map<int, Relationship*> rel;
	Relationship* npc_relationship;

	//base the npc reply on their relationship with the topic of the
	//conversation
	rel = hero->rel;
	if (topic.first == -1)
		topic.first = SHANGO;
	npc_relationship = rel[topic.first];//get npc's relationship with the topic of the conversation point

	/*chooses a number between 1 and 5 based on the npc's affinity for the topic
	of their conversation or reply point. The chosen number is used to select a phrase
	from the range hateful to loving.
	*/
	if (npc_relationship->getAffinity() <= 20) {
			phrase_picker = 1;
	}
	else if (npc_relationship->getAffinity() > 20 && npc_relationship->getAffinity() < 40) {
			phrase_picker = 2;
	}
	else if (npc_relationship->getAffinity() >= 40 && npc_relationship->getAffinity() < 60) {
			phrase_picker = 3;
	}
	else if (npc_relationship->getAffinity() >= 60 && npc_relationship->getAffinity() < 80) {
			phrase_picker = 4;
	}
	else if (npc_relationship->getAffinity() >= 80) {
			phrase_picker = 5;
	}
	//}
	//here the topic is Oya so have Yemoja respond based on her relationship with Oya
	//rather than her relationship with Shango
	/*else {
		if (yemoja_relationship_with_oya[0] <= 20) {
			phrase_picker = 1;
		}
		else if (yemoja_relationship_with_oya[0] > 20 && yemoja_relationship_with_oya[0] < 40) {
			phrase_picker = 2;
		}
		else if (yemoja_relationship_with_oya[0] >= 40 && yemoja_relationship_with_oya[0] < 60) {
			phrase_picker = 3;
		}
		else if (yemoja_relationship_with_oya[0] >= 60 && yemoja_relationship_with_oya[0] < 80) {
			phrase_picker = 4;
		}
		else if (yemoja_relationship_with_oya[0] >= 80) {
			phrase_picker = 5;
		}
	}*/
	if (act_accepted && topic.first == SHANGO && npc_relationship->getAffinity() < 40)
		phrase_picker = 3;



	return phrase_picker;
}

int DialogueHelper::hero_name_to_int(std::string hero) {
	int who_arg = 1;
	if (hero == "Shango")
	{
		who_arg = 1;
	}
	else if (hero == "Yemoja")
	{
		who_arg = 2;
	}
	else if (hero == "Oshosi")
	{
		who_arg = 4;
	}
	else if (hero == "Oya")
	{
		who_arg = 3;
	}
	else if (hero == "Ogun")
	{
		who_arg = 5;
	}

	return who_arg;
}

std::string DialogueHelper::int_to_hero_name(int hero) {
	std::string who_arg = "";
	if (hero == 1)
	{
		who_arg = "Shango";
	}
	else if (hero == 2)
	{
		who_arg = "Yemoja";
	}
	else if (hero == 3)
	{
		who_arg = "Oya";
	}
	else if (hero == 4)
	{
		who_arg = "Oshosi";
	}
	else if (hero == 5)
	{
		who_arg = "Ogun";
	}

	return who_arg;
}

bool DialogueHelper::give_quest() {
	return true;

}
