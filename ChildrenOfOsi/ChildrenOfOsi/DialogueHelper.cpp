#include "stdafx.h"
#include "DialogueHelper.h"
#include "Player.h"
#include "Tag.h"
typedef std::pair<int, ConversationPoint*> appealPoint;
template<>
bool std::operator==(const appealPoint& p1, const appealPoint& p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}



Player* player;
WorldObj* other;
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


DialogueHelper::DialogueHelper()
{
	srand(time(0)); //ensure good variation of random numbers when using rand()
}


DialogueHelper::~DialogueHelper()
{
}
int DialogueHelper::personality_appeal(ConversationPoint* point, vector<int> personality) {

	

	return ((personality[0]*point->multipliers->getHonor())+
	(personality[1] *point->multipliers->getPride())+
	(personality[2] *point->multipliers->getAggression())+
	(personality[3] *point->multipliers->getKindness())+
	(personality[4] *point->multipliers->getGreed())+
	(personality[5] *point->multipliers->getRecklessness())+
	(personality[6] *point->multipliers->getExtroversion()));
};
//functions where heroes make dialogue choices
dialogue_point DialogueHelper::choose_conv_pt(std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec)
{	/*index 0 = Affinity, index 1 = notoriety, index 2 = strength, index 3 = AffEstimateindex 4 = NotorEstimate, index 5 = StrEstimate*/

	/*index 0 = honor, index 1 = pride, index 2 = aggression, index 3 = kindnessindex 4 = greed, index 5 = recklessness, index 6 = extroversion*/
	vector<appealPoint> possible_replies;

	int conv_pt_index;

	std::vector<int> personality = yemoja_personality;
	std::vector<int> relationship = yemoja_relationship_with_shango;

	//check if the player has already asked the npc this question
	for (int i = 0; i < conversation_log_obj_pointer_vec.size() - 1; ++i) {
		if (conversation_log_obj_pointer_vec[i]->get_conv_point() == NULL)
			continue;
		if ((conversation_log_obj_pointer_vec[i]->get_conv_point()->get_name() == conversation_log_obj_pointer_vec[conversation_log_obj_pointer_vec.size() - 1]->get_conv_point()->get_name()) &&
			(conversation_log_obj_pointer_vec[conversation_log_obj_pointer_vec.size() - 1]->get_who() == conversation_log_obj_pointer_vec[i]->get_who()) && (conversation_log_obj_pointer_vec[conversation_log_obj_pointer_vec.size() - 1]->get_conv_point()->get_name().find("Ask",0) != string::npos))
			return {"",""};
	}

	for (auto i = conversation_log_obj_pointer_vec.begin(); i != conversation_log_obj_pointer_vec.end(); ++i) {
		//auto it = std::find(temp.begin(), temp.end(), (*i)->get_conv_point());
		//if (it != temp.end()) {
		//	temp.erase(std::remove(temp.begin(), temp.end(), *it), temp.end());
		//}
		//else {

		// }
		
		for (auto j : (*i)->get_conv_point()->tag_pointer_vec) {
			
			for (auto k : j->conversation_point_pointer_vec) {
				
				if (std::find(possible_replies.begin(), possible_replies.end(), std::make_pair(0, k)) != possible_replies.end()) {
				}
				else {
					if(relationship[0]>= k->rel_multipliers->getAffinity() && relationship[1] >= k->rel_multipliers->getNotoriety() && relationship[2] >= k->rel_multipliers->getStrength()){
					possible_replies.push_back(std::make_pair(0,k));}
				}
			
			
		      }


	    }
		
	}
	for (auto i = conversation_log_obj_pointer_vec.begin(); i != conversation_log_obj_pointer_vec.end(); ++i) {
		appealPoint tmp = std::make_pair(0, (*i)->get_conv_point());
		auto it = std::find(possible_replies.begin(), possible_replies.end(), tmp);
		if (it != possible_replies.end() && (*i)->get_who() == 2) {
			possible_replies.erase(std::remove(possible_replies.begin(), possible_replies.end(), *it), possible_replies.end());
		}
		else {

		}
	}
	//relationship filtering
	
	//choose based on personality
	std::vector<std::pair<int, ConversationPoint*>>  temp;
	dialogue_point def;
	def.push_back("");
	def.push_back("Goodbye");
	
	
	if (possible_replies.size() != 0) {
		conv_pt_index = rand() % (possible_replies.size());
		}
	int appeal;
	for (auto itor = possible_replies.begin(); itor != possible_replies.end(); itor++) {
			appeal = personality_appeal(itor->second, personality);
				temp.push_back(make_pair(appeal, itor->second));
	}
	possible_replies = temp;
	struct greatestAppeal {
		inline bool operator()(std::pair<int, ConversationPoint*> appeal1, std::pair<int, ConversationPoint*> appeal2) {//is temporarily an action
			return (appeal1.first > appeal2.first);
		};
	};

	std::sort(possible_replies.begin(), possible_replies.end(), greatestAppeal());
	std::ofstream ofs;
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::trunc);
	for (auto itor = possible_replies.begin(); itor != possible_replies.end(); itor++) {
	
		ofs << "Conversation Point Name: " << itor->second->get_name() << " Appeal " << itor->first << std::endl;

	}
	ofs.close();
	if (possible_replies.size() != 0) {
		return possible_replies[0].second->dpoint;
	}
	else {
		return{ "No_More_Phrases","No_More_Phrases" };
	}
}

dialogue_point DialogueHelper::choose_reply_pt(std::string point, int optn_inx, std::vector<ConversationLogObj*> conversation_log_obj_pointer_vec)
{
	//check if the player has already asked the npc this question
	for (int i = 0; i < conversation_log_obj_pointer_vec.size() - 1; ++i) {
		if (conversation_log_obj_pointer_vec[i]->get_conv_point() == NULL)
			continue;
		if ((conversation_log_obj_pointer_vec[i]->get_conv_point()->get_name() == conversation_log_obj_pointer_vec[conversation_log_obj_pointer_vec.size() - 1]->get_conv_point()->get_name()) &&
			(conversation_log_obj_pointer_vec[conversation_log_obj_pointer_vec.size() - 1]->get_who() == conversation_log_obj_pointer_vec[i]->get_who()) && (conversation_log_obj_pointer_vec[conversation_log_obj_pointer_vec.size() - 1]->get_conv_point()->get_name().find("Ask", 0) != string::npos))
			return{ "Already_Asked","Already_Asked" };
	}

	for (int i = 0; i < possible_reply_pts[optn_inx].size(); i++)
	{
		//if (possible_reply_pts[optn_inx][i][1].find(point, 0) != std::string::npos)
		//{
		//	return possible_reply_pts[optn_inx][i];
		//}
		if (possible_reply_pts[optn_inx][i][2] == point)
		{
			return possible_reply_pts[optn_inx][i];
		}
	}
	return{ "error phrase_type not found" };

}

std::vector<std::vector<dialogue_point>> DialogueHelper::get_possible_conv_pts()
{
	return possible_conv_pts;
}

std::vector<std::vector<dialogue_point>>& DialogueHelper::get_possible_conv_pts_ref()
{
	return possible_conv_pts;
}

std::vector<dialogue_point> DialogueHelper::get_possible_reply_pts(std::string point, int opts_inx)
{
	std::vector<dialogue_point> reply;
	for (int i = 0; i < possible_reply_pts[opts_inx].size(); i++) {
		if (possible_reply_pts[opts_inx][i][2].compare("Decline_To_Answer") == 0 || possible_reply_pts[opts_inx][i][2].compare(point) == 0) {
			reply.push_back({ possible_reply_pts[opts_inx][i] });
		}
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

	std::ifstream file("script_templates.json");
	file >> root;


	dialogue_template dtemp;

	//get a random conversation template
	int j = 0;
	if (root[diog_pt[1] + "_Templates"].size() > 1)
		j = rand() % root[diog_pt[1] + "_Templates"].size() + 1;
	else
		j = 1;
	/*populate a dialogue template using the contents
	of the randomly obtained dialogue template*/
	for (int i = 1; i <= root[diog_pt[1] + "_Templates"]
		[to_string(j)].size(); i++) {
		dtemp.push_back(root[diog_pt[1] + "_Templates"][to_string(j)]
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
		my_name = "SilverSoldier";
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
	
	/*look up appropriate random phrases using dialogue template
	if the string is punctuation then do not look it up and
	instead push the string right away*/

	///////////////////////////////////
	/*Do not use randomness to determine the dialogue_point if the name passed 
	into this function is Shango. Make what appears on upper GUI window be what 
	the player selected to say.*/
	///////////////////////////////////
	int j = 3;
	////stand in stuff until I finish refining topic extraction////
	std::pair<int, Memory*> topic;
	topic.first = 1;
	if (name != "Shango") {
		if (diog_pt[1].size() > 12) {//choose phrase based on relationship with other hero
			if (diog_pt[1].at(12) == 'M') {
				topic.first = 3;
				j = calc_text_choice_from_relationship(hero,topic);
			}
			else if (diog_pt[1].size() > 20) {
				if ((diog_pt[1].at(19) == 'S' || diog_pt[1].at(19) == 'A' || diog_pt[1].at(19) == 'N') && (diog_pt[1].at(13) != 'S')) {
					topic.first = 3;
					j = calc_text_choice_from_relationship(hero,topic);
				}
			}
		}
		else {//choose phrase based on relationship with Shango
			topic.first = 1;
			j = calc_text_choice_from_relationship(hero,topic);
		}
	}
	////////////////////////////////////////////////////////////////
	
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
				dpoint.push_back(root[tmp][to_string(j)]
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
		dpoint.push_back(root[diog_pt[1]][to_string(j)]
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
		if (itor->second->get_icon() == "qcp" && itor->second->get_name().find("Ask_About",0) == string::npos) {
			possible_conv_pts[3].push_back(itor->second->dpoint);//itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "qrp") {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "d") {
			
				possible_reply_pts[3].push_back(itor->second->dpoint);
				possible_reply_pts[0].push_back(itor->second->dpoint);
				possible_reply_pts[1].push_back(itor->second->dpoint);
				possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "scp") {
			possible_conv_pts[0].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "srp") {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "acp") {
			possible_conv_pts[1].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "arp" || itor->second->get_topic() == "nmp") {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
		else if (itor->second->get_icon() == "ncp" && itor->second->get_name().find("Move_To", 0) == string::npos) {
			possible_conv_pts[2].push_back(itor->second->dpoint);
		}
		else {
			possible_reply_pts[3].push_back(itor->second->dpoint);
			possible_reply_pts[0].push_back(itor->second->dpoint);
			possible_reply_pts[1].push_back(itor->second->dpoint);
			possible_reply_pts[2].push_back(itor->second->dpoint);
		}
	}
}

int DialogueHelper::calc_text_choice_from_relationship(Hero* hero, std::pair<int,Memory*> topic) {

	int phrase_picker = 1;
	unordered_map<int, Relationship*> rel;
	Relationship* npc_relationship;

	//base the npc reply on their relationship with the topic of the
	//conversation(we don't use the stuff in the below if statement
	//since we are using dummy vectors)
	/*if (hero->name != topic.first &&
		topic.first != 1) {
		rel = hero->rel;
		npc_relationship = rel[topic.first];//get npc's relationship with the topic of the conversation
	}*/

	/*Using dummy vectors for personalities and relationships for now 
	but will need to eventually use the relationship values from the 
	npc that is talking to the player rather than assuming that the player 
	is talking to Yemoja.
	*/
	if (topic.first == 1) {
		if (yemoja_relationship_with_shango[0] <= 20) {
			phrase_picker = 1;
		}
		else if (yemoja_relationship_with_shango[0] > 20 && yemoja_relationship_with_shango[0] < 40) {
			phrase_picker = 2;
		}
		else if (yemoja_relationship_with_shango[0] >= 40 && yemoja_relationship_with_shango[0] < 60) {
			phrase_picker = 3;
		}
		else if (yemoja_relationship_with_shango[0] >= 60 && yemoja_relationship_with_shango[0] < 80) {
			phrase_picker = 4;
		}
		else if (yemoja_relationship_with_shango[0] >= 80) {
			phrase_picker = 5;
		}
	}
	//here the topic is Oya so have Yemoja respond based on her relationship with Oya
	//rather than her relationship with Shango
	else {
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
	}

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
